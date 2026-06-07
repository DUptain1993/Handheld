#!/usr/bin/env bash

# Third stage
cat <<EOF >> "${work_dir}"/third-stage
status_stage3 'Clean up apt-get'
eatmydata apt-get -y --purge autoremove
eatmydata apt-get -y clean
EOF

# Run third stage
chmod 0755 "${work_dir}/third-stage"
status "Run third stage"
#systemd-nspawn_exec /third-stage
chroot_exec /third-stage
