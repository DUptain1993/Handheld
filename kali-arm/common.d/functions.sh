#!/usr/bin/env bash
# shellcheck disable=SC2154

# fallback TERM if not set or set to something too basic
if [[ -z "$TERM" || "$TERM" == "dumb" || "$TERM" == "vt220" ]]; then
    export TERM="xterm-256color"
fi

# Print color echo
function log() {
    local set_color="$2"
    color=""

    case $set_color in
        bold)
            color=$(tput bold) ;;

        red)
            color=$(tput setaf 1) ;;

        green)
            color=$(tput setaf 2) ;;

        yellow)
            color=$(tput setaf 3) ;;

        cyan)
            color=$(tput setaf 6) ;;

        gray)
            color=$(tput setaf 8) ;;

        white)
            color=$(tput setaf 15) ;;

    esac

    ## --no-color
    if [ "$colour_output" == "no" ] || [ -z "$color" ]; then
        echo -e "[i] $1"

    else
        echo -e "${color[i]} $1${colour_reset}"

    fi
}

# Usage function
function usage() {
    log "Usage commands:" bold

    cat <<EOF
    # Architectures (arm64, armel, armhf)
    $0 --arch arm64 or $0 -a armhf

    # Desktop manager (xfce, gnome, kde, i3, lxde, mate, e17 or none)
    $0 --desktop kde or $0 --desktop=kde

    # Minimal image - no desktop manager (alias to --desktop=none)
    $0 --minimal or $0 -m

    # Slim image - no desktop manager & no Kali tools
    $0 --slim or $0 -s

    # Enable debug & log file (./logs/<file>.log)
    $0 --debug or $0 -d

    # Perform extra checks on the images build
    $0 --extra or $0 -x

    # Remove color from output
    $0 --no-color or $0 --no-colour

    # Help screen (this)
    $0 --help or $0 -h
EOF

    exit 0
}

# Debug function
function debug_enable() {
    currentdir="${0##*/}"
    basenamedir="${currentdir%.*}"
    log="./logs/${basenamedir}_$(date +"%Y-%m-%d-%H-%M").log"
    mkdir -p ./logs/
    log "Debug: Enabled" green
    log "Output: ${log}" green
    # Pipe output to both console and log, but strip ANSI codes from log
    exec > >(tee -a >(sed 's/\x1B\[[0-9;]*[mK]//g' >> "${log}")) 2>&1

    # Print all commands inside of script
    set -x
    debug=1
    extra=1
}

# Validate desktop
function validate_desktop() {
    case $1 in
        xfce | gnome | kde | i3 | lxde | mate | e17)
            true ;;

        none)
            variant="minimal" ;;

        *)
            log "⚠️ Unknown desktop:${colour_reset} $1\n" red; usage ;;

    esac
}

# Arguments function
function arguments() {
    while [[ $# -gt 0 ]]; do
        opt="$1"

        shift

        case "$(echo ${opt} | tr '[:upper:]' '[:lower:]')" in
            "--")
                break 2 ;;

            -a | --arch)
                architecture="$1"; shift ;;

            --arch=*)
                architecture="${opt#*=}" ;;

            --desktop)
                validate_desktop $1; desktop="$1"; shift ;;

            --desktop=*)
                validate_desktop "${opt#*=}"; desktop="${opt#*=}" ;;

            -m | --minimal)
                variant="minimal"; minimal="1"; desktop="minimal" ;;

            -s | --slim)
                variant="slim"; desktop="slim"; minimal="1"; slim="1" ;;

            -d | --debug)
                debug_enable ;;

            -x | --extra)
                log "Extra Checks: Enabled" green; extra="1" ;;

            --no-color | --no-colour)
                colour_output="no";
                colour_reset="";
                log "Disabling color output" green ;;

            -h | -help | --help)
                usage ;;

            *)
                log "Unknown option: ${opt}" red; exit 1 ;;

        esac
    done
}

# Function to include common files
function include() {
    local file="$1"

    if [[ -f "common.d/${file}.sh" ]]; then
        log "✅ Load common file:${colour_reset} ${file}" green

        # shellcheck source=/dev/null
        source "common.d/${file}.sh" "$@"
        return 0

    else
        log "⚠️ Fail to load ${file} file" red

        [ "${debug}" = 1 ] && pwd || true

        exit 1

    fi
}

# systemd-nspawn environment
# Putting quotes around $extra_args causes systemd-nspawn to pass the extra arguments as 1, so leave it unquoted.
# This is left in for legacy/community scripts which call it directly until someone moves them to the new way
function systemd-nspawn_exec() {
    log "systemd-nspawn $*" gray
    ENV1="RUNLEVEL=1"
    ENV2="LANG=C"
    ENV3="DEBIAN_FRONTEND=noninteractive"
    ENV4="DEBCONF_NOWARNINGS=yes"
    # Jenkins server doesn't have this??
    if [ ${architecture} == "arm64" ]; then
    #ENV5="QEMU_CPU=max,pauth-impdef=on"
    ENV5="QEMU_CPU=cortex-a72"
    fi

    if [ "$(arch)" != "aarch64" ]; then
        # Ensure we export QEMU_CPU so its set for systemd-nspawn to use
        if [ ${architecture} == "arm64" ]; then
          #export QEMU_CPU=max,pauth-impdef=on
          export QEMU_CPU=cortex-a72
          systemd-nspawn --bind-ro "$qemu_bin" $extra_args --capability=cap_setfcap -E $ENV1 -E $ENV2 -E $ENV3 -E $ENV4 -E $ENV5 -M "$machine" -D "${work_dir}" "$@"
        else
          systemd-nspawn --bind-ro "$qemu_bin" $extra_args --capability=cap_setfcap -E $ENV1 -E $ENV2 -E $ENV3 -E $ENV4 -M "$machine" -D "${work_dir}" "$@"
        fi
    else
        systemd-nspawn $extra_args --capability=cap_setfcap -E $ENV1 -E $ENV2 -E $ENV3 -E $ENV4 -M "$machine" -D "${work_dir}" "$@"
    fi
}

# chroot environment
function chroot_exec() {
    log "chroot $*" gray

    # Define environment variables
    ENV_VARS="RUNLEVEL=1 LANG=C DEBIAN_FRONTEND=noninteractive DEBCONF_NOWARNINGS=yes"
    [ "${architecture}" == "arm64" ] && ENV_VARS="$ENV_VARS QEMU_CPU=cortex-a72"

    # Ensure /proc is mounted inside chroot
    mount --types proc /proc "${work_dir}/proc"

    # Determine whether to use QEMU (only if we're cross-emulating ARM64)
    if [ "$(arch)" != "aarch64" ] && [ "${architecture}" == "arm64" ]; then
        USE_QEMU="$qemu_bin"

        # Copy QEMU binary into chroot if it’s missing
        if [ ! -f "${work_dir}${qemu_bin}" ]; then
            cp "$qemu_bin" "${work_dir}${qemu_bin}"
            chmod +x "${work_dir}${qemu_bin}"
        fi
    fi

    # Run chroot, using QEMU only if needed
    chroot "${work_dir}" /bin/bash -c "exec env $ENV_VARS ${*:-/bin/bash}" < /dev/stdin

    # Cleanup: Unmount /proc
    umount -lf "${work_dir}/proc"
}

# Create the rootfs - not much to modify here, except maybe throw in some more packages if you want.
function debootstrap_exec() {
    status "debootstrap ${suite} $*"

    if [ "$(lsb_release -sc)" == "bullseye" ]; then
    eatmydata debootstrap --merged-usr --keyring=/usr/share/keyrings/kali-archive-keyring.gpg --components="${components}" \
        --include="${debootstrap_base}" --arch "${architecture}" "${suite}" "${work_dir}" "$@"
    else
    eatmydata mmdebstrap --keyring=/usr/share/keyrings/kali-archive-keyring.gpg --components="${components}" \
        --include="${debootstrap_base}" --arch "${architecture}" "${suite}" "${work_dir}" "$@"
    fi
}

# Disable the use of http proxy in case it is enabled.
function disable_proxy() {
    if [ -n "$proxy_url" ]; then
        log "Disable proxy" gray
        unset http_proxy
        rm -rf "${work_dir}"/etc/apt/apt.conf.d/66proxy

    elif [ "${debug}" = 1 ]; then
        log "Proxy enabled" yellow

    fi
}

# Mirror & suite replacement
function restore_mirror() {
    local default_mirror="http://http.kali.org/kali"
    local default_suite="kali-rolling"

    # Respect environment variables, allow overrides via replace_*
    local mirror="${mirror:-$default_mirror}"
    local suite="${suite:-$default_suite}"

    if [[ -n "${replace_mirror}" ]]; then
        mirror="${replace_mirror}"
    fi

    if [[ -n "${replace_suite}" ]]; then
        suite="${replace_suite}"
    fi

    log "Setting APT sources to mirror: ${mirror%/}/, suite: ${suite}" gray

    cat <<EOF >"${work_dir}/etc/apt/sources.list.d/kali.sources"
# See https://www.kali.org/docs/general-use/kali-apt-sources/
Types: deb
URIs: ${mirror%/}/
Suites: ${suite}
Components: main contrib non-free non-free-firmware
Signed-By: /usr/share/keyrings/kali-archive-keyring.gpg
EOF
}

# Limit CPU function
function limit_cpu() {
    if [[ ${cpu_limit:=} -lt "1" ]]; then
        cpu_limit=-1
        log "CPU limiting has been disabled" yellow
        eval "${@}"
        return $?
    elif [[ ${cpu_limit:=} -gt "100" ]]; then
        log "CPU limit (${cpu_limit}) is higher than 100" yellow
        cpu_limit=100
    fi

    if [[ -z $cpu_limit ]]; then
        log "CPU limit unset" yellow
        local cpu_shares=$((num_cores * 1024))
        local cpu_quota="-1"
    else
        log "Limiting CPU (${cpu_limit}%)" yellow
        local cpu_shares=$((1024 * num_cores * cpu_limit / 100))  # 1024 max value per core
        local cpu_quota=$((100000 * num_cores * cpu_limit / 100)) # 100000 max value per core
    fi

    local rand
    rand=$(
        tr -cd 'A-Za-z0-9' </dev/urandom | head -c4
        echo
    )

    cgcreate -g cpu:/cpulimit-"$rand"
    cgset -r cpu.shares="$cpu_shares" cpulimit-"$rand"
    cgset -r cpu.cfs_quota_us="$cpu_quota" cpulimit-"$rand"

    local n=1
    local max=5
    local delay=2
    local exit_code=1

    while true; do
        cgexec -g cpu:cpulimit-"$rand" "$@"
        exit_code=$?

        if [[ $exit_code -eq 0 ]]; then
            break
        elif [[ $n -lt $max ]]; then
            ((n++))
            log "Command failed. Attempt $n/$max" red
            sleep $delay
        else
            log "The command has failed after $n attempts" yellow
            break
        fi
    done

    cgdelete -g cpu:/cpulimit-"$rand"
    return $exit_code
}

function kali_sources() {
    # Define kali.sources
    log "✅ define kali.sources" green
    cat <<EOF >"${work_dir}"/etc/apt/sources.list.d/kali.sources
# See https://www.kali.org/docs/general-use/kali-apt-sources/
Types: deb
URIs: ${mirror%/}/
Suites: ${suite}
Components: ${components//,/ }
Signed-By: /usr/share/keyrings/kali-archive-keyring.gpg
EOF
    # Remove sources.list if any
    if [ -e "${work_dir}"/etc/apt/sources.list ]; then
        log "✅ remove sources.list" green
        rm -f "${work_dir}"/etc/apt/sources.list
    fi
}

# Choose a locale
function set_locale() {
    LOCALES="$1"

    log "locale:${colour_reset} ${LOCALES}" gray
    sed -i "s/^# *\($LOCALES\)/\1/" "${work_dir}"/etc/locale.gen

    #systemd-nspawn_exec locale-gen
    echo "LANG=$LOCALES" >"${work_dir}"/etc/locale.conf
    echo "LC_ALL=$LOCALES" >>"${work_dir}"/etc/locale.conf

    cat <<'EOM' >"${work_dir}"/etc/profile.d/default-lang.sh
if [ -z "$LANG" ]; then
    source /etc/locale.conf
    export LANG
elif [ -z "$LC_ALL" ]; then
    source /etc/locale.conf
    export LC_ALL
fi
EOM
}

# Set hostname
function set_hostname() {
    if [[ "$1" =~ ^[a-zA-Z0-9-]{2,63}+$ ]]; then
        log "Created /etc/hostname" white
        echo "$1" >"${work_dir}"/etc/hostname

    else
        log "$1 is not a correct hostname" red
        log "Using kali to default hostname" bold
        echo "kali" >"${work_dir}"/etc/hostname

    fi
}

# Add network interface
function add_interface() {
    interfaces="$*"
    for netdev in $interfaces; do
        cat <<EOF >"${work_dir}"/etc/network/interfaces.d/"$netdev"
auto $netdev
    allow-hotplug $netdev
    iface $netdev inet dhcp
EOF

        log "Configured /etc/network/interfaces.d/$netdev" white

    done
}

function basic_network() {
    # Disable IPv6
    if [ "$disable_ipv6" = "yes" ]; then
        log "Disable IPv6" white

        echo "# Don't load ipv6 by default" >"${work_dir}"/etc/modprobe.d/ipv6.conf
        echo "alias net-pf-10 off" >>"${work_dir}"/etc/modprobe.d/ipv6.conf
    fi

    cat <<EOF >"${work_dir}"/etc/network/interfaces
source-directory /etc/network/interfaces.d

auto lo
  iface lo inet loopback

EOF
    make_hosts
}

function make_hosts() {
    set_hostname "${hostname}"

    log "Created /etc/hosts" white
    cat <<EOF >"${work_dir}"/etc/hosts
127.0.1.1       ${hostname:=}
127.0.0.1       localhost
::1             localhost ip6-localhost ip6-loopback
fe00::0         ip6-localnet
ff00::0         ip6-mcastprefix
ff02::1         ip6-allnodes
ff02::2         ip6-allrouters
EOF
}

# Make SWAP
function make_swap() {
    if [ "$swap" = yes ]; then
        log "Make swap" green
        echo 'vm.swappiness = 50' >>"${work_dir}"/etc/sysctl.conf

        #sed -i 's/#CONF_SWAPSIZE=/CONF_SWAPSIZE=128/g' ${work_dir}/etc/dphys-swapfile

    else
        [[ -f ${work_dir}/swapfile.img ]] || log "Make Swap:${colour_reset} Disabled" yellow

    fi
}

# Print current config.
function print_config() {
    name_model="$(sed -n '3'p $0)"

    log "Compilation info" bold
    log "  Hardware model: ${colour_reset}${name_model#* for }" cyan
    log "  Architecture: ${colour_reset}$architecture" cyan
    log "  OS build: ${colour_reset}$suite $version" cyan
    log "  Desktop manager: ${colour_reset}$desktop" cyan
    log "  The base_dir thinks it is: ${colour_reset}${base_dir}" cyan
}

# Calculate the space to create the image and create.
function make_image() {
    # Calculate the space to create the image.
    root_size=$(du -s -B1 "${work_dir}" --exclude="${work_dir}"/boot | cut -f1)
    root_extra=$((root_size / 1000))
    raw_size=$(( (root_size / 1024) + (free_space * 1024) + (root_extra / 1024)  + (bootsize * 1024) + 4))
    padding=$(( (512 - (raw_size % 512)) % 512 ))
    padded_size=$(( raw_size + padding ))
    img_size=$(echo "${padded_size}"Ki | numfmt --from=iec-i --to=si)

    # Create the disk image
    log "Creating image file:${colour_reset} ${image_name}.img (Size: ${img_size})" white
    [ -d "${image_dir}" ] || mkdir -p "${image_dir}/"
    fallocate -l "${padded_size}"K "${image_dir}/${image_name}.img"
}

# Make sure that the loopdevice is available.
function ensure_loopdevice() {
    local img_file="$1"
    local loopdev
    local retry_attempts=5  # Number of retry attempts
    local retry_interval=1  # Time in seconds between retries
    for attempt in $(seq 1 "$retry_attempts"); do
        loopdev=$(losetup --show -fP "$img_file")
        # Add a sleep to let the devices settle
        sleep 3
        if [ -b "${loopdev}" ]; then
            # The echo below is intentional and crucial. It ensures the function outputs
            # the loop device path (e.g., /dev/loop0) as its return value.
            # Do NOT remove or replace it with a log statement, as other parts of the script
            # rely on this output to use the loop device.
            echo ${loopdev}
            return 0
        fi
        log "Retrying to set up loop device (attempt $attempt)..."
        sleep "$retry_interval"
    done
    log "Failed to set up loop device for $img after $retry_attempts attempts."
    return 1
}

# Set the partition variables
function make_loop() {
    img="${image_dir}/${image_name}.img"
    num_parts=$(fdisk -l "$img" | grep -c "${img}[1-2]")

    if [ "$num_parts" = "2" ]; then
        extra=1
        part_type1=$(fdisk -l "$img" | grep "${img}"1 | awk '{print $6}')
        part_type2=$(fdisk -l "$img" | grep "${img}"2 | awk '{print $6}')

        if [[ "$part_type1" == "c" ]]; then
            bootfstype="vfat"

        elif [[ "$part_type1" == "83" ]]; then
            bootfstype=${bootfstype:-"$fstype"}

        fi

        if [[ "$bootfstype" == "vfat" ]]; then
            boot_uuid_n="$(cat < /proc/sys/kernel/random/uuid | cut -d- -f2-3)"
            boot_uuid="$(echo "$boot_uuid_n" | tr '[:lower:]' '[:upper:]')"
            boot_uuid_n="$(echo "$boot_uuid_n" | tr -d -)"
        else
            boot_uuid="$(cat < /proc/sys/kernel/random/uuid)"
        fi

        rootfstype=${rootfstype:-"$fstype"}
        loopdevice=$(ensure_loopdevice "$img")
        bootp="${loopdevice}p1"
        rootp="${loopdevice}p2"

    elif [ "$num_parts" = "1" ]; then
        part_type1=$(fdisk -l "$img" | grep "${img}"1 | awk '{print $6}')

        if [[ "$part_type1" == "83" ]]; then
            rootfstype=${rootfstype:-"$fstype"}

        fi

        rootfstype=${rootfstype:-"$fstype"}
        loopdevice=$(ensure_loopdevice "$img")
        rootp="${loopdevice}p1"

    fi
}

# Create fstab file.
function make_fstab() {
    status "Create /etc/fstab"
    cat <<EOF >"${work_dir}"/etc/fstab
# <file system> <mount point>   <type>  <options>       <dump>  <pass>
proc            /proc           proc    defaults          0       0

UUID=$root_uuid /               $rootfstype errors=remount-ro 0       1
EOF

    if ! [ -z "$bootp" ]; then
        echo "UUID=$boot_uuid      /boot           $bootfstype    defaults          0       2" >>"${work_dir}"/etc/fstab

    fi

    make_swap

    if [ -f "${work_dir}/swapfile.img" ]; then
        cat <<EOF >>${work_dir}/etc/fstab
/swapfile.img   none            swap    sw                0       0
EOF

    fi
}

# Create file systems
function mkfs_partitions() {
    status "Formatting partitions"
    # Formatting boot partition.
    if [ -n "${bootp}" ]; then
        case $bootfstype in
            vfat)
                mkfs.vfat -i "$boot_uuid_n" -n BOOT -F 32 "${bootp}" ;;

            ext4)
                features="^64bit,^metadata_csum";
                mkfs -U "$boot_uuid" -O "$features" -t "$fstype" -L BOOT "${bootp}" ;;

            ext2 | ext3)
                features="^64bit"
                mkfs -U "$boot_uuid" -O "$features" -t "$fstype" -L BOOT "${bootp}" ;;

        esac

        bootfstype=$(blkid -o value -s TYPE $bootp)

    fi

    # Formatting root partition.
    if [ -n "${rootp}" ]; then
        case $rootfstype in
            ext4)
                features="^64bit,^metadata_csum" ;;

            ext2 | ext3)
                features="^64bit" ;;

        esac

        yes | mkfs -U "$root_uuid" -O "$features" -t "$fstype" -L ROOTFS "${rootp}"
        root_partuuid=$(blkid -s PARTUUID -o value ${rootp})
        rootfstype=$(blkid -o value -s TYPE $rootp)

    fi
}

# Compress image compilation
function compress_img() {
    if [ "${compress:=}" = xz ]; then
        status "Compressing file: ${image_name}.img"

        if [ "$(arch)" == 'x86_64' ] || [ "$(arch)" == 'aarch64' ]; then
            limit_cpu pixz -p "${num_cores:=}" "${image_dir}/${image_name}.img" # -p Nº cpu cores use

        else
            xz --memlimit-compress=50% -T "$num_cores" "${image_dir}/${image_name}.img" # -T Nº cpu cores use

        fi

        img="${image_dir}/${image_name}.img.xz"

    fi

    chmod 0644 "$img"
}

# Calculate total time compilation.
function fmt_plural() {
  [[ $1 -gt 1 ]] && printf "%d %s" $1 "${3}" || printf "%d %s" $1 "${2}"
}

function total_time() {
  local t=$(( $1 ))
  local h=$(( t / 3600 ))
  local m=$(( t % 3600 / 60 ))
  local s=$(( t % 60 ))

  printf "\nFinal time: "
  [[ $h -gt 0 ]] && { fmt_plural $h "hour" "hours"; printf " "; }
  [[ $m -gt 0 ]] && { fmt_plural $m "minute" "minutes"; printf " "; }
  [[ $s -gt 0 ]] && fmt_plural $s "second" "seconds"
  printf "\n"
}

# Unmount filesystem
function umount_partitions() {
    # Make sure we are somewhere we are not going to unmount
    cd "${repo_dir}/"

    # Run a sync to flush any cached data
    sync
    # Define possible mounted points
    # This function is called both if success and failed
    # If we fail early in the process, then work_dir may still have proc mounted
    possible_mounts=("${base_dir}/root/boot" "${base_dir}/root/boot/firmware" "${base_dir}/root/proc" "${work_dir}/proc")

    # Unmount boot partitions if they exist
    for mount in "${possible_mounts[@]}"; do
        if mountpoint -q "$mount"; then
            umount -q "$mount"
        fi
    done

    # Unmount root partition
    if mountpoint -q "${base_dir}/root"; then
        umount -q "${base_dir}/root"
    fi
}

# Clean up all the temporary build stuff and remove the directories.
function clean_build() {
    log "Cleaning up" green

    # unmount anything that may be mounted
    log "Un-mount anything that may be mounted" green
    umount_partitions

    # Delete files
    if [[ $debug = 0 ]]; then
      log "Cleaning up the temporary build files: ${work_dir}" green
      rm -rf "${work_dir}"
      log "Cleaning up the temporary build files: ${base_dir}" green
      rm -rf "${base_dir}"
    else
      log "Skipping cleaning up the temporary build files (due to DEBUG):" green
      log "- ${work_dir}" green
      log "- ${base_dir}" green
    fi

    # Done
    log "Done" green
    total_time $SECONDS
}

function check_trap() {
    log "⚠️ An error has occurred!\n" red
    clean_build

    exit 1
}

# Show progress
function status() {
    status_i=$((status_i + 1))
    [[ $debug = 1 ]] && timestamp="($(date +"%Y-%m-%d %H:%M:%S"))" || timestamp=""
    log "✅ ${status_i}/${status_t}:${colour_reset} $1 $timestamp" green
}

find_qemu_static() {
    local arch="$1"
    ## Debian <= 12
    if [ -e "/usr/bin/qemu-${arch}-static" ]; then
        echo "/usr/bin/qemu-${arch}-static"
    ## Debian >= 13
    elif [ -e "/usr/bin/qemu-${arch}" ]; then
        echo "/usr/bin/qemu-${arch}"
    else
        return 1
    fi
}
