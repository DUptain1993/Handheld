#!/usr/bin/env bash
#
# Kali Linux ARM build-script (host machine preparation)
# https://gitlab.com/kalilinux/build-scripts/kali-arm
#

PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

# Stop on error
set -e

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

apt-wait() {
  while fuser /var/{lib/{dpkg,apt/lists},cache/apt/archives}/lock >/dev/null 2>&1; do
      sleep $[ ( $RANDOM % 15) + 5 ]
 
  done

    if [ "$1" == "update" ]; then
        echo -e "\n[i] Updating apt"
        apt-get update

    elif [ "$1" == "install_deps" ]; then
        echo -e "\n[i] Installing: $deps"
        apt-get install -y $deps

    # Don't think this is used?
    elif [ "$1" == "remove" ]; then
        echo -e "\n[i] Removing: $@"
        apt-get -y --purge "$@"

    else
        echo "\n[-] Unknown option: $1" >&2

        exit 1

    fi
}

# Function create script to clean system packages
clean_build() {
    mkdir -p ./local/
    clean_script=${backup_packages/list-pkgs/remove-pkgs}.sh

    echo -e "\n[i] Creating clean up script: ${clean_script}"
    cat <<EOF >${clean_script}
#!/usr/bin/env bash

set -e

if [[ \$EUID -ne 0 ]]; then
    echo "[-] This script must be run as root" >&2
    exit 1

fi

clean_system() {
    dpkg --clear-selections
    dpkg --set-selections < ${backup_packages}
    apt-get -y dselect-upgrade
    apt-get -y remove --purge \$(dpkg -l | grep "^rc" | awk '{print \$2}')
    ${del_arch_i386}
}

echo "Use this script under your responsibility"
read -p "Are you sure you want to remove the packages from the build? [y/N]: " yn
case \$yn in
    [Yy]* )
        clean_system ;;

    * )
        exit ;;
esac
EOF

    chmod 0755 ${clean_script}

    #rm -f "${backup_packages}"

    echo -e "\n[i] Need to manually run: ${clean_script}"
}

function check_trap() {
    echo -e "\n[-] An error has occurred!"
    clean_build

    exit 1
}

# If there is an issue, run the above function
trap check_trap INT ERR SIGTERM SIGINT

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# Check permissions script
if [[ $EUID -ne 0 ]]; then
    echo "[-] This script must be run as root" >&2

    exit 1

else
    echo -e "\n[i] Kali-ARM build-script machine preparation"

fi

# Check compatible systems
if ! which dpkg >/dev/null; then
    echo "[-] Script only compatible with Debian-based systems" >&2

    exit 1

fi

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# List of installed packages file
backup_packages=./local/build-deps-list-pkgs-$(date +"%Y-%m-%d-%H-%M")
mkdir -pv ./local/

# Create a current list of installed packages
dpkg --get-selections >${backup_packages}

# Update list deb packages
apt-wait update

# Check if crossbuild-essential-armel is available (not avail on Ubuntu)
if apt-cache show crossbuild-essential-armel >/dev/null 2>&1; then
    compilers="crossbuild-essential-arm64 crossbuild-essential-armhf crossbuild-essential-armel"
else
    compilers="crossbuild-essential-arm64 crossbuild-essential-armhf"
fi
compilers="${compilers} gcc-arm-none-eabi"

dependencies="arch-test autoconf automake bc binfmt-support bison build-essential ca-certificates cgpt  \
cgroup-tools cmake cpio curl dbus debootstrap device-tree-compiler dosfstools e2fsprogs eatmydata fdisk \
flex gawk git gnupg kpartx libgnutls28-dev libncurses-dev libssl-dev lsb-release lsof lzma lzop m4 make \
mmdebstrap parted pixz pkg-config python3-dev qemu-user qemu-user-binfmt rsync swig systemd-container   \
u-boot-tools uuid-dev vboot-kernel-utils vboot-utils wget xz-utils"
deps="${dependencies} ${compilers}"

# Install dependencies
apt-wait install_deps

DEB_VERSION=$(grep -oP 'VERSION_ID="\K[0-9]+' /etc/os-release 2>/dev/null)
if [ -z "${DEB_VERSION}" ]; then
    echo "[-] Unable to detect Debian version"
    exit 1
elif [ "${DEB_VERSION}" -le 12 ]; then
    echo "[i] Debian ${DEB_VERSION} detected"
    deps="qemu-user-static"
    apt-wait install_deps
fi

# Check minimum version debootstrap
debootstrap_ver=$(debootstrap --version | grep -o '[0-9.]\+' | head -1)

if dpkg --compare-versions "$debootstrap_ver" lt "1.0.105"; then
    echo "[-] Currently your version of debootstrap ($debootstrap_ver) does not support the script" >&2
    echo "[-] The minimum version of debootstrap is 1.0.105" >&2

    exit 1

fi

# Install kali-archive-keyring
if [ ! -f /usr/share/keyrings/kali-archive-keyring.gpg ]; then
    echo -e "\n[i] Installing: kali-archive-keyring"
    temp_key="$(mktemp -d)"
    git clone https://gitlab.com/kalilinux/packages/kali-archive-keyring.git $temp_key
    cd $temp_key/
    make
    cp -v kali-archive-keyring.gpg /usr/share/keyrings/ #make install
    cd $OLDPWD/
    rm -rf $temp_key

else
    echo -e "\n[i] Already have: kali-archive-keyring"

fi

# Install packages i386
if [ $(arch) == 'x86_64' ]; then
    echo -e "\n[i] Detected x64"

    if [ -z $(dpkg --print-foreign-architectures | grep i386) ]; then
        echo -e "\n[i] Adding x86 support"
        dpkg --add-architecture i386
        apt-wait update
        deps="-o APT::Immediate-Configure=0 libstdc++6:i386 libc6:i386 libgcc1:i386 zlib1g:i386 libncurses6:i386"
        apt-wait install_deps
        del_arch_i386="dpkg --remove-architecture i386"

    elif [[ $(dpkg --print-foreign-architectures | grep i386) == 'i386' ]]; then
        echo -e "\n[i] Already found x86 support"
        deps="-o APT::Immediate-Configure=0 libstdc++6:i386 libc6:i386 libgcc1:i386 zlib1g:i386 libncurses6:i386"
        apt-wait install_deps

    fi

elif [ $(arch) == 'i386' ]; then
    echo -e "\n[i] Detected x86"
    deps="libstdc++6 libc6 libgcc1 zlib1g libncurses5"
    apt-wait install_deps

fi

if [ -z "$(ls /proc/sys/fs/binfmt_misc/qemu-* 2>/dev/null)" ]; then
    echo "You need to reboot the system before you can build any images."
fi
# Create the script to clean the system
#clean_build
