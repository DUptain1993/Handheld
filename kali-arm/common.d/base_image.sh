#!/usr/bin/env bash
#
# Every Kali ARM image starts with this
#

# shellcheck disable=SC2154
# shellcheck source=/dev/null

# Stop on error
set -e

# Load general functions
source ./common.d/functions.sh

# Read in any command line arguments
arguments $*

# Load common variables
# Needs to come after arguments, given the values are used as variables
source ./common.d/variables.sh

# If there is any issues, run check_trap (from ./common.d/functions.sh)
trap check_trap INT ERR SIGTERM SIGINT

# Always at the end, run clean_build (from ./common.d/functions.sh)
trap clean_build EXIT

# Checks script environment
source ./common.d/check.sh

# Packages build list
include packages

# Execute initial debootstrap
debootstrap_exec ${mirror}

# Define kali.sources
kali_sources

# APT options
include apt_options

# Disable suspend/resume - speeds up boot massively
mkdir -p "${work_dir}/etc/initramfs-tools/conf.d/"
echo "RESUME=none" >"${work_dir}/etc/initramfs-tools/conf.d/resume"

# Copy directory bsp into build dir
status "Copy directory bsp into build dir"
cp -rp bsp "${work_dir}"

# Third stage
cat <<EOF >"${work_dir}/third-stage"
#!/usr/bin/env bash
# Stop on error
set -e

status_3i=0
status_3t=\$(grep '^status_stage3 ' \$0 | wc -l)

status_stage3() {
  status_3i=\$((status_3i+1))
  colour1=""
  colour2=""
  if [ -n "${colour_reset}" ]; then
    colour1="$(tput setaf 15)"
    colour2="$(tput setaf 2)"
  fi
  echo  "  ${colour1}✅ Stage 3 (\${status_3i}/\${status_3t}):${colour2} \$1${colour_reset}"
}

status_stage3 'Update apt'
eatmydata apt-get update

status_stage3 'Install core packages'
eatmydata apt-get -y install ${third_stage_pkgs}

status_stage3 'Install packages'
eatmydata apt-get install -y ${packages}
EOF

if [ "${desktop}" != "none" ]; then
  log "Desktop mode enabled: ${desktop}" green
  cat <<EOF >>"${work_dir}/third-stage"
status_stage3 'Install desktop packages'
eatmydata apt-get install -y ${desktop_pkgs} ${extra}

# In case any other terminals are installed, set x-t-e to qterminal as that is
# our default terminal.
status_stage3 'Set default terminal via update-alternatives'
update-alternatives --verbose --set x-terminal-emulator /usr/bin/qterminal || true

if [ -e /etc/lightdm/lightdm.conf ]; then
status_stage3 'Set logind check graphical to false'
sed -i -e 's/^#logind-check-graphical=true/logind-check-graphical=false/' /etc/lightdm/lightdm.conf
fi
EOF
fi

cat <<EOF >>"${work_dir}/third-stage"
status_stage3 'ntp does not always sync the date, but systemd-timesyncd does, so we remove ntp and reinstall it with this'
eatmydata apt-get install -y systemd-timesyncd --autoremove

status_stage3 'Set various defaults in debconf'
debconf-set-selections -v << _EOF_
# Disable popularity-contest
popularity-contest popularity-contest/participate boolean false

# Disable the encfs error message
encfs encfs/security-information boolean true
encfs encfs/security-information seen true

# Random other questions
console-common console-data/keymap/policy select "Select keymap from full list"
console-common console-data/keymap/full select en-latin1-nodeadkeys
console-setup console-setup/charmap47 select UTF-8
samba-common samba-common/dhcp boolean false
kismet-capture-common kismet-capture-common/install-users string
kismet-capture-common kismet-capture-common/install-setuid boolean true
wireshark-common wireshark-common/install-setuid boolean true
sslh sslh/inetd_or_standalone select standalone
atftpd atftpd/use_inetd boolean false
_EOF_

status_stage3 'Copy all services'
cp -p /bsp/services/all/*.service /etc/systemd/system/

status_stage3 'Enable SSH service'
systemctl enable ssh

status_stage3 'Allow users to use NetworkManager'
mkdir -p /etc/polkit-1/rules.d/
install -m644 /bsp/polkit/10-networkmanager.rules /etc/polkit-1/rules.d/

status_stage3 'Copy script growpart'
install -m755 /bsp/scripts/growpart /usr/local/bin/

status_stage3 'Copy script rpi-resizerootfs'
install -m755 /bsp/scripts/rpi-resizerootfs /usr/sbin/

status_stage3 'Enable rpi-resizerootfs first boot'
systemctl enable rpi-resizerootfs

status_stage3 'Enable runonce script'
install -m755 /bsp/scripts/runonce /usr/sbin/
cp -rf /bsp/runonce.d /etc
systemctl enable runonce

# Install Powershell 7.5.1
status_stage3 'Install powershell 7.5.1'
if [[ ${architecture} != armel ]]; then
  if [[ ${architecture} == "arm64" ]]; then
    curl -L -o /tmp/powershell.tar.gz https://github.com/PowerShell/PowerShell/releases/download/v7.5.1/powershell-7.5.1-linux-arm64.tar.gz

  else
    curl -L -o /tmp/powershell.tar.gz https://github.com/PowerShell/PowerShell/releases/download/v7.5.1/powershell-7.5.1-linux-arm32.tar.gz

  fi
    ls -lh /tmp/powershell.tar.gz
    file /tmp/powershell.tar.gz
    md5sum /tmp/powershell.tar.gz
    mkdir -p /opt/microsoft/powershell/7
    tar -xf  /tmp/powershell.tar.gz -C /opt/microsoft/powershell/7
    chmod +x /opt/microsoft/powershell/7/pwsh
    ln -s /opt/microsoft/powershell/7/pwsh /usr/bin/pwsh

fi

status_stage3 'Try and make the console a bit nicer. Set the terminus font for a bit nicer display'
sed -i -e 's/CHARMAP=.*/CHARMAP="UTF-8"/' /etc/default/console-setup
sed -i -e 's/FONTFACE=.*/FONTFACE="Terminus"/' /etc/default/console-setup
sed -i -e 's/FONTSIZE=.*/FONTSIZE="6x12"/' /etc/default/console-setup

status_stage3 'Fix startup time from 5 minutes to 15 secs on raise interface'
sed -i 's/^TimeoutStartSec=5min/TimeoutStartSec=15/g' "/usr/lib/systemd/system/networking.service"

status_stage3 'Mask smartmontools service'
systemctl mask smartmontools

status_stage3 'Add arch to /var/lib/dpkg/arch file'
if [[ ${architecture} == "arm64" ]]; then
echo 'arm64' | tee /var/lib/dpkg/arch
fi
EOF
