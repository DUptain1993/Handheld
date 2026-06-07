#!/usr/bin/env bash
# shellcheck disable=SC2034,SC2154

# Current directory
repo_dir="$(pwd)"

# Variant name for image and dir build
variant=${variant=$desktop}-${architecture}

# Base directory
base_dir=${repo_dir}/base/${hw_model}-${variant}

# Working directory
work_dir="${base_dir}/working"

# Image directory
image_dir="${repo_dir}/images"

# Version Kali release
version=${version:-rolling}

# Custom image file name variable - MUST NOT include .img at the end
image_name=${image_name:-"kali-linux-${version}-${hw_model}-${variant}"}

# Generate a random machine name to be used
machine=$(dbus-uuidgen)

# Custom hostname variable
hostname=${hostname:-kali}

# If hw_model is set, add it to hostname
[ -n "${hw_model:=}" ] && [ "${hostname:=}" = "kali" ] \
  && hostname="kali-${hw_model}"

# Suite to use, valid options are:
# kali-rolling, kali-dev, kali-bleeding-edge, kali-dev-only, kali-experimental, kali-last-snapshot
suite=${suite:-"kali-rolling"}

# Choose a locale
locale="en_US.UTF-8"

# Free space rootfs in MiB
free_space="${free_space:-1024}"

# /boot partition in MiB
bootsize="${bootsize:-256}"

# Select compression, xz or none
compress="xz"

# Choose filesystem format to format root partition (ext3 or ext4).
fstype="ext4"

# Generate a random root partition UUID to be used
root_uuid=$(cat </proc/sys/kernel/random/uuid | less)

# Disable IPv6 (yes or no)
disable_ipv6="yes"

# Make SWAP (yes or no)
swap="no"

# Use 0 for unlimited CPU cores, -1 to subtract 1 cores from the total
cpu_cores="4"

# 0 or 100 No limit, 10 = percentage use, 50, 75, 90, etc
# Percentage to limit CPU (via cgroups)
# -1 to disable the feature
# 1 -> 100. 10 = percentage use, 50, 75, 90, etc
cpu_limit="-1"

# If you have your own preferred mirrors, set them here
mirror=${mirror:-"http://http.kali.org/kali"}

# Use packages from the listed components of the archive
components="main,contrib,non-free,non-free-firmware"

# GitLab URL Kali repository
kaligit="https://gitlab.com/kalilinux"

# GitHub raw URL
githubraw="https://raw.githubusercontent.com"

# DNS server
nameserver=${nameserver:-"8.8.8.8"}

# workaround for LP: #520465 ~ https://bugs.launchpad.net/ubuntu/+bug/520465
export MALLOC_CHECK_=0

# Proxy
# You can turn off automatic settings by uncommenting apt_cacher=off
# apt_cacher=off
# By default the proxy settings are local, but you can define an external proxy
# proxy_url="http://external.intranet.local"

# Load build configuration
if [ -f "${repo_dir}"/builder.txt ]; then
  log "Loading: "${repo_dir}"/builder.txt"
  
  # shellcheck source=/dev/null
  source "${repo_dir}"/builder.txt

  [ "${debug}" = 1 ] \
    && grep -v '#' "${repo_dir}"/builder.txt \
      | sort -u \
    || true

fi

# In case `su` was used
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

## From ./common.d/functions.sh
debug=0
extra=0
status_i=0
status_t=$(($(grep '.*status ' $0 common.d/*.sh | wc -l) -1))

## Enable colour (--no-colour)
colour_output="${colour_output:-yes}"
colour_reset=${colour_reset:-$( tput sgr0 )}
