#!/usr/bin/env python3

import re
import sys
from datetime import datetime

import yaml  # python3 -m pip install pyyaml --user

OUTPUT_FILE = "./devices.md"
INPUT_FILE = "./devices.yml"

repo_msg = f"""
_This table was [generated automatically](https://gitlab.com/kalilinux/build-scripts/kali-arm/-/blob/main/devices.yml) on {datetime.now().strftime('%Y-%B-%d %H:%M:%S')} from the [Kali ARM GitLab repository](https://gitlab.com/kalilinux/build-scripts/kali-arm)_
"""

qty_devices = 0

# Input:
# ------------------------------------------------------------
# See: ./devices.yml
# https://gitlab.com/kalilinux/build-scripts/kali-arm/-/blob/main/devices.yml


def yaml_parse(content):
    result = ""
    lines = content.split('\n')

    for line in lines:
        if line.strip() and not line.strip().startswith('#'):
            result += line + "\n"

    return yaml.safe_load(result)

# https://stackoverflow.com/a/11150413


def natural_sort(l):
    def convert(text): return int(text) if text.isdigit() else text.lower()

    def alphanum_key(key): return [convert(c)
                                   for c in re.split('([0-9]+)', key)]

    return sorted(l, key=alphanum_key)


def generate_table(data):
    global qty_devices

    default = ""

    table = "| Vendor | Board | CPU | CPU Cores | GPU | RAM | RAM Size (MB) | Ethernet | Ethernet Speed (MB) | Wi-Fi | Bluetooth | USB2 | USB3 | Storage |        Notes        |\n"
    table += "|--------|-------|-----|-----------|-----|-----|---------------|----------|---------------------|-------|-----------|------|------|---------|---------------------|\n"

    # Iterate over per input (depth 1)
    for yaml in data["devices"]:
        # Iterate over vendors
        for vendor in yaml.keys():
            # Iterate over board (depth 2)
            for board in yaml[vendor]:
                qty_devices += 1

                ram_size = ""

                storage = ""

                i = 0

                for f in natural_sort(board.get("ram-size", default)):
                    if i > 0:
                        ram_size += ", "

                    ram_size += f

                    i += 1

                i = 0

                for f in natural_sort(board.get("storage", default)):
                    if i > 0:
                        storage += ", "

                    storage += f

                    i += 1

                table += f"| {vendor} | {board.get('name', default)} | {board.get('cpu', default)} | {board.get('cpu-cores', default)} | {board.get('gpu', default)} | {board.get('ram', default)} | {ram_size} | {board.get('ethernet', default)} | {board.get('ethernet-speed', default)} | {board.get('wifi', default)} | {board.get('bluetooth', default)} | {board.get('usb2', default)} | {board.get('usb3', default)} | {storage} | {board.get('notes', default)} |\n"

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
            meta += "title: Kali ARM Devices\n"
            meta += "---\n\n"

            stats = f"- The official [Kali ARM repository](https://gitlab.com/kalilinux/build-scripts/kali-arm) contains build-scripts to support [**{qty_devices}** Kali ARM devices](device-stats.html)\n"
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
