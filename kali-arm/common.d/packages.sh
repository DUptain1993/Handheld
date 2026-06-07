#!/usr/bin/env bash

log "Selecting packages..." gray

debootstrap_base="kali-archive-keyring,eatmydata,usrmerge,ca-certificates"

# This is the bare minimum if you want to start from very scratch
minimal_pkgs="ca-certificates cloud-init haveged iw netplan.io network-manager \
parted rsyslog sudo wpasupplicant"

# This is the list of minimal common packages
common_min_pkgs="$minimal_pkgs apt-transport-https command-not-found \
fontconfig ifupdown kali-defaults kali-tweaks man-db net-tools netcat-traditional \
pciutils plocate psmisc rfkill screen snmp snmpd ssh-import-id tftp-hpa tmux unrar \
usbutils vim wireless-regdb zerofree zsh zsh-autosuggestions zsh-syntax-highlighting"

# This is the list of common packages
common_pkgs="$minimal_pkgs apt-transport-https dialog \
ifupdown inxi kali-linux-core kali-linux-firmware libnss-systemd man-db net-tools \
network-manager pciutils plocate psmisc rfkill screen snmp snmpd tftp-hpa \
triggerhappy usbutils whiptail zerofree"

services="apache2 atftpd openvpn ssh tightvncserver"

extra_custom_pkgs=""

# This is the list of most cli based tools
cli_tools_pkgs="kali-linux-headless"

# Desktop packages to install - default is specified after the desktop because
# we want to pull in the desktop's default terminal first instead of relying on
# something else to pull in x-terminal-emulator from the defaults.
# The texlive packages cause the build to take 4x as long, so we pass the
# package name with a - in order to tell apt-get to *not* install them.
case $desktop in
    xfce | gnome | kde | i3 | lxde | mate | e17)
        desktop_pkgs="kali-desktop-$desktop kali-linux-default alsa-utils \
        xfonts-terminus xinput xserver-xorg-video-fbdev xserver-xorg-input-libinput" ;;

    none | slim | miminal)
        variant="minimal"; minimal="1"; desktop_pkgs="" ;;

esac

# Installed kernel sources when using a kernel that isn't packaged.
custom_kernel_pkgs="bc bison libssl-dev"

rpi_pkgs="kali-sbc-raspberrypi"

# Add swap packages
if [ "$swap" = yes ]; then
    minimal_pkgs+=" dphys-swapfile"

fi

extra="$custom_kernel_pkgs"

# add extra_custom_pkgs, that can be a global variable
packages="$common_pkgs $cli_tools_pkgs $services $extra_custom_pkgs"

# Do not add re4son_pkgs to this list, as we do not have his repo added when these are installed
if [[ "$hw_model" == *raspberrypi* ]]; then
    extra+="$rpi_pkgs"

fi

if [ "$minimal" = "1" ]; then
    image_mode="minimal"

    if [ "$slim" = "1" ]; then
        image_mode="slim"
        packages="$common_min_pkgs ssh"

    else
        packages="$common_min_pkgs $services $extra_custom_pkgs"

    fi

    log "Selecting $image_mode mode..." gray

fi

# Basic packages third stage
third_stage_pkgs="binutils ca-certificates console-common console-setup curl \
git libterm-readline-gnu-perl locales wget"

# Re4son packages
re4son_pkgs="kalipi-bootloader kalipi-config kalipi-kernel kalipi-kernel-headers \
kalipi-re4son-firmware kalipi-tft-config pi-bluetooth"

# Pi-Tail specific packages
pitail_pkgs="bluelog blueranger bluesnarfer bluez-tools bridge-utils cmake \
darkstat dnsmasq htop isc-dhcp-client libusb-1.0-0-dev locate mailutils \
pure-ftpd tightvncpasswd tigervnc-standalone-server wifiphisher"
