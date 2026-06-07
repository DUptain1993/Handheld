#!/usr/bin/env python3
# REF: https://www.kali.org/docs/arm/

import sys
from datetime import datetime

import yaml  # python3 -m pip install pyyaml --user

OUTPUT_FILE = "./image-overview.md"
INPUT_FILE = "./devices.yml"

repo_msg = f"""
_This table was [generated automatically](https://gitlab.com/kalilinux/build-scripts/kali-arm/-/blob/main/devices.yml) on {datetime.now().strftime('%Y-%B-%d %H:%M:%S')} from the [Kali ARM GitLab repository](https://gitlab.com/kalilinux/build-scripts/kali-arm)_
"""

qty_devices = 0
qty_images = 0
qty_image_kali = 0
qty_image_community = 0
qty_image_eol = 0
qty_image_unknown = 0

# Input:
# ------------------------------------------------------------
# See: ./devices.yml
# https://gitlab.com/kalilinux/build-scripts/kali-arm/-/blob/main/devices.yml


def yaml_parse(content):
    result = ""
    lines = content.split("\n")

    for line in lines:
        if line.strip() and not line.strip().startswith("#"):
            result += line + "\n"

    return yaml.safe_load(result)


def generate_table(data):
    global qty_devices, qty_images, qty_image_kali, qty_image_community, qty_image_eol, qty_image_unknown

    images = []

    default = ""

    table = "| [Device Name](https://www.kali.org/docs/arm/) | [Build-Script](https://gitlab.com/kalilinux/build-scripts/kali-arm/) | [Official Image](https://www.kali.org/get-kali/#kali-arm) | Community Image | EOL/Retired Image |\n"
    table += "|---------------|--------------|----------------|-----------------|---------------|\n"

    # Iterate over per input (depth 1)
    for yaml in data["devices"]:
        # Iterate over vendors
        for vendor in yaml.keys():
            # Iterate over board (depth 2)
            for board in yaml[vendor]:
                qty_devices += 1

                # Iterate over per board
                for key in board.keys():
                    # Check if there is an image for the board
                    if "images" in key:
                        # Iterate over image (depth 3)
                        for image in board[key]:
                            if image["name"] not in images:
                                # ALT: images.append(image["image"])
                                images.append(image["name"])

                                qty_images += 1

                                build_script = image.get(
                                    "build-script",
                                    default
                                )

                                if build_script:
                                    build_script = f"[{build_script}](https://gitlab.com/kalilinux/build-scripts/kali-arm/-/blob/main/{build_script})"

                                name = image.get("name", default)
                                slug = image.get("slug", default)

                                if name and slug:
                                    name = f"[{name}](https://www.kali.org/docs/arm/{slug}/)"

                                support = image.get("support", default)

                                if support == "kali":
                                    status = "x |  | "
                                    qty_image_kali += 1

                                elif support == "community":
                                    status = " | x | "
                                    qty_image_community += 1

                                elif support == "eol":
                                    status = " |  | x"
                                    qty_image_eol += 1

                                else:
                                    status = " |  | "
                                    qty_image_unknown += 1

                                table += f"| {name} | {build_script} | {status} |\n"

                            # else:
                            #    print(f"DUP {image["name"]} / {image["image"]}")

                if "images" not in board.keys():
                    print(f"[i] Possible issue with: {board.get('board', default)} (no images)")

    return table


def read_file(file):
    try:
        with open(file) as f:
            data = f.read()

    except Exception as e:
        print(f"[-] Cannot open input file: {file} - {e}")

    return data


def write_file(data, file):
    try:
        with open(file, "w") as f:
            meta = "---\n"
            meta += "title: Kali ARM Image Overview\n"
            meta += "---\n\n"

            stats = f"- The official [Kali ARM repository](https://gitlab.com/kalilinux/build-scripts/kali-arm) contains [build-scripts]((https://gitlab.com/kalilinux/build-scripts/kali-arm)) to create [**{qty_images}** unique Kali ARM images](image-stats.html) for **{qty_devices}** devices\n"
            stats += f"- The [next release](https://www.kali.org/releases/) cycle will include [**{qty_image_kali}** Kali ARM images](image-stats.html) _([ready to download](https://www.kali.org/get-kali/#kali-arm))_, **{qty_image_community}** images which can be [built](https://gitlab.com/kalilinux/build-scripts/kali-arm), and {qty_image_eol} retired images\n"
            stats += "- [Kali ARM Statistics](index.html)\n\n"

            f.write(str(meta))
            f.write(str(stats))
            f.write(str(data))
            f.write(str(repo_msg))

            print(f"[+] File: {OUTPUT_FILE} successfully written")

    except Exception as e:
        print(f"[-] Cannot write to output file: {file} - {e}")

    return 0


def print_summary():
    print(f"Devices: {qty_devices}")
    print(f"Images : {qty_images}")
    print(f"- Kali     : {qty_image_kali}")
    print(f"- Community: {qty_image_community}")
    print(f"- EOL      : {qty_image_eol}")
    print(f"- Unknown  : {qty_image_unknown}")


def main(argv):
    # Assign variables
    data = read_file(INPUT_FILE)

    # Get data
    res = yaml_parse(data)
    generated_markdown = generate_table(res)

    # Create markdown file
    write_file(generated_markdown, OUTPUT_FILE)

    # Print result
    print_summary()

    # Exit
    exit(0)


if __name__ == "__main__":
    main(sys.argv[1:])
