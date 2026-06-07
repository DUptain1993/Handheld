#!/usr/bin/env python3
# REF: https://gitlab.com/kalilinux/nethunter/build-scripts/kali-nethunter-kernels/-/blob/52cbfb36/scripts/generate_images_stats.py

import sys
from datetime import datetime

import yaml  # python3 -m pip install pyyaml --user

OUTPUT_FILE = "./image-stats.md"

INPUT_FILE = "./devices.yml"

repo_msg = f"""
_This table was [generated automatically](https://gitlab.com/kalilinux/build-scripts/kali-arm/-/blob/main/devices.yml) on {datetime.now().strftime('%Y-%B-%d %H:%M:%S')} from the [Kali ARM GitLab repository](https://gitlab.com/kalilinux/build-scripts/kali-arm)_
"""

qty_images = 0

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
    global qty_images

    images = []

    default = ""

    # Iterate over per input (depth 1)
    for yaml in data["devices"]:
        # Iterate over vendors
        for vendor in yaml.keys():
            # Iterate over board (depth 2)
            for board in yaml[vendor]:
                # Iterate over per board
                for key in board.keys():
                    # Check if there is an image for the board
                    if "images" in key:
                        # Iterate over image (depth 3)
                        for image in board[key]:
                            images.append(f"{image.get('name', default)} ({image.get('architecture', default)})")

                if "images" not in board.keys():
                    print(f"[i] Possible issue with: {board.get('board', default)} (no images)")

    table = "| [Image Name](images.html) (Architecture) |\n"
    table += "|---------------------------|\n"

    # iterate over all the devices
    for device in sorted(set(images)):
        table += f"| {device} |\n"

    qty_images = len(set(images))

    return table


def read_file(file):
    try:
        with open(file) as f:
            data = f.read()

    except Exception as e:
        print("[-] Cannot open input file: {} - {}".format(file, e))

    return data


def write_file(data, file):
    try:
        with open(file, "w") as f:
            meta = "---\n"
            meta += "title: Kali ARM Image Statistics\n"
            meta += "---\n\n"

            stats = "- The official [Kali ARM repository](https://gitlab.com/kalilinux/build-scripts/kali-arm) contains [build-scripts]((https://gitlab.com/kalilinux/build-scripts/kali-arm)) to create [**{}** unique Kali ARM images](images.html)\n".format(str(qty_images))
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
    print(f"Images: {qty_images}")


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
