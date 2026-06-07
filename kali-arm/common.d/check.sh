#!/usr/bin/env bash

# Check EUID=0 you can run any binary as root.
if [[ $EUID -ne 0 ]]; then
    log "This script must be run as root or have super user permissions" red
    log "Use: ${colour_reset}sudo $0" green

    exit 1

fi

# Check for systemd-nspawn
if [ ! -e /usr/bin/systemd-nspawn ]; then
    log "Error: missing systemd-nspawn" red
    log "Please run ./common.d/build_deps.sh" red

    exit 1

fi

# Check for qemu-user
# Debian >= 13 (qemu-aarch64), Debian <= 12 (qemu-aarch64-static)
if [ ! -e /usr/bin/qemu-aarch64 ] && [ ! -e /usr/bin/qemu-aarch64-static ]; then
    log "Error: missing QEMU" red
    log "Please run ./commond.d/build_deps.sh" red

    exit 1

fi

# Check for the kali archive keyring
if [ ! -e /usr/share/keyrings/kali-archive-keyring.gpg ]; then
    log "Error: missing kali-archive-keyring" red
    log "Please download the latest version from" red
    log "https://kali.download/kali/pool/main/k/kali-archive-keyring" red
    log "and install it manually." red

    exit 1

fi

# Check exist bsp directory.
if [ ! -e "bsp" ]; then
    log "Error: missing bsp directory structure" red
    log "Please clone the full repository ${kaligit}/build-scripts/kali-arm" green

    exit 255

fi

# Check directory build
if [ -e "${base_dir}" ]; then
    log "${base_dir} directory exists, will not continue" red

    exit 1

elif [[ ${repo_dir} =~ [[:space:]] ]]; then
    log "The directory "\"${repo_dir}"\" contains whitespace. Not supported." red

    exit 1

else
    print_config
    mkdir -p ${base_dir}

fi

# Detect architecture
case ${architecture} in
    arm64)
        qemu_bin=$(find_qemu_static aarch64) || log "Failed to find QEMU: aarch64/arm64" red
        lib_arch="aarch64-linux-gnu" ;;

    armhf)
        qemu_bin=$(find_qemu_static arm) || log "Failed to find QEMU: arm/armhf" red
        lib_arch="arm-linux-gnueabihf" ;;

    armel)
        qemu_bin=$(find_qemu_static arm) || log "Failed to find QEMU: arm/armel" red
        lib_arch="arm-linux-gnueabi" ;;

esac

# Check systemd-nspawn version
nspawn_ver=$(systemd-nspawn --version | awk '{if(NR==1) print $2}')

if [[ $nspawn_ver -ge 245 ]]; then
    extra_args="--hostname=$hostname -q -P"

elif [[ $nspawn_ver -ge 241 ]]; then
    extra_args="--hostname=$hostname -q"

else
    extra_args="-q"

fi

# Check CPU cores to use
if [ "$cpu_cores" = "0" ]; then
    num_cores=$(nproc --all)

elif [[ "$cpu_cores" =~ ^[0-9]{1,2}$ ]]; then
    if [ "$cpu_cores" -le $(nproc --all) ]; then
        num_cores="$cpu_cores"

    else
        num_cores=$(nproc --all)

    fi

elif [[ "$cpu_cores" =~ ^[-0-9]{1,2}$ ]]; then
    num_cores=$(nproc --ignore="${cpu_cores/-/}")

else
    num_cores="1"

fi

# Automatic configuration to use an http proxy, such as apt-cacher-ng.
apt_cacher=${apt_cacher:-"$(lsof -i :3142 | cut -d ' ' -f3 | uniq | sed '/^\s*$/d')"}

if [ -n "$proxy_url" ]; then
    export http_proxy=$proxy_url

elif [[ "$apt_cacher" =~ (apt-cacher-ng|root) ]]; then
    if [ -z "$proxy_url" ]; then
        proxy_url=${proxy_url:-"http://127.0.0.1:3142/"}
        export http_proxy=$proxy_url

    fi

fi
