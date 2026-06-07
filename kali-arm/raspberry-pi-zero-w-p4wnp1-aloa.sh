#!/usr/bin/env bash
#
# Kali Linux ARM build-script for Raspberry Pi Zero W (P4wnP1 A.L.O.A.) (32-bit)
# Source: https://gitlab.com/kalilinux/build-scripts/kali-arm
#
# This is a community script - you will need to generate your own image to use
# More information: https://www.kali.org/docs/arm/raspberry-pi-zero-w-p4wnp1-aloa/
#
# Due to the nexmon firmware's age, there is a lack of recognizing arm64.
# This script cannot be run on an arm64 host.

# Hardware model
hw_model=${hw_model:-"raspberry-pi-zero-w-p4wnp1-aloa"}

# Architecture
architecture=${architecture:-"armel"}

# Desktop manager (xfce, gnome, i3, kde, lxde, mate, e17 or none)
desktop=${desktop:-"none"}

# Load default base_image configs
source ./common.d/base_image.sh

# Network configs
basic_network
#add_interface eth0

# move P4wnP1 in (change to release blob when ready)
git clone -b 'master' --single-branch --depth 1 https://github.com/rogandawes/P4wnP1_aloa "${work_dir}"/root/P4wnP1

# Third stage
cat <<EOF >>"${work_dir}"/third-stage
status_stage3 'Copy rpi services'
cp -p /bsp/services/rpi/*.service /etc/systemd/system/

status_stage3 'Script mode wlan monitor START/STOP'
install -m755 /bsp/scripts/monstart /usr/bin/
install -m755 /bsp/scripts/monstop /usr/bin/

# haveged: assure enough entropy data for hostapd on startup
# avahi-daemon: allow mDNS resolution (apple bonjour) by remote hosts
# dhcpcd5: REQUIRED (P4wnP1 A.L.O.A. currently wraps this binary if a DHCP client is needed)
# dnsmasq: REQUIRED (P4wnP1 A.L.O.A. currently wraps this binary if a DHCP server is needed, currently not used for DNS)
# dosfstools: contains fatlabel (used to label FAT32 iamges for UMS)
# genisoimage: allow creation of CD-Rom iso images for CD-Rom USB gadget from existing folders on the fly
# iodine: allow DNS tunneling
status_stage3 'Install needed packages for P4wnp1 A.L.O.A'
eatmydata apt-get install -y apache2 atftpd autossh avahi-daemon bash-completion bluez bluez-firmware build-essential dhcpcd5 dnsmasq dosfstools fake-hwclock genisoimage golang haveged hostapd i2c-tools iodine openssh-server openvpn pi-bluetooth policykit-1 python3-configobj python3-dev python3-pip python3-requests python3-smbus wpasupplicant

status_stage3 'Remove NetworkManager'
eatmydata apt-get purge -y network-manager

status_stage3 'Enabling ssh by putting ssh or ssh.txt file in /boot'
systemctl enable enable-ssh

status_stage3 'Fixup wireless-regdb signature'
update-alternatives --set regulatory.db /lib/firmware/regulatory.db-upstream

status_stage3 'Enable hciuart and bluetooth'
systemctl enable hciuart
systemctl enable bluetooth

status_stage3 'Set root password to toor'
echo "root:toor" | chpasswd

status_stage3 'Remove persistent net rules file'
rm -f /etc/udev/rules.d/70-persistent-net.rules

status_stage3 'Allow root to ssh in'
sed -i -e 's/^#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

status_stage3 'Disable dhcpcd'
# dhcpcd is needed by P4wnP1, but started on demand
# installation of dhcpcd5 package enables a systemd unit starting dhcpcd for all
# interfaces, which results in conflicts with DHCP servers running on created
# bridge interface (especially for the bteth BNEP bridge). To avoid this we
# disable the service. If communication problems occur, although DHCP leases
# are handed out by dnsmasq, dhcpcd should be the first place to look
# (no interface should hava an APIPA addr assigned, unless the DHCP client
# was explcitely enabled by P4wnP1 for this interface)
systemctl disable dhcpcd

status_stage3 'Copy config.txt into place'
# Copy a default config, with everything commented out so people find it when
# they go to add something when they are following instructions on a website
cp /bsp/firmware/rpi/config.txt /boot/config.txt

status_stage3 'Run P4wnP1 A.L.O.A installer'
cd /root/P4wnP1
# This is one case where we actually want the pip install to be system wide.
sed -i -e 's/pip install/pip install --break-system-packages/' Makefile
make installkali

status_stage3 'Enable dwc2 module'
echo "dwc2" | tee -a /etc/modules

status_stage3 'Enable root login over ttyGS0'
echo ttyGS0 >> /etc/securetty

status_stage3 'Add cronjob to update fake-hwclock'
echo '* * * * * root /usr/sbin/fake-hwclock' >> /etc/crontab

status_stage3 'Create rc.local to remove kernel output on the console'
echo "#!/bin/sh -e" > /etc/rc.local
echo "dmesg -D" >> /etc/rc.local
echo "exit 0" >> /etc/rc.local
chmod +x /etc/rc.local

# Despite the name, all this does is disable root login over ssh
# which we want to enable on this image.
status_stage3 'Remove ssh key check'
rm /etc/runonce.d/03-check-ssh-keys

# Copy in bluetooth overrides
status_stage3 'Add systemd service overrides for bluetooth'
cp -a /bsp/overrides/* /etc/systemd/system/

# Create spi and gpio groups
status_stage3 'Add spi and gpio groups'
groupadd -f -r spi
groupadd -f -r gpio

# We don't care about console font on this image.
status_stage3 'Disable console-setup service'
systemctl disable console-setup
EOF

# Run third stage
include third_stage

cd "${base_dir}"

status 'Clone bootloader and firmware'
git clone -b 1.20181112 --depth 1 https://github.com/raspberrypi/firmware.git "${work_dir}"/rpi-firmware
cp -rf "${work_dir}"/rpi-firmware/boot/* "${work_dir}"/boot/

# Copy over Pi specific libs (video core) and binaries (dtoverlay,dtparam...)
cp -rf "${work_dir}"/rpi-firmware/opt/* "${work_dir}"/opt/
rm -rf "${work_dir}"/rpi-firmware

status 'Clone nexmon firmware'
cd "${base_dir}"
git clone https://github.com/mame82/nexmon_wifi_covert_channel.git -b p4wnp1 "${base_dir}"/nexmon --depth 1

status 'Clone and build kernel'
cd "${base_dir}"

# Re4son kernel 4.14.80 with P4wnP1 patches (dwc2 and brcmfmac)
git clone --depth 1 https://github.com/Re4son/re4son-raspberrypi-linux -b rpi-4.14.80-re4son-p4wnp1 "${work_dir}"/usr/src/kernel

cd "${work_dir}"/usr/src/kernel

# Remove redundant yyloc global declaration
patch -p1 --no-backup-if-mismatch <"${repo_dir}"/patches/11647f99b4de6bc460e106e876f72fc7af3e54a6.patch

# Note: Compiling the kernel in /usr/src/kernel of the target file system is problematic, as the binaries of the compiling host architecture
# get deployed to the /usr/src/kernel/scripts subfolder (in this case linux-x64 binaries), which is symlinked to /usr/src/build later on
# This would f.e. hinder rebuilding single modules, like nexmon's brcmfmac driver, on the Pi itself (online compilation)
# The cause:building of modules relies on the pre-built binaries in /usr/src/build folder. But the helper binaries are compiled with the
# HOST toolchain and not with the crosscompiler toolchain (f.e. /usr/src/kernel/script/basic/fixdep would end up as x64 binary, as this helper
# is not compiled with the CROSS toolchain). As those scripts are used druing module build, it wouldn't work to build on the pi, later on,
# without recompiling the helper binaries with the proper crosscompiler toolchain
#
# To account for that, the 'script' subfolder could be rebuild on the target (online) by running `make scripts/` from /usr/src/kernel folder
# Rebuilding the script, again, depends on additional tooling, like `bc` binary, which has to be installed
#
# Currently the step of recompiling the kernel/scripts folder has to be done manually online, but it should be possible to do it after kernel
# build, by setting the host compiler (CC) to the gcc of the linaro-arm-linux-gnueabihf-raspbian-x64 toolchain (not only the CROSS_COMPILE)
# The problem is, that the used linaro toolchain builds for armhf (not a problem for kernel, as there're no dependencies on hf librearies),
# but the debian packages (and the provided gcc) are armel
#
# To clean up this whole "armel" vs "armhf" mess, the kernel should be compiled with a armel toolchain (best choice would be the toolchain
# which is used to build the kali armel packages itself, which is hopefully available for linux-x64)
#
# For now this is left as manual step, as the normal user shouldn't have a need to recompile kernel parts on the Pi itself

# Set default defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- re4son_pi1_defconfig

# Build kernel
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j$(nproc)

# Make kernel modules
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- modules_install INSTALL_MOD_PATH="${work_dir}"

# Copy kernel to boot
perl scripts/mkknlimg --dtok arch/arm/boot/zImage "${work_dir}"/boot/kernel.img
cp arch/arm/boot/dts/*.dtb "${work_dir}"/boot/
cp arch/arm/boot/dts/overlays/*.dtb* "${work_dir}"/boot/overlays/
cp arch/arm/boot/dts/overlays/README "${work_dir}"/boot/overlays/

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- mrproper
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- re4son_pi1_defconfig

# Fix up the symlink for building external modules
# kernver is used so we don't need to keep track of what the current compiled
# version is
kernver=$(ls "${work_dir}"/lib/modules/)
cd "${work_dir}"/lib/modules/"${kernver}"
rm build
rm source
ln -s /usr/src/kernel build
ln -s /usr/src/kernel source
cd "${base_dir}"

# git clone of nexmon moved in front of kernel compilation, to have poper brcmfmac driver ready
status 'Build nexmon firmware'
cd "${base_dir}"/nexmon

# Make sure we're not still using the armel cross compiler
unset CROSS_COMPILE

# Disable statistics
touch DISABLE_STATISTICS
source setup_env.sh
make
cd buildtools/isl-0.10
CC=$CCgcc
./configure
make
sed -i -e 's/all:.*/all: $(RAM_FILE)/g' "${NEXMON_ROOT}"/patches/bcm43430a1/7_45_41_46/nexmon/Makefile
cd "${NEXMON_ROOT}"/patches/bcm43430a1/7_45_41_46/nexmon
make clean

# We do this so we don't have to install the ancient isl version into /usr/local/lib on systems
LD_LIBRARY_PATH="${NEXMON_ROOT}/buildtools/isl-0.10/.libs" make ARCH=arm CC="${NEXMON_ROOT}/buildtools/gcc-arm-none-eabi-5_4-2016q2-linux-x86/bin/arm-none-eabi-"

# RPi0w->3B firmware
# disable nexmon by default
mkdir -p "${work_dir}"/lib/firmware/brcm
cp "${NEXMON_ROOT}/patches/bcm43430a1/7_45_41_46/nexmon/brcmfmac43430-sdio.bin" "${work_dir}"/lib/firmware/brcm/brcmfmac43430-sdio.nexmon.bin
cp "${NEXMON_ROOT}/patches/bcm43430a1/7_45_41_46/nexmon/brcmfmac43430-sdio.bin" "${work_dir}"/lib/firmware/brcm/brcmfmac43430-sdio.bin
wget https://raw.githubusercontent.com/RPi-Distro/firmware-nonfree/master/brcm/brcmfmac43430-sdio.txt -O "${work_dir}"/lib/firmware/brcm/brcmfmac43430-sdio.txt

# Make a backup copy of the rpi firmware in case people don't want to use the nexmon firmware
# The firmware used on the RPi is not the same firmware that is in the firmware-brcm package which is why we do this
wget https://raw.githubusercontent.com/RPi-Distro/firmware-nonfree/master/brcm/brcmfmac43430-sdio.bin -O "${work_dir}"/lib/firmware/brcm/brcmfmac43430-sdio.rpi.bin

# Set hostname
status 'Set hostname'
echo "${hostname}" >"${work_dir}"/etc/hostname

cd "${repo_dir}/"

# Clean system
include clean_system

# Calculate the space to create the image and create
make_image

# Create the disk partitions
status "Create the disk partitions"
parted -s "${image_dir}/${image_name}.img" mklabel msdos
parted -s "${image_dir}/${image_name}.img" mkpart primary fat32 4MiB "${bootsize}"MiB
parted -s -a minimal "${image_dir}/${image_name}.img" mkpart primary "$fstype" "${bootsize}"MiB 100%

# Set the partition variables
make_loop

# Create file systems
mkfs_partitions

# Make fstab,
make_fstab

# Configure Raspberry Pi firmware
include rpi_firmware

# Create the dirs for the partitions and mount them
status "Create the dirs for the partitions and mount them"
mkdir -p "${base_dir}"/root/

if [[ $fstype == ext4 ]]; then
    mount -t ext4 -o noatime,data=writeback,barrier=0 "${rootp}" "${base_dir}"/root

else
    mount "${rootp}" "${base_dir}"/root

fi

mkdir -p "${base_dir}"/root/boot
mount "${bootp}" "${base_dir}"/root/boot

status "Rsyncing rootfs into image file"
rsync -HPavz -q --exclude boot "${work_dir}"/ "${base_dir}"/root/
sync

status "Rsyncing rootfs into image file (/boot)"
rsync -rtx -q "${work_dir}"/boot "${base_dir}"/root
sync

# Finally, enable dwc2 for udc gadgets
status 'Enable dwc2'
echo "dtoverlay=dwc2" >>"${base_dir}"/root/boot/config.txt
sed -i -e 's/net.ifnames=0/net.ifnames=0 modules-load=dwc2/' "${base_dir}"/root/boot/cmdline.txt

# Load default finish_image configs
include finish_image
