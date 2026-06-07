#!/usr/bin/env bash
#
# Every Kali ARM image finishes with this
#

# Stop on error
set -e

# Make sure we are somewhere we are not going to unmount
cd "${repo_dir}/"

# Flush buffers and bytes - this is nicked from the Devuan arm-sdk
blockdev --flushbufs "${loopdevice}"
python3 -c 'import os; os.fsync(open("'${loopdevice}'", "r+b"))'

# Unmount filesystem
umount_partitions

# Check filesystem
status "Check filesystem partitions ($rootfstype)"
if [ -n "${bootp}" ] && [ "${extra}" = 1 ]; then
  log "Check filesystem boot partition:${colour_reset} (${bootfstype})" green

  if [ "$bootfstype" = "vfat" ]; then
    dosfsck -w -r -a -t "${bootp}"

  else
    e2fsck -y -f "${bootp}"

  fi
fi

log "Check filesystem root partition:${colour_reset} ($rootfstype)" green
e2fsck -y -f "${rootp}"

# Remove loop devices
status "Remove loop devices"
losetup -d "${loopdevice}"

# Create sha256sum file of the UNCOMPRESSED image file
log "Generate sha256sum: ${colour_reset}($img)" green
cd "${image_dir}"

shasum -a 256 "${image_name}.img" >"${image_name}.img.sha256sum"
cd "${repo_dir}"

# Compress image compilation
compress_img

# Create sha256sum file of the COMPRESSED image file
if [ -f "${image_dir}/${image_name}.img.$compress" ]; then
  log "Generate sha256sum: ${colour_reset}($img.$compress)" green

  cd "${image_dir}"
  shasum -a 256 "${image_name}.img.$compress" >"${image_name}.img.$compress.sha256sum"
  cd "${repo_dir}"

fi

# Clean up all the temporary build stuff and remove the directories
#clean_build

# Quit
log "Your image is: ${colour_reset}$img (Size: $(du -h $img | cut -f1))" bold
exit 0
