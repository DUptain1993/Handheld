#!/usr/bin/env python3

# ARM Devices ~ https://gitlab.com/kalilinux/build-scripts/kali-arm/-/blob/main/devices.yml

###############################################
# Script to prepare the rpi-imager json script for Kali ARM quarterly releases.
# Based on ./bin/pre-release.py
#
# This should be run after images are created.
#
# It parses the YAML sections of the devices.yml and creates:
#   - "<imagedir>/rpi-imager.json = "manifest file mapping image name to display name
#
# Dependencies:
#   $ sudo apt -y install python3 python3-yaml xz-utils
#   ...OR...
#   $ python3 -m venv .env; source .env/bin/activate; python3 -m pip install pyyaml
#
# Usage:
#   $ ./bin/post-release.py -i <input file> -r <release> -o <image directory>
#
# E.g.:
#   $ ./bin/post-release.py -i devices.yml -r 2022.3 -o images/

import datetime
import getopt
import json
import os
import re
import stat
import subprocess
import sys

import yaml  # python3 -m pip install pyyaml --user

manifest = ""  # Generated automatically (<imagedir>/rpi-imager.json)

release = ""

imagedir = ""

inputfile = ""

qty_devices = 0
qty_images = 0
qty_release_images = 0

file_ext = [
    "xz",
    "xz.sha256sum",
    "sha256sum"
    ]

# Input:
# ------------------------------------------------------------
# See: ./devices.yml
# https://gitlab.com/kalilinux/build-scripts/kali-arm/-/blob/main/devices.yml
#
# See:  ./images/*.img.sha256sum (uncompressed image sha256sum - to get the sha256sum
#       ./images/*.img.xz.sha256sum (compressed image sha256sum - to get the sha256sum
#       ./images/*.img.xz (compressed image; we use xz to look at the metadata to get compressed/uncompressed size)


def bail(message="", strerror=""):
    outstr = ""

    prog = sys.argv[0]

    if message != "":
        outstr = f"\nError: {message}"

    if strerror != "":
        outstr += f"\nMessage: {strerror}\n"

    else:
        outstr += f"\n\nUsage: {prog} -i <input file> -o <output directory> -r <release>"
        outstr += f"\nE.g. : {prog} -i devices.yml -o images/ -r {datetime.datetime.now().year}.1\n"

    print(outstr)

    sys.exit(2)


def getargs(argv):
    global inputfile, imagedir, release

    try:
        opts, args = getopt.getopt(
            argv,
            "hi:o:r:",
            [
                "inputfile=",
                "imagedir=",
                "release="
            ]
        )

    except getopt.GetoptError as e:
        bail(f"Incorrect arguments: {e}")

    if opts:
        for opt, arg in opts:
            if opt == "-h":
                bail()

            elif opt in ("-i", "--inputfile"):
                inputfile = arg

            elif opt in ("-r", "--release"):
                release = arg

            elif opt in ("-o", "--imagedirectory"):
                imagedir = arg.rstrip("/")

            else:
                bail(f"Unrecognised argument: {opt}")

    else:
        bail("Failed to read arguments")

    if not release:
        bail("Missing required argument: -r/--release")

    return 0


def yaml_parse(content):
    result = ""

    lines = content.split("\n")

    for line in lines:
        if line.strip() and not line.strip().startswith("#"):
            result += line + "\n"

    return yaml.safe_load(result)


def jsonarray(devices, vendor, name, url, extract_size, extract_sha256, image_download_size, image_download_sha256, device_arch):
    if not vendor in devices:
        devices[vendor] = []

    jsondata = {
        "name": name,
        "description": f"Kali Linux ARM image for the {name}",
        "url": url,
        "icon": "https://www.kali.org/images/kali-linux-logo.svg",
        "website": "https://www.kali.org/",
        "release_date": datetime.datetime.today().strftime("%Y-%m-%d"),
        "extract_size": extract_size,
        "extract_sha256": extract_sha256,
        "image_download_size": image_download_size,
        "image_download_sha256": image_download_sha256,
        "devices": device_arch,
        "init_format": "cloudinit",
    }

    devices[vendor].append(jsondata)

    return devices


def generate_manifest(data):
    global release, qty_devices, qty_images, qty_release_images

    default = ""

    devices = {}

    # Iterate over per input (depth 1)
    for yaml in data["devices"]:
        # Iterate over vendors
        for vendor in yaml.keys():
            # @g0tmi1k: Feels like there is a cleaner way todo this
            if not vendor == "raspberrypi":
                continue

            # Ready to have a unique name in the entry
            img_seen = set()

            # Iterate over board (depth 2)
            for board in yaml[vendor]:
                qty_devices += 1

                # Iterate over per board
                for key in board.keys():
                    # Check if there is an image for the board
                    if "images" in key:
                        # Iterate over image (depth 3)
                        for image in board[key]:
                            qty_images += 1

                            # Check that it's not EOL or community supported
                            if image.get("support") == "kali":
                                name = image.get("name", default)

                                # If we haven't seen this image before for this vendor
                                if name not in img_seen:
                                    img_seen.add(name)
                                    qty_release_images += 1

                                    filename = f"kali-linux-{release}-{image.get('image', default)}"

                                    # Check to make sure files got created
                                    for ext in file_ext:
                                        check_file = f"{imagedir}/{filename}.{ext}"

                                        if not os.path.isfile(check_file):
                                            bail(
                                                f"Missing: '{check_file}'! Please create the image before running")

                                    with open(f"{imagedir}/{filename}.xz.sha256sum") as f:
                                        image_download_sha256 = f.read().split()[0]

                                    with open(f"{imagedir}/{filename}.sha256sum") as f:
                                        extract_sha256 = f.read().split()[0]

                                    url = f"https://kali.download/arm-images/kali-{release}/{filename}.xz"

                                    if "arm64" in image.get("architecture", default):
                                        arch = "64bit"
                                    else:
                                        arch = "32bit"

                                    # Due to board naming, map the board slugs so that we end up with the correct devices supported list.
                                    pi_map = {
                                            "raspberry-pi-5": "pi5",
                                            "raspberry-pi-4": "pi4",
                                            "raspberry-pi-3": "pi3",
                                            "raspberry-pi-2": "pi2",
                                            "raspberry-pi1": "pi1",
                                            "raspberry-pi-zero-2-w": "pi3",
                                            "raspberry-pi-zero-w": "pi1",
                                    }

                                    device_arch = []

                                    # Loop over the RaspberryPi boards.  We have to do this because otherwise, we end up matching too loosely, or conversely, not enough.
                                    for yaml in data["devices"]:
                                        for vendor in yaml.keys():
                                            if vendor != "raspberrypi":
                                                continue
                                            for board in yaml[vendor]:
                                                board_name = board.get("board")
                                                for img in board.get("images", []):
                                                    if img.get("image") == image.get("image") and img.get("support") == "kali":
                                                        slug = pi_map.get(board_name)
                                                        if slug:
                                                            device_arch.append(f"{slug}-{arch}")

                                    device_arch = list(dict.fromkeys(device_arch))
                                    preferred_order = ["pi5", "pi4", "pi3", "pi2", "pi1"]
                                    device_arch.sort(key=lambda x: preferred_order.index(x.split("-")[0]))

                                    # @g0tmi1k: not happy about external OS, rather keep it in python (import lzma)
                                    try:
                                        unxz = subprocess.check_output(
                                            f"unxz --verbose --list {imagedir}/{filename}.xz | grep 'Uncompressed'", shell=True)

                                        extract_size = re.findall(
                                            r"\((.*?) B\)",
                                            str(unxz)
                                        )[0]
                                        extract_size = extract_size.replace(
                                            ",",
                                            ""
                                            )
                                        extract_size = int(extract_size)

                                    except subprocess.CalledProcessError as e:
                                        #print(f"command "{e.cmd}" return with error (code {e.returncode})")
                                        extract_size = 0

                                    #image_download_size = os.stat(f'{imagedir}/{filename}.xz').st_size
                                    image_download_size = os.path.getsize(f"{imagedir}/{filename}.xz")

                                    device_arch = list(dict.fromkeys(device_arch))
                                    preferred_order = ["pi5", "pi4", "pi3", "pi2", "pi1"]
                                    device_arch.sort(key=lambda x: preferred_order.index(x.split("-")[0]))

                                    jsonarray(
                                        devices,
                                        "os_list",
                                        name,
                                        url,
                                        extract_size,
                                        extract_sha256,
                                        image_download_size,
                                        image_download_sha256,
                                        device_arch,
                                        )

    return json.dumps(devices, indent=2)


def createdir(dir):
    try:
        if not os.path.exists(dir):
            os.makedirs(dir)

    except:
        bail(f"Directory {dir} does not exist and cannot be created")

    return 0


def readfile(file):
    try:
        with open(file) as f:
            data = f.read()

    except:
        bail(f"Cannot open input file: {file}")

    return data


def writefile(data, file):
    try:
        with open(file, "w") as f:
            f.write(str(data))

    except:
        bail(f"Cannot write to output file: {file}")

    return 0


def main(argv):
    global inputfile, imagedir, release

    # Parse command-line arguments
    if len(sys.argv) > 1:
        getargs(argv)

    else:
        bail("Missing arguments")

    # Assign variables
    manifest = f"{imagedir}/rpi-imager.json"
    data = readfile(inputfile)

    # Get data
    res = yaml_parse(data)
    manifest_list = generate_manifest(res)

    # Create output directory if required
    createdir(imagedir)

    # Create manifest file
    writefile(manifest_list, manifest)

    # Print result and exit
    print("\nStats:")
    print(f"  - Total devices\t: {qty_devices}")
    print(f"  - Total images\t: {qty_images}")
    print(f"  - {release} rpi images\t: {qty_release_images}")
    print("\n")
    print(f"Manifest file created\t: {manifest}")

    exit(0)


if __name__ == "__main__":
    main(sys.argv[1:])
