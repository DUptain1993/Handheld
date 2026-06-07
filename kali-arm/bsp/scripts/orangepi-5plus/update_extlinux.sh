#!/bin/bash

TIMEOUT=""
DEFAULT=""
APPEND=""

set -eo pipefail

if [[ ! -f "/boot/config.txt" ]]; then
  . /etc/default/extlinux
fi

if [[ -f "/etc/kernel/cmdline" ]]; then
  APPEND="$APPEND `cat /etc/kernel/cmdline`"
elif `grep -qi "rk3328" /sys/firmware/devicetree/base/compatible` || `grep -qi "rk3399" /sys/firmware/devicetree/base/compatible`; then
  APPEND="$APPEND root=PARTUUID=B921B045-1DF0-41C3-AF44-4C6F280D3FAE"
else
  APPEND="$APPEND root=PARTUUID=614E0000-0000-4B53-8000-1D28000054A9"
fi

if [[ -f "/etc/default/console" ]]; then
  APPEND="$APPEND `cat /etc/default/console`"
fi

if [[ -f "/boot/config.txt" ]]; then
  for CMDLINE in `grep "^cmdline:" /boot/config.txt | sed 's/cmdline://g'`
  do
    APPEND="$APPEND $CMDLINE"
  done
fi

echo "Kernel configuration : $APPEND" 1>&2
echo ""

echo "Creating new extlinux.conf..." 1>&2

mkdir -p /boot/extlinux/
exec 1> /boot/extlinux/extlinux.conf.new

echo "#timeout ${TIMEOUT:-10}"
echo "#menu title select kernel"
[[ -n "$DEFAULT" ]] && echo "default $DEFAULT"
echo ""

emit_kernel() {
  local VERSION="$1"
  local APPEND="$2"
  local NAME="$3"
  local DTOVERLAY=""

  echo "label kernel-$VERSION$NAME"
  echo "    kernel /boot/vmlinuz-$VERSION"

  if [[ -f "/etc/kernel/cmdline" ]]; then
    if [[ -f "/boot/initrd.img-$VERSION" ]]; then
      echo "    initrd /boot/initrd.img-$VERSION"
    fi
  fi

  if [[ -f "/boot/dtb-$VERSION" ]]; then
    echo "    fdt /dtb-$VERSION"
  else
    if [[ ! -d "/boot/dtbs/$VERSION" ]]; then
      mkdir -p /boot/dtbs
      cp -au "/usr/lib/linux-image-$VERSION" "/boot/dtbs/$VERSION"
    fi
    echo "    devicetreedir /boot/dtbs/$VERSION/rockchip"
  fi

  if [[ -f "/boot/config.txt" ]]; then
    for DTBO in `grep "^dtoverlay=" /boot/config.txt | sed 's/dtoverlay=//g'`
    do
      if [[ -f "/boot/dtbs/$VERSION/rockchip/overlay/$DTBO.dtbo" ]]; then
        DTOVERLAY="$DTOVERLAY /boot/dtbs/$VERSION/rockchip/overlay/$DTBO.dtbo "
      fi
    done
    if [[ -n "$DTOVERLAY" ]]; then
      echo "    fdtoverlays "$DTOVERLAY""
    fi
  fi

  echo "    append $APPEND"
  echo ""
}

rm -rf /boot/dtbs
linux-version list | linux-version sort --reverse | while read VERSION; do
  emit_kernel "$VERSION" "$APPEND"
done

exec 1<&-

echo "Installing new extlinux.conf..." 1>&2
mv /boot/extlinux/extlinux.conf.new /boot/extlinux/extlinux.conf
