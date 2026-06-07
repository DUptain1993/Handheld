#!/usr/bin/env bash
#
# Kali Linux ARM build-script for NanoPi2 (32-bit)
# Source: https://gitlab.com/kalilinux/build-scripts/kali-arm
#
# This is a community script - you will need to generate your own image to use
# More information: https://www.kali.org/docs/arm/nanopi2/
#

# Hardware model
hw_model=${hw_model:-"nanopi2"}

# Architecture
architecture=${architecture:-"armhf"}

# Desktop manager (xfce, gnome, i3, kde, lxde, mate, e17 or none)
desktop=${desktop:-"xfce"}

# Load default base_image configs
source ./common.d/base_image.sh

# Network configs
basic_network
add_interface eth0

# Third stage
cat <<EOF >>"${work_dir}"/third-stage
status_stage3 'Enable login over serial'
echo "T0:23:respawn:/sbin/agetty -L ttyAMA0 115200 vt100" >> /etc/inittab
EOF

# Run third stage
include third_stage

# Clean system
include clean_system

# Calculate the space to create the image and create
make_image

# We need an older gcc because of kernel age
cd "${base_dir}"
git clone --depth 1 https://gitlab.com/kalilinux/packages/gcc-arm-linux-gnueabihf-4-7.git gcc-arm-linux-gnueabihf-4.7

# Kernel section. If you want to use a custom kernel, or configuration, replace
# them in this section
git clone --depth 1 https://github.com/friendlyarm/linux-3.4.y -b nanopi2-lollipop-mr1 ${work_dir}/usr/src/kernel
cd ${work_dir}/usr/src/kernel
git rev-parse HEAD >${work_dir}/usr/src/kernel-at-commit
touch .scmversion
export ARCH=arm
export CROSS_COMPILE="${base_dir}"/gcc-arm-linux-gnueabihf-4.7/bin/arm-linux-gnueabihf-
patch -p1 --no-backup-if-mismatch <${repo_dir}/patches/mac80211.patch

# Ugh, this patch is needed because the ethernet driver uses parts of netdev
# from a newer kernel?
patch -p1 --no-backup-if-mismatch <${repo_dir}/patches/0001-Remove-define.patch
cp ${repo_dir}/kernel-configs/nanopi2* ${work_dir}/usr/src/
cp ../nanopi2-vendor.config .config
make -j $(grep -c processor /proc/cpuinfo)
make uImage
make modules_install INSTALL_MOD_PATH=${work_dir}

# We copy this twice because you can't do symlinks on fat partitions
# Also, the uImage known as uImage.hdmi is used by uboot if hdmi output is
# detected
cp arch/arm/boot/uImage ${work_dir}/boot/uImage-720p
cp arch/arm/boot/uImage ${work_dir}/boot/uImage.hdmi

# Friendlyarm suggests staying at 720p for now
#cp ../nanopi2-1080p.config .config
#make -j $(grep -c processor /proc/cpuinfo)
#make uImage
#cp arch/arm/boot/uImage ${work_dir}/boot/uImage-1080p
#cp ../nanopi2-lcd-hd101.config .config
#make -j $(grep -c processor /proc/cpuinfo)
#make uImage
#cp arch/arm/boot/uImage ${work_dir}/boot/uImage-hd101
#cp ../nanopi2-lcd-hd700.config .config
#make -j $(grep -c processor /proc/cpuinfo)
#make uImage
#cp arch/arm/boot/uImage ${work_dir}/boot/uImage-hd700
#cp ../nanopi2-lcd.config .config
#make -j $(grep -c processor /proc/cpuinfo)
#make uImage
# The default uImage is for lcd usage, so we copy the lcd one twice
# so people have a backup in case they overwrite uImage for some reason
#cp arch/arm/boot/uImage ${work_dir}/boot/uImage-s70
#cp arch/arm/boot/uImage ${work_dir}/boot/uImage.lcd
#cp arch/arm/boot/uImage ${work_dir}/boot/uImage
cd "${base_dir}"

# FriendlyARM suggest using backports for wifi with their devices, and the
# recommended version is the 4.4.2
cd ${work_dir}/usr/src/
#wget https://www.kernel.org/pub/linux/kernel/projects/backports/stable/v4.4.2/backports-4.4.2-1.tar.xz
#tar -xf backports-4.4.2-1.tar.xz
git clone https://github.com/friendlyarm/wireless
cd wireless
cd backports-4.4.2-1
patch -p1 --no-backup-if-mismatch <${repo_dir}/patches/kali-wifi-injection-4.4.patch
cd ..
#cp ${repo_dir}/kernel-configs/backports.config .config
#make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j $(grep -c processor /proc/cpuinfo) KLIB_BUILD=${work_dir}/usr/src/kernel KLIB=${work_dir}
#make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- KLIB_BUILD=${work_dir}/usr/src/kernel KLIB=${work_dir} INSTALL_MOD_PATH=${work_dir} install
#make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- KLIB_BUILD=${work_dir}/usr/src/kernel KLIB=${work_dir} mrproper
#cp ${repo_dir}/kernel-configs/backports.config .config
XCROSS="${base_dir}"/gcc-arm-linux-gnueabihf-4.7/bin/arm-linux-gnueabihf- ANDROID=n ./build.sh -k ${work_dir}/usr/src/kernel -c nanopi2 -o ${work_dir}
cd "${base_dir}"

# Now we clean up the kernel build
cd ${work_dir}/usr/src/kernel
make mrproper
cd "${base_dir}"

# Copy over the firmware for the nanopi2/3 wifi
# At some point, nexmon could work for the device, but the support would need to
# be added to nexmon
mkdir -p ${work_dir}/lib/firmware/ap6212/
wget https://raw.githubusercontent.com/friendlyarm/android_vendor_broadcom_nanopi2/nanopi2-lollipop-mr1/proprietary/nvram_ap6212.txt -O ${work_dir}/lib/firmware/ap6212/nvram.txt
wget https://raw.githubusercontent.com/friendlyarm/android_vendor_broadcom_nanopi2/nanopi2-lollipop-mr1/proprietary/nvram_ap6212a.txt -O ${work_dir}/lib/firmware/ap6212/nvram_ap6212.txt
wget https://raw.githubusercontent.com/friendlyarm/android_vendor_broadcom_nanopi2/nanopi2-lollipop-mr1/proprietary/fw_bcm43438a0.bin -O ${work_dir}/lib/firmware/ap6212/fw_bcm43438a0.bin
wget https://raw.githubusercontent.com/friendlyarm/android_vendor_broadcom_nanopi2/nanopi2-lollipop-mr1/proprietary/fw_bcm43438a1.bin -O ${work_dir}/lib/firmware/ap6212/fw_bcm43438a1.bin
wget https://raw.githubusercontent.com/friendlyarm/android_vendor_broadcom_nanopi2/nanopi2-lollipop-mr1/proprietary/fw_bcm43438a0_apsta.bin -O ${work_dir}/lib/firmware/ap6212/fw_bcm43438a0_apsta.bin
wget https://raw.githubusercontent.com/friendlyarm/android_vendor_broadcom_nanopi2/nanopi2-lollipop-mr1/proprietary/bcm43438a0.hcd -O ${work_dir}/lib/firmware/ap6212/bcm43438a0.hcd
wget https://raw.githubusercontent.com/friendlyarm/android_vendor_broadcom_nanopi2/nanopi2-lollipop-mr1/proprietary/bcm43438a1.hcd -O ${work_dir}/lib/firmware/ap6212/bcm43438a1.hcd
wget https://raw.githubusercontent.com/friendlyarm/android_vendor_broadcom_nanopi2/nanopi2-lollipop-mr1/proprietary/config_ap6212.txt -O ${work_dir}/lib/firmware/ap6212/config.txt
cd "${base_dir}"

# Fix up the symlink for building external modules
# kernver is used so we don't need to keep track of what the current compiled
# version is
kernver=$(ls ${work_dir}/lib/modules/)
cd ${work_dir}/lib/modules/${kernver}
rm build
rm source
ln -s /usr/src/kernel build
ln -s /usr/src/kernel source
cd "${base_dir}"

# Calculate the space to create the image and create
make_image

# Create the disk partitions
status "Create the disk partitions"
parted -s "${image_dir}/${image_name}.img" mklabel msdos
parted -s "${image_dir}/${image_name}.img" mkpart primary ext2 4MiB "${bootsize}"MiB
parted -s -a minimal "${image_dir}/${image_name}.img" mkpart primary "$fstype" "${bootsize}"MiB 100%

# Set the partition variables
make_loop

# Create file systems
mkfs_partitions

# Make fstab.
make_fstab

# Create the dirs for the partitions and mount them
status "Create the dirs for the partitions and mount them"
mkdir -p "${base_dir}"/root
mount ${rootp} "${base_dir}"/root
mkdir -p "${base_dir}"/root/boot
mount ${bootp} "${base_dir}"/root/boot

echo "Rsyncing rootfs into image file"
rsync -HPavz -q ${work_dir}/ ${base_dir}/root/

# Samsung bootloaders must be signed
# These are the same steps that are done by
# https://github.com/friendlyarm/sd-fuse_nanopi2/blob/master/fusing.sh

# Download the latest prebuilt from the above url
mkdir -p "${base_dir}"/bootloader
cd "${base_dir}"/bootloader
wget 'https://github.com/friendlyarm/sd-fuse_nanopi2/blob/96e1ba9603d237d0169485801764c5ce9591bf5e/prebuilt/2ndboot.bin?raw=true' -O 2ndboot.bin
wget 'https://github.com/friendlyarm/sd-fuse_nanopi2/blob/96e1ba9603d237d0169485801764c5ce9591bf5e/prebuilt/boot.TBI?raw=true' -O boot.TBI
wget 'https://github.com/friendlyarm/sd-fuse_nanopi2/blob/96e1ba9603d237d0169485801764c5ce9591bf5e/prebuilt/bootloader' -O bootloader
#wget https://raw.githubusercontent.com/friendlyarm/sd-fuse_nanopi2/master/prebuilt/bl1-mmcboot.bin
#wget https://raw.githubusercontent.com/friendlyarm/sd-fuse_nanopi2/master/prebuilt/bl_mon.img
#wget https://raw.githubusercontent.com/friendlyarm/sd-fuse_nanopi2/master/prebuilt/bootloader.img # This is u-boot
#wget https://raw.githubusercontent.com/friendlyarm/sd-fuse_nanopi2/master/prebuilt/loader-mmc.img
wget https://raw.githubusercontent.com/friendlyarm/sd-fuse_nanopi2/master/tools/fw_printenv
chmod 0755 fw_printenv
ln -s fw_printenv fw_setenv

dd if=2ndboot.bin of=${loopdevice} bs=512 seek=1
dd if=boot.TBI of=${loopdevice} bs=512 seek=64 count=1
dd if=bootloader of=${loopdevice} bs=512 seek=65

cat <<EOF >${base_dir}/bootloader/env.conf
# U-Boot environment for Debian, Ubuntu
#
# Copyright (C) Guangzhou FriendlyARM Computer Tech. Co., Ltd
# (http://www.friendlyarm.com)
#

bootargs	console=ttyAMA0,115200n8 root=/dev/mmcblk0p2 rootfstype=$fstype rootwait rw consoleblank=0 net.ifnames=0
bootdelay	1
EOF

./fw_setenv ${loopdevice} -s env.conf

sync

cd "${repo_dir}/"

# Load default finish_image configs
include finish_image
