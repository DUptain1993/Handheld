## Kali-ARM Build-Scripts
Kali Linux ARM build-scripts.

These are the same build scripts that we use to generate the pre-generated official Kali Linux ARM images, found here: <https://www.kali.org/get-kali/>

There are additional scripts included in this repository, supporting more devices, but these will need to be built in order for them to be used.

For more information, please see: <https://www.kali.org/docs/arm/>

---

### Building
- These scripts are tested on Kali Linux `arm64`, `x64`, and `x86` installations only _(We **recommend x64**)_
- Make sure you run the `./common.d/build_deps.sh` script before trying to build an image, as this installs all required dependencies.  You may need to reboot after installing the build dependencies, if you do, the script will mention it at the end.
- You will need at **least 8GB of RAM or use SWAP file**

An example workflow to build a _[Raspberry Pi 4](https://www.kali.org/docs/arm/raspberry-pi-4/) Kali Linux image_ would look like:

```
$ cd ~/
$ git clone https://gitlab.com/kalilinux/build-scripts/kali-arm
$ cd ~/kali-arm/
$ sudo ./common.d/build_deps.sh
$ sudo ./raspberry-pi.sh
```

- Depending on your system hardware & network connectivity, will depend on how long it will take to build _(4 core CPU, 8GB RAM, SSD inside a VM takes using a [local repo](https://www.kali.org/docs/community/setting-up-a-kali-linux-mirror/) about 100 minutes per script)_
- On x64 systems, after the script finishes running, you will have an image file located in `~/kali-arm/images/` called `kali-linux-2021.3-rpi-armhf.img.xz`
- On x86 systems, as they do not have enough RAM to compress the image, after the script finishes running, you will have an image file located in `~/kali-arm/images/` called `kali-linux-2021.3-rpi-armhf.img`
  - _Should you want to try and shrink the file to make it easier to distribute, you will need to use **your own preferred compression**_.

---

### Help
On any build script, add `--help`. Example:

```
$ ./raspberry-pi.sh --help
 Usage commands:
# Architectures (arm64, armel, armhf)
./raspberry-pi.sh --arch arm64 or ./raspberry-pi.sh -a armhf

# Desktop manager (xfce, gnome, kde, i3, lxde, mate, e17 or none)
./raspberry-pi.sh --desktop kde or ./raspberry-pi.sh --desktop=kde

# Minimal image - no desktop manager
./raspberry-pi.sh --minimal or ./raspberry-pi.sh -m

# Slim image - no desktop manager & cli tools
./raspberry-pi.sh --slim or ./raspberry-pi.sh -s

# Enable debug & log file (./logs/<file>.log)
./raspberry-pi.sh --debug or ./raspberry-pi.sh -d

# Perform extra checks on the images build
./raspberry-pi.sh --extra or ./raspberry-pi.sh -x

# Help screen (this)
./raspberry-pi.sh --help or ./raspberry-pi.sh -h
```

---

### Custom Values
Changing [builder.txt](builder.txt.example) will allow for custom values, such as using a local LAN mirror:

```
$ echo 'mirror="http://192.168.1.100/kali"' > ./builder.txt
```

---

Thu Jan 27 15:47:28 UTC 2022
