#!/usr/bin/env bash

log "Enabling eatmydata..." gray

# Find the latest version of eatmydata in the APT cache
archive=$(ls -v "${work_dir}/var/cache/apt/archives/"*eatmydata*.deb 2>/dev/null | tail -n 1)

if [[ -n "${archive:-}" ]]; then
  log "Using eatmydata package: $archive" green
  dpkg-deb -x "$archive" "${work_dir}"
else
  log "No eatmydata package found in APT cache!" red
  exit 1
fi

# Prepare dpkg to use eatmydata
chroot_exec dpkg-divert --divert /usr/bin/dpkg-eatmydata --rename --add /usr/bin/dpkg

# Generate wrapper script for dpkg with eatmydata
cat >"${work_dir}/usr/bin/dpkg" <<EOF
#!/bin/sh
LIBEAT="/usr/lib/${lib_arch}/libeatmydata.so"

if [ -e "$LIBEAT" ]; then
    export LD_PRELOAD="\${LD_PRELOAD:+\$LD_PRELOAD:}\$LIBEAT"
fi

exec /usr/bin/dpkg-eatmydata --force-unsafe-io "\$@"
EOF

chmod 0755 "${work_dir}/usr/bin/dpkg"
