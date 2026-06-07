#!/usr/bin/env bash
# shellcheck disable=SC2154

if [ "${debug}" = 1 ]; then
  log "Skipping due to debug mode ($0 -d) being enabled" yellow

  return

fi

status "clean system"

# Clean system
chroot_exec <<'EOF'
rm -f /0
rm -rf /bsp
command fc-cache && fc-cache -frs
rm -rf /tmp/*
rm -rf /etc/*-
rm -rf /hs_err*
rm -rf /etc/console-setup/cached_*
rm -rf /userland
rm -rf /opt/vc/src
rm -f /third-stage
rm -f /etc/ssh/ssh_host_*
rm -rf /var/lib/dpkg/*-old
rm -rf /var/lib/apt/lists/*
rm -rf /var/cache/apt/*.bin
rm -rf /var/cache/debconf/*-old
rm -rf /var/cache/apt/archives/*
rm -rf /etc/apt/apt.conf.d/apt_opts
rm -rf /etc/apt/apt.conf.d/99_norecommends
find /var/log -type f ! -path "/var/log/apt/*" ! -path "/var/log/postgresql/*" ! -empty -exec truncate -s 0 {} +
history -c
EOF

# Disable the use of http proxy in case it is enabled
disable_proxy

# Mirror & suite replacement
restore_mirror

# Reload kali.sources
#kali_sources

# Choose a locale
set_locale "$locale"

# Newer systemd requires that /etc/machine-id exists but is empty
rm -f "${work_dir}"/etc/machine-id || true
touch "${work_dir}"/etc/machine-id
rm -f "${work_dir}"/var/lib/dbus/machine-id || true

# Define DNS server after last running systemd-nspawn
echo "nameserver ${nameserver}" >"${work_dir}"/etc/resolv.conf
