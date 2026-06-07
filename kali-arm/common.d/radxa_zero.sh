case $2 in
    sdcard)
        format="sdcard" ;;

    emmc)
        format="emmc" ;;

    *)
        echo -e "\n[-] Unsupported format: $2" >&2; exit 1 ;;

esac

# Network configs
basic_network

# Third stage
cat <<EOF >>"${work_dir}"/third-stage
status_stage3 'Install kali-sbc package'
eatmydata apt-get install -y kali-sbc-amlogic

# We need "file" for the kernel scripts we run, and it won't be installed if you pass --slim
# So we always make sure it's installed. Also, for hdmi audio, we need to run commands
# so install alsa-utils for amixer and alsactl availability.
eatmydata apt-get install -y file alsa-utils

# Note: This just creates an empty /boot/extlinux/extlinux.conf for us to use
# later when we install the kernel, and then fixup further down
status_stage3 'Run u-boot-update'
u-boot-update

status_stage3 'Copy WiFi/BT firmware'
mkdir -p /lib/firmware/brcm/
cp /bsp/firmware/radxa-zero/* /lib/firmware/brcm/

status_stage3 'Add needed extlinux and uenv scripts'
cp /bsp/scripts/radxa/update_extlinux.sh /usr/local/sbin/
cp /bsp/scripts/radxa/update_uenv.sh /usr/local/sbin/
cp /bsp/scripts/radxa/config.txt /boot/
mkdir -p /etc/kernel/postinst.d
# Be sure to update the cmdline with the correct UUID after creating the img.
cp /bsp/scripts/radxa/cmdline /etc/kernel
cp /bsp/scripts/radxa/extlinux /etc/default/extlinux
cp /bsp/scripts/radxa/zz-uncompress /etc/kernel/postinst.d/
cp /bsp/scripts/radxa/zz-update-extlinux /etc/kernel/postinst.d/
cp /bsp/scripts/radxa/zz-update-uenv /etc/kernel/postinst.d/

status_stage3 'Fixup wireless-regdb signature'
update-alternatives --set regulatory.db /lib/firmware/regulatory.db-upstream

status_stage3 'Remove cloud-init where it is not used'
eatmydata apt-get -y purge --autoremove cloud-init
EOF

# Run third stage
include third_stage

# Clean system
include clean_system

# Kernel section. If you want to use a custom kernel, or configuration, replace
# them in this section
status "Kernel stuff"
git clone --depth 1 -b radxa-zero-linux-5.10.y https://github.com/steev/linux.git ${work_dir}/usr/src/kernel
cd ${work_dir}/usr/src/kernel
git rev-parse HEAD >${work_dir}/usr/src/kernel-at-commit
rm -rf .git
export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-
make radxa_zero_defconfig
make -j $(grep -c processor /proc/cpuinfo) LOCALVERSION="" bindeb-pkg
make mrproper
make radxa_zero_defconfig
cd ..

# Cross building kernel packages produces broken header packages
# so only install the headers if we're building on arm64
if [ "$(arch)" == 'aarch64' ]; then
    # We don't need to install the linux-libc-dev package, we just want kernel and headers
    rm linux-libc-dev*.deb
    # Temporary hack to work around dpkg statoverride user errors
    mv "${work_dir}"/var/lib/dpkg/statoverride "${work_dir}"/var/lib/dpkg/statoverride.bak
    dpkg --root "${work_dir}" -i linux-*.deb
    mv "${work_dir}"/var/lib/dpkg/statoverride.bak "${work_dir}"/var/lib/dpkg/statoverride

else
    # Temporary hack to work around dpkg statoverride user errors
    mv "${work_dir}"/var/lib/dpkg/statoverride "${work_dir}"/var/lib/dpkg/statoverride.bak
    dpkg --root "${work_dir}" -i linux-image-*.deb
    mv "${work_dir}"/var/lib/dpkg/statoverride.bak "${work_dir}"/var/lib/dpkg/statoverride

fi

rm linux-*_*

cd "${repo_dir}/"

# Calculate the space to create the image and create
make_image

# Create the disk partitions
status "Create the disk partitions"
parted -s "${image_dir}/${image_name}.img" mklabel msdos
parted -s "${image_dir}/${image_name}.img" mkpart primary fat32 32MiB "${bootsize}"MiB
parted -s -a minimal "${image_dir}/${image_name}.img" mkpart primary "$fstype" "${bootsize}"MiB 100%

# Set the partition variables
make_loop

# Create file systems
status "Formatting partitions"
mkfs_partitions

# Make fstab
make_fstab

# Create the dirs for the partitions and mount them
status "Create the dirs for the partitions and mount them"
mkdir -p "${base_dir}"/root/
mount "${rootp}" "${base_dir}"/root
mkdir -p "${base_dir}"/root/boot
mount "${bootp}" "${base_dir}"/root/boot

status "Edit the extlinux.conf file to set root uuid and proper name"
# Ensure we don't have root=/dev/sda3 in the extlinux.conf which comes from running u-boot-menu in a cross chroot
# We do this down here because we don't know the UUID until after the image is created
sed -i -e "0,/append.*/s//append root=UUID=$(blkid -s UUID -o value ${rootp}) rootfstype=$fstype earlyprintk console=ttyAML0,115200 console=tty1 console=both swiotlb=1 coherent_pool=1m ro rootwait/g" ${work_dir}/boot/extlinux/extlinux.conf
# And we remove the "GNU/Linux because we don't use it
sed -i -e "s|.*GNU/Linux Rolling|menu label Kali Linux|g" ${work_dir}/boot/extlinux/extlinux.conf

# And we need to edit the /etc/kernel/cmdline file as well
sed -i -e "s/root=UUID=.*/root=UUID=$(blkid -s UUID -o value ${rootp})/" ${work_dir}/etc/kernel/cmdline

# Turns out, when you have eMMC, and you are booting from SD card, it will randomly pick which boot partition
# to use when you use LABEL=BOOT in the fstab instead of picking the one that you're actually using.
# This can be very detrimental depending on what you are doing in /boot... so lets replace label with uuid.
sed -i -e "s/LABEL=BOOT/UUID=$(blkid -s UUID -o value ${bootp})/" ${work_dir}/etc/fstab

status "Set the default options in /etc/default/u-boot"
echo 'U_BOOT_MENU_LABEL="Kali Linux"' >>${work_dir}/etc/default/u-boot
echo 'U_BOOT_PARAMETERS="earlyprintk console=ttyAML0,115200 console=tty1 console=both swiotlb=1 coherent_pool=1m ro rootwait"' >>${work_dir}/etc/default/u-boot

status "Rsyncing rootfs into image file"
rsync -HPavz -q --exclude boot "${work_dir}"/ "${base_dir}"/root/
sync

status "Rsyncing boot into image file (/boot)"
rsync -rtx -q "${work_dir}"/boot "${base_dir}"/root
sync

status "u-Boot"
cd "${work_dir}"
git clone https://github.com/radxa/fip.git
git clone https://github.com/u-boot/u-boot.git -b v2022.10 --depth 1
cd u-boot

# Remove amlogic from the config, this matches what LibreElec does, as well as the vendor u-boot
patch -p1 --no-backup-if-mismatch <"${repo_dir}"/patches/u-boot/radxa/0001-HACK-configs-meson64-remove-amlogic.patch

# Enable USB at preboot, so we can use usb keyboard to interrupt boot sequence, with the nifty side effect
# that USB boot *should* also work, but untested.
patch -p1 --no-backup-if-mismatch <"${repo_dir}"/patches/u-boot/radxa/0002-boards-amlogic-enable-usb-preboot.patch
make distclean
make radxa-zero_defconfig
make ARCH=arm -j$(nproc)
cp u-boot.bin ../fip/radxa-zero/bl33.bin
cd ../fip/radxa-zero/
make

# https://wiki.radxa.com/Zero/dev/u-boot
if [ "$format" == "sdcard" ]; then
    dd if=u-boot.bin.sd.bin of=${loopdevice} conv=fsync,notrunc bs=1 count=442
    dd if=u-boot.bin.sd.bin of=${loopdevice} conv=fsync,notrunc bs=512 skip=1 seek=1

else
    dd if=u-boot.bin of=${loopdevice} conv=fsync,notrunc bs=512 seek=1

fi

cd "${repo_dir}/"
rm -rf "${work_dir}"/{fip,u-boot}

# Load default finish_image configs
include finish_image
