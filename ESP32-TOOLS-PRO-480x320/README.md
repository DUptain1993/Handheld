Here is the translated and regenerated README in English.

<div align="center">

# 🦎 ESP32-TOOLS

### WiFi + Bluetooth security multi-tool firmware for ESP32

*Inspired by Flipper Zero, Bruce and ESP32 Marauder — created from scratch in Mexico*

<img src="img/splash.jpg" width="400" alt="Splash screen with axolotl"/>

<div align="center">

# 🦎 ESP32-TOOLS

### WiFi + Bluetooth security multi-tool firmware for ESP32

*Inspired by Flipper Zero, Bruce and ESP32 Marauder — made from scratch in Mexico*

<img src="img/splash.jpg" width="400" alt="Splash screen with axolotl"/>


![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform: ESP32](https://img.shields.io/badge/platform-ESP32-red.svg)
![Framework: Arduino](https://img.shields.io/badge/framework-Arduino-00979D.svg)
![Built with: PlatformIO](https://img.shields.io/badge/built%20with-PlatformIO-orange.svg)
![Version: 2.0](https://img.shields.io/badge/version-2.0-brightgreen.svg)
[![Web Installer](https://img.shields.io/badge/⚡_FLASH_FROM_BROWSER-fa4500?style=for-the-badge)](https://pepeangell5.github.io/ESP32-TOOLS-PRO-480x320/)
</div><div align="center"><div align="center">

# 🦎 ESP32-TOOLS

### WiFi + Bluetooth security multi-tool firmware for ESP32

*Inspired by Flipper Zero, Bruce and ESP32 Marauder — made from scratch in Mexico*

<img src="img/splash.jpg" width="400" alt="Splash screen with axolotl"/>

**By PepeAngell** · [Instagram](https://instagram.com/pepeangelll) · [Facebook](https://www.facebook.com/esp32tools/) · [GitHub](https://github.com/pepeangell5)

![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform: ESP32](https://img.shields.io/badge/platform-ESP32-red.svg)
![Framework: Arduino](https://img.shields.io/badge/framework-Arduino-00979D.svg)
![Built with: PlatformIO](https://img.shields.io/badge/built%20with-PlatformIO-orange.svg)
![Version: 2.0](https://img.shields.io/badge/version-2.0-brightgreen.svg)
[![Web Installer](https://img.shields.io/badge/⚡_FLASH_FROM_BROWSER-fa4500?style=for-the-badge)](https://pepeangell5.github.io/ESP32-TOOLS-PRO-480x320/)
</div>

---

## 🎬 Live demo

<div align="center">
<img src="img/ESP32.gif" width="500" alt="Firmware demo browsing all tools"/>

*Complete tour of firmware menus and tools*

</div>

---

## 🆕 What's new in version 1.0

v2.0 massively expands the firmware with **6 new tools**, a full **WiFi setup system** with virtual keyboard, and several quality of life extras:

- 🌐 **Evil Portal** — captive portal with fake AP, DNS spoofing and credential capture (SIMPLE mode + CLONE+Deauth mode)
- 🎭 **KARMA Attack** — captures probes and announces them as existing networks to attract devices
- 📡 **Probe Request Sniffer** — discover the networks that search for nearby cell phones
- 🌤️ **Clock & Weather** — NTP clock + live weather with IP location detection
- ⌨️ **QWERTY Virtual Keyboard** — reusable text input with ñ and symbols
- 🌙 **Screensaver** — axolotl bouncing style DVD logo with little stars
- 🔧 **WiFi Persistent Config** — writes your network only once, it is saved
- 🗑️ **Forget WiFi** — option in Settings to forget the saved network

---

## 📖 What is ESP32-TOOLS?

**ESP32-TOOLS** is a complete firmware for an ESP32-based portable multi-tool, designed for WiFi and Bluetooth security testing. Includes network scanner, spectrum analyzer, package monitor, beacon generator, deauther, Bluetooth disruptor, evil portal, KARMA attack, live weather watch and more — all with its own retro console-style UI with our official mascot: a axolotl with sunglasses. 😎

Inspired by projects such as **Flipper Zero**, **ESP32 Marauder** and **Bruce**, but built from scratch with its own personality, in Spanish, and designed for the Spanish-speaking maker community.

---

## ⚠️ Legal notice

This tool is designed for **educational and pentesting purposes in own networks or with explicit authorization**. Several of its functions (Deauther, BT Disruptor, Beacon Spam, Evil Portal, KARMA) can cause interference in third-party networks or capture other people's information.

**In Mexico and most countries, the use of these tools against other people's networks or devices without consent constitutes a federal crime** (Art. 211 bis of the Federal Penal Code in Mexico). The author is not responsible for misuse of the firmware. You are 100% responsible for how you use it.

Use wisely. 🧠

---

## 🛠️ Tools included

<div align="center">

| Category | Tools |
|:---|:---|
| 📡 **WiFi** | WiFi Scanner · Beacon Spam · Deauther · **Evil Portal** 🆕 · **Probe Sniffer** 🆕 · **KARMA Attack** 🆕 |
| 🔵 **Bluetooth** | BLE Scanner · BLE Spam · BT Disruptor |
| 📻 **2.4GHz Radio** | Jammer · Spectrum Analyzer (3 modes) |
| 📊 **Monitoring** | Packet Monitor |
| ⚙️ **System** | Settings (with Forget WiFi 🆕) · System Info · **Clock & Weather** 🆕 |

</div>

**14 functional tools** + complete system with splash, screensaver, NVS persistence, and reusable modules (virtual keyboard, WiFi config).

---

## 📸 Gallery

### Carousel style main menu

<div align="center">
<img src="img/menu.jpg" width="45%" alt="WIFI TOOLS"/>
<img src="img/menu2.jpg" width="45%" alt="RADIO TOOLS"/>
</div>

Flipper-type vertical navigation with 64x64 pixel art icons for each category. Soft slide animation, OK flash with beeps, and 5 categories: **WiFi · Radio · Bluetooth · Monitor · System**.

### Screensaver

<div align="center">
<img src="img/screensaver.jpg" width="50%" alt="Screensaver with axolotl bouncing"/>
</div>

After 30 seconds without activity, the screensaver enters: the axolotl bounces DVD-style logo with little stars twinkling in the background, rotating texts ("ESP32-TOOLS", "by PepeAngell", "ZzZ...") and uptime counter. Any button wakes him up.

---

### 📡 WiFi Tools

<div align="center">
<img src="img/wifiscanner.jpg" width="45%" alt="WiFi Scanner"/>
<img src="img/wifitools.jpg" width="45%" alt="WiFi Tools submenu"/>
</div>

**WiFi Scanner** — discover all nearby 2.4GHz networks with SSID, channel, RSSI, encryption type (WEP/WPA2/WPA3 with colors), hidden network detection and lookup from Mexican manufacturers (Telmex, Totalplay, Izzi, Megacable, AT&T, etc.) by OUI.

**Beacon Spam** — transmits hundreds of dummy WiFi networks with channel hopping (CH 1→6→11) and BSSID rotation. 5 themed modes:

<div align="center">
<img src="img/beaconspam.jpg" width="45%" alt="Beacon Spam menu"/>
<img src="img/beaconspam2.jpg" width="45%" alt="Beacon Spam active"/>
</div>

- 🌶️ **Mexipicante** — 40 spicy SSIDs in Spanish
- 🎭 **Classic Memes** — FBI_Van, Virus.exe, etc.
- 😱 **Paranoia** — "Active_Hidden_Camera", "We_are_Recording"...
- 💀 **Chaos UTF-8** — emojis and symbols only
- 🎪 **Mix Total** — all combined (~100 unique SSIDs)

Transmission rate: ~190 beacons/sec.

**Deauther** — disconnect devices from WiFi networks using deauth frames 802.11.

<div align="center">
<img src="img/deautheralert.jpg" width="45%" alt="Deauther disclaimer"/>
<img src="img/deauther.jpg" width="45%" alt="Deauther action menu"/>
</div>

- AP scan with visual selection
- Scan of connected clients (promiscuous mode)
- Targeted attack on a specific client or broadcast to the entire AP
- **Rambo Mode**: simultaneous attack on all APs with channel hopping
- Requires SDK patch (instructions in the installation section)

---

### 🆕 Evil Portal

<div align="center">
<img src="img/evilportal_modes.jpg" width="45%" alt="Evil Portal modes"/>
<img src="img/evilportal.jpg" width="45%" alt="Evil Portal main menu"/>
</div>

Full captive portal with fake AP + DNS spoofing + HTTP server. When a device connects to the ESP32 AP, all URLs are redirected to a login page that looks like Facebook, Google, Instagram or TikTok.

**2 modes available:**

- 🟢 **SIMPLE mode** — Fixed AP with one of 10 predefined SSIDs (`INFINITUM_5G_LIBRE`, `TOTALPLAY_GUESTS`, `Starbucks_Clients`, `OXXO_WiFi_Free`, etc.). Ideal for demos.
- 🔴 **CLONE + Deauth mode** — scans the real network, **clones its SSID and channel**, and simultaneously launches deauth attacks on the original network to force clients to reconnect to the clone.

**4 phishing platforms:**
- 📘 Facebook with official circular SVG
- 🟢 Google with color logo
- 📸 Instagram with gradient + camera icon
- 🎵 TikTok with cyan/magenta logo

After capturing credentials, it redirects to `/success` which bounces to `google.com` so as not to raise suspicion.

#### Persistent logs

<div align="center">
<img src="img/evilportal_logs.jpg" width="50%" alt="Logs captured"/>
</div>

Logs are saved in NVS (up to 20, circular FIFO) and persist upon reboot. Shows captured platform, email/user and password. Deleteable from the menu with confirmation.

---

### 🆕 Test Request Sniffer

<div align="center">
<img src="img/probesniffer.jpg" width="50%" alt="Probe Sniffer"/>
</div>

Promiscuous mode that captures **probe requests** — the packets sent by cell phones asking "is this saved network nearby?". Useful for discovering mobility patterns and combining it with KARMA.

- Channel hopping 1→6→11 every 2 seconds
- Deduplicates by SSID, shows times viewed counter, RSSI and "how long ago" viewed
- OK short click = sort by count
- OK hold = exit
- Up to 50 unique SSIDs in memory

---

### 🆕 KARMA Attack

<div align="center">
<img src="img/karma.jpg" width="45%" alt="KARMA Phase 1"/>
<img src="img/karma2.jpg" width="45%" alt="KARMA Phase 2 active"/>
</div>

The most sophisticated attack in firmware. Combine Probe Sniffer + Beacon Spam surgically:

1. **Phase 1** (15s) — listen to which networks nearby cell phones are searching for
2. **Phase 2** — transmits beacons by spoofing those SSIDs as existing open networks

Vulnerable devices (old Android, IoT, smart TVs, cameras) that had those networks saved as open connect automatically. Combined later with Evil Portal, it becomes a complete phishing attack.

**Actual efficiency:** ~30-50% in a crowd (iOS 14+ and Android 10+ resist KARMA by MAC randomization). Enough to demonstrate the attack and understand the risk.

---

### 🔵 Bluetooth Tools

<div align="center">
<img src="img/blescan.jpg" width="50%" alt="BLE Scanner"/>
</div>

**BLE Scanner** — discover nearby Bluetooth Low Energy devices (AirPods, smartwatches, beacons, tags, etc.). List sorted by RSSI with signal bars, vendor lookup by OUI (Apple, Samsung, Xiaomi, Microsoft, Google, and ~20 more), details screen with MAC, services advertisers and manufacturer data in hex.

**BLE Spam** — transmits fake BLE advertisements that trigger pairing popups on nearby devices. 5 protocols implemented:

- 🍎 **Apple Continuity** — AirPods Pro, AirPods Max, Beats, Apple TV popups (13 models)
- 📱 **Samsung Easy Setup** — Galaxy Buds Pro, Buds 2, Buds FE (7 models)
- 🪟 **Microsoft Swift Pair** — keyboards, Surface mouse, Xbox Controller
- 🟢 **Google Fast Pair** — Pixel Buds, Nest devices
- 🌪️ **CHAOS Mode** — rotate the 4 protocols randomly

**BT Disruptor** — targeted attack on a specific BLE device. After scanning and selecting target, generate connection flood, L2CAP ping storm, identity spoof or chaos combined. Useful for degrading BLE hearing aid/speaker connection.

---

### 📻 Radio Tools

<div align="center">
<img src="img/spectrum.jpg" width="32%" alt="Spectrum"/>
<img src="img/spectrum2.jpg" width="32%" alt="Waterfall"/>
<img src="img/sprectrum3.jpg" width="32%" alt="WiFi Chans"/>
</div>

**Radio Scanner** with NRF24L01 — 2.4GHz spectrum analyzer with 3 modes:

- **SPECTRUM** — 80 bars with vertical gradient, peak hold, geiger sound
- **WATERFALL** — 166 rows of temporal history with color map
- **WIFI CHANS** — 13 bars (one per WiFi channel), best channel recommendation

**Radio Jammer** — continuous transmission in 2.4GHz with the NRF24. 3 modes: Turbo (concentrated), Wide (±2 channels), Sweep (all 14 WiFi channels). *Note: jamming is illegal in Mexico outside of isolated educational contexts.*

---

### 📊 Packet Monitor

<div align="center">
<img src="img/packetmonitor.jpg" width="50%" alt="Packet Monitor"/>
</div>

Promiscuous sniffer of 802.11 packets per channel. Shows color-coded PPS (packets per second), vertical VU meter, 60-second historical graph and accumulated stats. 6 activity levels (QUIET → LOW → ACTIVE → BUSY → HEAVY → FLOODED) with different ambient sounds per level.

---

### 🆕 Clock & Weather

<div align="center">
<img src="img/clockweather.jpg" width="45%" alt="Clock & Weather submenu"/>
<img src="img/clockweather2.jpg" width="45%" alt="Loading weather"/>
</div>

<div align="center">
<img src="img/clockweather3.jpg" width="60%" alt="Clock & Weather main screen"/>
</div>

Complete widget with NTP + IP geolocation + live weather:

- ⏰ **Large hour in 12h format** with AM/PM (cyan in the morning, orange in the afternoon/night)
- 📅 **Date in Spanish** ("Saturday, April 25")
- 🌡️ **Current temperature + wind chill** with color coding
- 🌤 ️ **Pixel art weather icons** (sun, cloud, rain, storm, snow, fog)
- 💨 **Humidity and wind speed**
- 🌅 **Dawn and sunset time**
- 🏙️ **City detected by IP** (no GPS required)

**Free APIs without registration:**
- [ip-api.com](https://ip-api.com) for IP geolocation
- [Open-Meteo](https://open-meteo.com) for climate data

**Correct time management:** mapper IANA → POSIX so that the time is exact in each time zone, including areas without DST (Sinaloa, Sonora, Arizona) and with DST (CDMX, continental USA).

---

### 🆕 WiFi Config + Virtual Keyboard

<div align="center">
<img src="img/keyboard.jpg" width="60%" alt="Virtual keyboard typing password"/>
</div>

Reusable WiFi configuration system that any tool can invoke:

- **Silent auto-connection** with credentials saved in NVS (5 seconds)
- **Automatic scan** if there are no credentials or the saved network fails
- **Visual selection** of networks ordered by RSSI with bars and encryption type
- **Spanish QWERTY virtual keyboard** with ñ, shifted symbols, toggle capital letters, character counter and password mask
- **NVS Persistence** — the user only writes the network **once**

**Forget WiFi** available in `SYSTEM → Settings` to clear saved credentials with security confirmation (red UI).

---

## 🔧 Necessary hardware

List of components to replicate this project. All available in Mexico through Amazon, Mercado Libre or Steren for approximately **$400-500 MXN** in total.

### Main components

| Component | Specific model | Function |
|:---|:---|:---|
| **Microcontroller** | ESP32-D (ESP32-WROOM-32, 30 pins) | Brain, WiFi + integrated BT/BLE |
| **2.4GHz Radio** | 2 x NRF24L01+ | Spectrum analyzer + jammer |
| **Screen** | TFT SPI ILI9488 | Display 480x320 |
| **Buttons** | 3 × push buttons 12mm (arcade-style) | Navigation: UP / OK / DOWN |
| **Buzzer** | Not assigned on this wiring | Audio disabled due to pin conflict |
| **Battery** | LiPo 3.7V 1000mAh | Portability |
| **Charge battery** | TP4056 module with protection | USB charging |
| **DC-DC Converter** | Step-Up MT3608 adjustable to 5V | Powers ESP32 and display |
| **Switch** | 2 position slide switch | Power on/off |
| **Prototype PCB** | Perforated plate 7x9cm (or similar) | Physical assembly |

### Optional
- Dupont jumper cables (female-male, male-male)
- Pin headers 2.54mm
- Case 3D printed (pending for a next version)

---

## 🔌 Connection diagram

### ESP32 ↔ TFT SPI ILI9488 screen

| TFT screen | ESP32 (GPIO) | Function |
|:---|:---:|:---|
| VCC | 3.3V | Feeding |
| GND | GND | Land |
| SCK | 18 | Shared SPI |
| SDI / MOSI | 23 | Shared SPI |
| SDO / MISO | Offline | TFT does not use reading |
| CS | 5 | Chip Select |
| RESET | 4 | Reset |
| DC /RS | 22 | Command/Data select |
| LED | 13 | Backlight |

### ESP32 ↔ NRF24L01 #1

| NRF24L01 #1 | ESP32 (GPIO) | Function |
|:---|:---:|:---|
| VCC | 3.3V | With 100μF capacitor |
| GND | GND | Land |
| SCK | 18 | Shared SPI |
| MOSI | 23 | shared SPI |
| MISO | 19 | Shared SPI |
| CE | 27 | Chip Enable |
| CSN | 14 | Chip Select Not |

### ESP32 ↔ NRF24L01 #2

| NRF24L01 #2 | ESP32 (GPIO) | Function |

# 🦎 ESP32-TOOLS

### WiFi + Bluetooth security multi-tool firmware for ESP32

*Inspired by Flipper Zero, Bruce and ESP32 Marauder — made from scratch in Mexico*

<img src="img/splash.jpg" width="400" alt="Splash screen with axolotl"/>

**By PepeAngell** · [Instagram](https://instagram.com/pepeangelll) · [Facebook](https://www.facebook.com/esp32tools/) · [GitHub](https://github.com/pepeangell5)

![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform: ESP32](https://img.shields.io/badge/platform-ESP32-red.svg)
![Framework: Arduino](https://img.shields.io/badge/framework-Arduino-00979D.svg)
![Built with: PlatformIO](https://img.shields.io/badge/built%20with-PlatformIO-orange.svg)
![Version: 2.0](https://img.shields.io/badge/version-2.0-brightgreen.svg)
[![Web Installer](https://img.shields.io/badge/⚡_FLASH_FROM_BROWSER-fa4500?style=for-the-badge)](https://pepeangell5.github.io/ESP32-TOOLS-PRO-480x320/)
</div>

---

## 🎬 Live demo

<div align="center">
<img src="img/ESP32.gif" width="500" alt="Firmware demo browsing all tools"/>

*Complete tour of firmware menus and tools*

</div>

---

## 🆕 What's new in version 1.0

v2.0 massively expands the firmware with **6 new tools**, a full **WiFi setup system** with virtual keyboard, and several quality of life extras:

- 🌐 **Evil Portal** — captive portal with fake AP, DNS spoofing and credential capture (SIMPLE mode + CLONE+Deauth mode)
- 🎭 **KARMA Attack** — captures probes and announces them as existing networks to attract devices
- 📡 **Probe Request Sniffer** — discover the networks that search for nearby cell phones
- 🌤️ **Clock & Weather** — NTP clock + live weather with IP location detection
- ⌨️ **QWERTY Virtual Keyboard** — reusable text input with ñ and symbols
- 🌙 **Screensaver** — axolotl bouncing style DVD logo with little stars
- 🔧 **WiFi Persistent Config** — writes your network only once, it is saved
- 🗑️ **Forget WiFi** — option in Settings to forget the saved network

---

## 📖 What is ESP32-TOOLS?

**ESP32-TOOLS** is a complete firmware for an ESP32-based portable multi-tool, designed for WiFi and Bluetooth security testing. Includes network scanner, spectrum analyzer, package monitor, beacon generator, deauther, Bluetooth disruptor, evil portal, KARMA attack, live weather watch and more — all with its own retro console-style UI with our official mascot: a axolotl with sunglasses. 😎

Inspired by projects such as **Flipper Zero**, **ESP32 Marauder** and **Bruce**, but built from scratch with its own personality, in Spanish, and designed for the Spanish-speaking maker community.

---

## ⚠️ Legal notice

This tool is designed for **educational and pentesting purposes in own networks or with explicit authorization**. Several of its functions (Deauther, BT Disruptor, Beacon Spam, Evil Portal, KARMA) can cause interference in third-party networks or capture other people's information.

**In Mexico and most countries, the use of these tools against other people's networks or devices without consent constitutes a federal crime** (Art. 211 bis of the Federal Penal Code in Mexico). The author is not responsible for misuse of the firmware. You are 100% responsible for how you use it.

Use wisely. 🧠

---

## 🛠️ Tools included

<div align="center">

| Category | Tools |
|:---|:---|
| 📡 **WiFi** | WiFi Scanner · Beacon Spam · Deauther · **Evil Portal** 🆕 · **Probe Sniffer** 🆕 · **KARMA Attack** 🆕 |
| 🔵 **Bluetooth** | BLE Scanner · BLE Spam · BT Disruptor |
| 📻 **2.4GHz Radio** | Jammer · Spectrum Analyzer (3 modes) |
| 📊 **Monitoring** | Packet Monitor |
| ⚙️ **System** | Settings (with Forget WiFi 🆕) · System Info · **Clock & Weather** 🆕 |

</div>

**14 functional tools** + complete system with splash, screensaver, NVS persistence, and reusable modules (virtual keyboard, WiFi config).

---

## 📸 Gallery

### Carousel style main menu

<div align="center">
<img src="img/menu.jpg" width="45%" alt="WIFI TOOLS"/>
<img src="img/menu2.jpg" width="45%" alt="RADIO TOOLS"/>
</div>

Flipper-type vertical navigation with 64x64 pixel art icons for each category. Soft slide animation, OK flash with beeps, and 5 categories: **WiFi · Radio · Bluetooth · Monitor · System**.

### Screensaver

<div align="center">
<img src="img/screensaver.jpg" width="50%" alt="Screensaver with axolotl bouncing"/>
</div>

After 30 seconds without activity, the screensaver enters: the axolotl bounces DVD-style logo with little stars twinkling in the background, rotating texts ("ESP32-TOOLS", "by PepeAngell", "ZzZ...") and uptime counter. Any button wakes him up.

---

### 📡 WiFi Tools

<div align="center">
<img src="img/wifiscanner.jpg" width="45%" alt="WiFi Scanner"/>
<img src="img/wifitools.jpg" width="45%" alt="WiFi Tools submenu"/>
</div>

**WiFi Scanner** — discover all nearby 2.4GHz networks with SSID, channel, RSSI, encryption type (WEP/WPA2/WPA3 with colors), hidden network detection and lookup from Mexican manufacturers (Telmex, Totalplay, Izzi, Megacable, AT&T, etc.) by OUI.

**Beacon Spam** — transmits hundreds of dummy WiFi networks with channel hopping (CH 1→6→11) and BSSID rotation. 5 themed modes:

<div align="center">
<img src="img/beaconspam.jpg" width="45%" alt="Beacon Spam menu"/>
<img src="img/beaconspam2.jpg" width="45%" alt="Beacon Spam active"/>
</div>

- 🌶️ **Mexipicante** — 40 spicy SSIDs in Spanish
- 🎭 **Classic Memes** — FBI_Van, Virus.exe, etc.
- 😱 **Paranoia** — "Active_Hidden_Camera", "We_are_Recording"...
- 💀 **Chaos UTF-8** — emojis and symbols only
- 🎪 **Mix Total** — all combined (~100 unique SSIDs)

Transmission rate: ~190 beacons/sec.

**Deauther** — disconnect devices from WiFi networks using deauth frames 802.11.

<div align="center">
<img src="img/deautheralert.jpg" width="45%" alt="Deauther disclaimer"/>
<img src="img/deauther.jpg" width="45%" alt="Deauther action menu"/>
</div>

- AP scan with visual selection
- Scan of connected clients (promiscuous mode)
- Targeted attack on a specific client or broadcast to the entire AP
- **Rambo Mode**: simultaneous attack on all APs with channel hopping
- Requires SDK patch (instructions in the installation section)

---

### 🆕 Evil Portal

<div align="center">
<img src="img/evilportal_modes.jpg" width="45%" alt="Evil Portal modes"/>
<img src="img/evilportal.jpg" width="45%" alt="Evil Portal main menu"/>
</div>

Full captive portal with fake AP + DNS spoofing + HTTP server. When a device connects to the ESP32 AP, all URLs are redirected to a login page that looks like Facebook, Google, Instagram or TikTok.

**2 modes available:**

- 🟢 **SIMPLE mode** — Fixed AP with one of 10 predefined SSIDs (`INFINITUM_5G_LIBRE`, `TOTALPLAY_GUESTS`, `Starbucks_Clients`, `OXXO_WiFi_Free`, etc.). Ideal for demos.
- 🔴 **CLONE + Deauth mode** — scans the real network, **clones its SSID and channel**, and simultaneously launches deauth attacks on the original network to force clients to reconnect to the clone.

**4 phishing platforms:**
- 📘 Facebook with official circular SVG
- 🟢 Google with color logo
- 📸 Instagram with gradient + camera icon
- 🎵 TikTok with cyan/magenta logo

After capturing credentials, it redirects to `/success` which bounces to `google.com` so as not to raise suspicion.

#### Persistent logs

<div align="center">
<img src="img/evilportal_logs.jpg" width="50%" alt="Logs captured"/>
</div>

Logs are saved in NVS (up to 20, circular FIFO) and persist upon reboot. Shows captured platform, email/user and password. Deleteable from the menu with confirmation.

---

### 🆕 Test Request Sniffer

<div align="center">
<img src="img/probesniffer.jpg" width="50%" alt="Probe Sniffer"/>
</div>

Promiscuous mode that captures **probe requests** — the packets sent by cell phones asking "is this saved network nearby?". Useful for discovering mobility patterns and combining it with KARMA.

- Channel hopping 1→6→11 every 2 seconds
- Deduplicates by SSID, shows times viewed counter, RSSI and "how long ago" viewed
- OK short click = sort by count
- OK hold = exit
- Up to 50 unique SSIDs in memory

---

### 🆕 KARMA Attack

<div align="center">
<img src="img/karma.jpg" width="45%" alt="KARMA Phase 1"/>
<img src="img/karma2.jpg" width="45%" alt="KARMA Phase 2 active"/>
</div>

The most sophisticated attack in firmware. Combine Probe Sniffer + Beacon Spam surgically:

1. **Phase 1** (15s) — listen to which networks nearby cell phones are searching for
2. **Phase 2** — transmits beacons by spoofing those SSIDs as existing open networks

Vulnerable devices (old Android, IoT, smart TVs, cameras) that had those networks saved as open connect automatically. Combined later with Evil Portal, it becomes a complete phishing attack.

**Actual efficiency:** ~30-50% in a crowd (iOS 14+ and Android 10+ resist KARMA by MAC randomization). Enough to demonstrate the attack and understand the risk.

---

### 🔵 Bluetooth Tools

<div align="center">
<img src="img/blescan.jpg" width="50%" alt="BLE Scanner"/>
</div>

**BLE Scanner** — discover nearby Bluetooth Low Energy devices (AirPods, smartwatches, beacons, tags, etc.). List sorted by RSSI with signal bars, vendor lookup by OUI (Apple, Samsung, Xiaomi, Microsoft, Google, and ~20 more), details screen with MAC, services advertisers and manufacturer data in hex.

**BLE Spam** — transmits fake BLE advertisements that trigger pairing popups on nearby devices. 5 protocols implemented:

- 🍎 **Apple Continuity** — AirPods Pro, AirPods Max, Beats, Apple TV popups (13 models)
- 📱 **Samsung Easy Setup** — Galaxy Buds Pro, Buds 2, Buds FE (7 models)
- 🪟 **Microsoft Swift Pair** — keyboards, Surface mouse, Xbox Controller
- 🟢 **Google Fast Pair** — Pixel Buds, Nest devices
- 🌪️ **CHAOS Mode** — rotate the 4 protocols randomly

**BT Disruptor** — targeted attack on a specific BLE device. After scanning and selecting target, generate connection flood, L2CAP ping storm, identity spoof or chaos combined. Useful for degrading BLE hearing aid/speaker connection.

---

### 📻 Radio Tools

<div align="center">
<img src="img/spectrum.jpg" width="32%" alt="Spectrum"/>
<img src="img/spectrum2.jpg" width="32%" alt="Waterfall"/>
<img src="img/sprectrum3.jpg" width="32%" alt="WiFi Chans"/>
</div>

**Radio Scanner** with NRF24L01 — 2.4GHz spectrum analyzer with 3 modes:

- **SPECTRUM** — 80 bars with vertical gradient, peak hold, geiger sound
- **WATERFALL** — 166 rows of temporal history with color map
- **WIFI CHANS** — 13 bars (one per WiFi channel), best channel recommendation

**Radio Jammer** — continuous transmission in 2.4GHz with the NRF24. 3 modes: Turbo (concentrated), Wide (±2 channels), Sweep (all 14 WiFi channels). *Note: jamming is illegal in Mexico outside of isolated educational contexts.*

---

### 📊 Packet Monitor

<div align="center">
<img src="img/packetmonitor.jpg" width="50%" alt="Packet Monitor"/>
</div>

Promiscuous sniffer of 802.11 packets per channel. Shows color-coded PPS (packets per second), vertical VU meter, 60-second historical graph and accumulated stats. 6 activity levels (QUIET → LOW → ACTIVE → BUSY → HEAVY → FLOODED) with different ambient sounds per level.

---

### 🆕 Clock & Weather

<div align="center">
<img src="img/clockweather.jpg" width="45%" alt="Clock & Weather submenu"/>
<img src="img/clockweather2.jpg" width="45%" alt="Loading weather"/>
</div>

<div align="center">
<img src="img/clockweather3.jpg" width="60%" alt="Clock & Weather main screen"/>
</div>

Complete widget with NTP + IP geolocation + live weather:

- ⏰ **Large hour in 12h format** with AM/PM (cyan in the morning, orange in the afternoon/night)
- 📅 **Date in Spanish** ("Saturday, April 25")
- 🌡️ **Current temperature + wind chill** with color coding
- 🌤 ️ **Pixel art weather icons** (sun, cloud, rain, storm, snow, fog)
- 💨 **Humidity and wind speed**
- 🌅 **Dawn and sunset time**
- 🏙️ **City detected by IP** (no GPS required)

**Free APIs without registration:**
- [ip-api.com](https://ip-api.com) for IP geolocation
- [Open-Meteo](https://open-meteo.com) for climate data

**Correct time management:** mapper IANA → POSIX so that the time is exact in each time zone, including areas without DST (Sinaloa, Sonora, Arizona) and with DST (CDMX, continental USA).

---

### 🆕 WiFi Config + Virtual Keyboard

<div align="center">
<img src="img/keyboard.jpg" width="60%" alt="Virtual keyboard typing password"/>
</div>

Reusable WiFi configuration system that any tool can invoke:

- **Silent auto-connection** with credentials saved in NVS (5 seconds)
- **Automatic scan** if there are no credentials or the saved network fails
- **Visual selection** of networks ordered by RSSI with bars and encryption type
- **Spanish QWERTY virtual keyboard** with ñ, shifted symbols, toggle capital letters, character counter and password mask
- **NVS Persistence** — the user only writes the network **once**

**Forget WiFi** available in `SYSTEM → Settings` to clear saved credentials with security confirmation (red UI).

---

## 🔧 Necessary hardware

List of components to replicate this project. All available in Mexico through Amazon, Mercado Libre or Steren for approximately **$400-500 MXN** in total.

### Main components

| Component | Specific model | Function |
|:---|:---|:---|
| **Microcontroller** | ESP32-D (ESP32-WROOM-32, 30 pins) | Brain, WiFi + integrated BT/BLE |
| **2.4GHz Radio** | 2 x NRF24L01+ | Spectrum analyzer + jammer |
| **Screen** | TFT SPI ILI9488 | Display 480x320 |
| **Buttons** | 3 × push buttons 12mm (arcade-style) | Navigation: UP / OK / DOWN |
| **Buzzer** | Not assigned on this wiring | Audio disabled due to pin conflict |
| **Battery** | LiPo 3.7V 1000mAh | Portability |
| **Charge battery** | TP4056 module with protection | USB charging |
| **DC-DC Converter** | Step-Up MT3608 adjustable to 5V | Powers ESP32 and display |
| **Switch** | 2 position slide switch | Power on/off |
| **Prototype PCB** | Perforated plate 7x9cm (or similar) | Physical assembly |

### Optional
- Dupont jumper cables (female-male, male-male)
- Pin headers 2.54mm
- Case 3D printed (pending for a next version)

---

## 🔌 Connection diagram

### ESP32 ↔ TFT SPI ILI9488 screen

| TFT screen | ESP32 (GPIO) | Function |
|:---|:---:|:---|
| VCC | 3.3V | Feeding |
| GND | GND | Land |
| SCK | 18 | Shared SPI |
| SDI / MOSI | 23 | Shared SPI |
| SDO / MISO | Offline | TFT does not use reading |
| CS | 5 | Chip Select |
| RESET | 4 | Reset |
| DC /RS | 22 | Command/Data select |
| LED | 13 | Backlight |

### ESP32 ↔ NRF24L01 #1

| NRF24L01 #1 | ESP32 (GPIO) | Function |
|:---|:---:|:---|
| VCC | 3.3V | With 100μF capacitor |
| GND | GND | Land |
| SCK | 18 | Shared SPI |
| MOSI | 23 | shared SPI |
| MISO | 19 | Shared SPI |
| CE | 27 | Chip Enable |
| CSN | 14 | Chip Select Not |

### ESP32 ↔ NRF24L01 #2

| NRF24L01 #2 | ESP32 (GPIO) | Function |

---

## 🎬 Live demo

<div align="center">
<img src="img/ESP32.gif" width="500" alt="Firmware demo browsing all tools"/>

*Complete tour of firmware menus and tools*

</div>

---

## 🆕 What's new in version 1.0

v2.0 massively expands the firmware with **6 new tools**, a full **WiFi setup system** with virtual keyboard, and several quality of life extras:

- 🌐 **Evil Portal** — captive portal with fake AP, DNS spoofing and credential capture (SIMPLE mode + CLONE+Deauth mode)
- 🎭 **KARMA Attack** — captures probes and announces them as existing networks to attract devices
- 📡 **Probe Request Sniffer** — discover the networks that search for nearby cell phones
- 🌤️ **Clock & Weather** — NTP clock + live weather with IP location detection
- ⌨️ **QWERTY Virtual Keyboard** — reusable text input with ñ and symbols
- 🌙 **Screensaver** — axolotl bouncing style DVD logo with little stars
- 🔧 **WiFi Persistent Config** — writes your network only once, it is saved
- 🗑️ **Forget WiFi** — option in Settings to forget the saved network

---

## 📖 What is ESP32-TOOLS?

**ESP32-TOOLS** is a complete firmware for an ESP32-based portable multi-tool, designed for WiFi and Bluetooth security testing. Includes network scanner, spectrum analyzer, package monitor, beacon generator, deauther, Bluetooth disruptor, evil portal, KARMA attack, live weather watch and more — all with its own retro console-style UI with our official mascot: a axolotl with sunglasses. 😎

Inspired by projects such as **Flipper Zero**, **ESP32 Marauder** and **Bruce**, but built from scratch with its own personality, in Spanish, and designed for the Spanish-speaking maker community.

---

## ⚠️ Legal notice

This tool is designed for **educational and pentesting purposes in own networks or with explicit authorization**. Several of its functions (Deauther, BT Disruptor, Beacon Spam, Evil Portal, KARMA) can cause interference in third-party networks or capture other people's information.

**In Mexico and most countries, the use of these tools against other people's networks or devices without consent constitutes a federal crime** (Art. 211 bis of the Federal Penal Code in Mexico). The author is not responsible for misuse of the firmware. You are 100% responsible for how you use it.

Use wisely. 🧠

---

## 🛠️ Tools included

<div align="center">

| Category | Tools |
|:---|:---|
| 📡 **WiFi** | WiFi Scanner · Beacon Spam · Deauther · **Evil Portal** 🆕 · **Probe Sniffer** 🆕 · **KARMA Attack** 🆕 |
| 🔵 **Bluetooth** | BLE Scanner · BLE Spam · BT Disruptor |
| 📻 **2.4GHz Radio** | Jammer · Spectrum Analyzer (3 modes) |
| 📊 **Monitoring** | Packet Monitor |
| ⚙️ **System** | Settings (with Forget WiFi 🆕) · System Info · **Clock & Weather** 🆕 |

</div>

**14 functional tools** + complete system with splash, screensaver, NVS persistence, and reusable modules (virtual keyboard, WiFi config).

---

## 📸 Gallery

### Carousel style main menu

<div align="center">
<img src="img/menu.jpg" width="45%" alt="WIFI TOOLS"/>
<img src="img/menu2.jpg" width="45%" alt="RADIO TOOLS"/>
</div>

Flipper-type vertical navigation with 64x64 pixel art icons for each category. Soft slide animation, OK flash with beeps, and 5 categories: **WiFi · Radio · Bluetooth · Monitor · System**.

### Screensaver

<div align="center">
<img src="img/screensaver.jpg" width="50%" alt="Screensaver with axolotl bouncing"/>
</div>

After 30 seconds without activity, the screensaver enters: the axolotl bounces DVD-style logo with little stars twinkling in the background, rotating texts ("ESP32-TOOLS", "by PepeAngell", "ZzZ...") and uptime counter. Any button wakes him up.

---

### 📡 WiFi Tools

<div align="center">
<img src="img/wifiscanner.jpg" width="45%" alt="WiFi Scanner"/>
<img src="img/wifitools.jpg" width="45%" alt="WiFi Tools submenu"/>
</div>

**WiFi Scanner** — discover all nearby 2.4GHz networks with SSID, channel, RSSI, encryption type (WEP/WPA2/WPA3 with colors), hidden network detection and lookup from Mexican manufacturers (Telmex, Totalplay, Izzi, Megacable, AT&T, etc.) by OUI.

**Beacon Spam** — transmits hundreds of dummy WiFi networks with channel hopping (CH 1→6→11) and BSSID rotation. 5 themed modes:

<div align="center">
<img src="img/beaconspam.jpg" width="45%" alt="Beacon Spam menu"/>
<img src="img/beaconspam2.jpg" width="45%" alt="Beacon Spam active"/>
</div>

- 🌶️ **Mexipicante** — 40 spicy SSIDs in Spanish
- 🎭 **Classic Memes** — FBI_Van, Virus.exe, etc.
- 😱 **Paranoia** — "Active_Hidden_Camera", "We_are_Recording"...
- 💀 **Chaos UTF-8** — emojis and symbols only
- 🎪 **Mix Total** — all combined (~100 unique SSIDs)

Transmission rate: ~190 beacons/sec.

**Deauther** — disconnect devices from WiFi networks using deauth frames 802.11.

<div align="center">
<img src="img/deautheralert.jpg" width="45%" alt="Deauther disclaimer"/>
<img src="img/deauther.jpg" width="45%" alt="Deauther action menu"/>
</div>

- AP scan with visual selection
- Scan of connected clients (promiscuous mode)
- Targeted attack on a specific client or broadcast to the entire AP
- **Rambo Mode**: simultaneous attack on all APs with channel hopping
- Requires SDK patch (instructions in the installation section)

---

### 🆕 Evil Portal

<div align="center">
<img src="img/evilportal_modes.jpg" width="45%" alt="Evil Portal modes"/>
<img src="img/evilportal.jpg" width="45%" alt="Evil Portal main menu"/>
</div>

Full captive portal with fake AP + DNS spoofing + HTTP server. When a device connects to the ESP32 AP, all URLs are redirected to a login page that looks like Facebook, Google, Instagram or TikTok.

**2 modes available:**

- 🟢 **SIMPLE mode** — Fixed AP with one of 10 predefined SSIDs (`INFINITUM_5G_LIBRE`, `TOTALPLAY_GUESTS`, `Starbucks_Clients`, `OXXO_WiFi_Free`, etc.). Ideal for demos.
- 🔴 **CLONE + Deauth mode** — scans the real network, **clones its SSID and channel**, and simultaneously launches deauth attacks on the original network to force clients to reconnect to the clone.

**4 phishing platforms:**
- 📘 Facebook with official circular SVG
- 🟢 Google with color logo
- 📸 Instagram with gradient + camera icon
- 🎵 TikTok with cyan/magenta logo

After capturing credentials, it redirects to `/success` which bounces to `google.com` so as not to raise suspicion.

#### Persistent logs

<div align="center">
<img src="img/evilportal_logs.jpg" width="50%" alt="Logs captured"/>
</div>

Logs are saved in NVS (up to 20, circular FIFO) and persist upon reboot. Shows captured platform, email/user and password. Deleteable from the menu with confirmation.

---

### 🆕 Test Request Sniffer

<div align="center">
<img src="img/probesniffer.jpg" width="50%" alt="Probe Sniffer"/>
</div>

Promiscuous mode that captures **probe requests** — the packets sent by cell phones asking "is this saved network nearby?". Useful for discovering mobility patterns and combining it with KARMA.

- Channel hopping 1→6→11 every 2 seconds
- Deduplicates by SSID, shows times viewed counter, RSSI and "how long ago" viewed
- OK short click = sort by count
- OK hold = exit
- Up to 50 unique SSIDs in memory

---

### 🆕 KARMA Attack

<div align="center">
<img src="img/karma.jpg" width="45%" alt="KARMA Phase 1"/>
<img src="img/karma2.jpg" width="45%" alt="KARMA Phase 2 active"/>
</div>

The most sophisticated attack in firmware. Combine Probe Sniffer + Beacon Spam surgically:

1. **Phase 1** (15s) — listen to which networks nearby cell phones are searching for
2. **Phase 2** — transmits beacons by spoofing those SSIDs as existing open networks

Vulnerable devices (old Android, IoT, smart TVs, cameras) that had those networks saved as open connect automatically. Combined later with Evil Portal, it becomes a complete phishing attack.

**Actual efficiency:** ~30-50% in a crowd (iOS 14+ and Android 10+ resist KARMA by MAC randomization). Enough to demonstrate the attack and understand the risk.

---

### 🔵 Bluetooth Tools

<div align="center">
<img src="img/blescan.jpg" width="50%" alt="BLE Scanner"/>
</div>

**BLE Scanner** — discover nearby Bluetooth Low Energy devices (AirPods, smartwatches, beacons, tags, etc.). List sorted by RSSI with signal bars, vendor lookup by OUI (Apple, Samsung, Xiaomi, Microsoft, Google, and ~20 more), details screen with MAC, services advertisers and manufacturer data in hex.

**BLE Spam** — transmits fake BLE advertisements that trigger pairing popups on nearby devices. 5 protocols implemented:

- 🍎 **Apple Continuity** — AirPods Pro, AirPods Max, Beats, Apple TV popups (13 models)
- 📱 **Samsung Easy Setup** — Galaxy Buds Pro, Buds 2, Buds FE (7 models)
- 🪟 **Microsoft Swift Pair** — keyboards, Surface mouse, Xbox Controller
- 🟢 **Google Fast Pair** — Pixel Buds, Nest devices
- 🌪️ **CHAOS Mode** — rotate the 4 protocols randomly

**BT Disruptor** — targeted attack on a specific BLE device. After scanning and selecting target, generate connection flood, L2CAP ping storm, identity spoof or chaos combined. Useful for degrading BLE hearing aid/speaker connection.

---

### 📻 Radio Tools

<div align="center">
<img src="img/spectrum.jpg" width="32%" alt="Spectrum"/>
<img src="img/spectrum2.jpg" width="32%" alt="Waterfall"/>
<img src="img/sprectrum3.jpg" width="32%" alt="WiFi Chans"/>
</div>

**Radio Scanner** with NRF24L01 — 2.4GHz spectrum analyzer with 3 modes:

- **SPECTRUM** — 80 bars with vertical gradient, peak hold, geiger sound
- **WATERFALL** — 166 rows of temporal history with color map
- **WIFI CHANS** — 13 bars (one per WiFi channel), best channel recommendation

**Radio Jammer** — continuous transmission in 2.4GHz with the NRF24. 3 modes: Turbo (concentrated), Wide (±2 channels), Sweep (all 14 WiFi channels). *Note: jamming is illegal in Mexico outside of isolated educational contexts.*

---

### 📊 Packet Monitor

<div align="center">
<img src="img/packetmonitor.jpg" width="50%" alt="Packet Monitor"/>
</div>

Promiscuous sniffer of 802.11 packets per channel. Shows color-coded PPS (packets per second), vertical VU meter, 60-second historical graph and accumulated stats. 6 activity levels (QUIET → LOW → ACTIVE → BUSY → HEAVY → FLOODED) with different ambient sounds per level.

---

### 🆕 Clock & Weather

<div align="center">
<img src="img/clockweather.jpg" width="45%" alt="Clock & Weather submenu"/>
<img src="img/clockweather2.jpg" width="45%" alt="Loading weather"/>
</div>

<div align="center">
<img src="img/clockweather3.jpg" width="60%" alt="Clock & Weather main screen"/>
</div>

Complete widget with NTP + IP geolocation + live weather:

- ⏰ **Large hour in 12h format** with AM/PM (cyan in the morning, orange in the afternoon/night)
- 📅 **Date in Spanish** ("Saturday, April 25")
- 🌡️ **Current temperature + wind chill** with color coding
- 🌤 ️ **Pixel art weather icons** (sun, cloud, rain, storm, snow, fog)
- 💨 **Humidity and wind speed**
- 🌅 **Dawn and sunset time**
- 🏙️ **City detected by IP** (no GPS required)

**Free APIs without registration:**
- [ip-api.com](https://ip-api.com) for IP geolocation
- [Open-Meteo](https://open-meteo.com) for climate data

**Correct time management:** mapper IANA → POSIX so that the time is exact in each time zone, including areas without DST (Sinaloa, Sonora, Arizona) and with DST (CDMX, continental USA).

---

### 🆕 WiFi Config + Virtual Keyboard

<div align="center">
<img src="img/keyboard.jpg" width="60%" alt="Virtual keyboard typing password"/>
</div>

Reusable WiFi configuration system that any tool can invoke:

- **Silent auto-connection** with credentials saved in NVS (5 seconds)
- **Automatic scan** if there are no credentials or the saved network fails
- **Visual selection** of networks ordered by RSSI with bars and encryption type
- **Spanish QWERTY virtual keyboard** with ñ, shifted symbols, toggle capital letters, character counter and password mask
- **NVS Persistence** — the user only writes the network **once**

**Forget WiFi** available in `SYSTEM → Settings` to clear saved credentials with security confirmation (red UI).

---

## 🔧 Necessary hardware

List of components to replicate this project. All available in Mexico through Amazon, Mercado Libre or Steren for approximately **$400-500 MXN** in total.

### Main components

| Component | Specific model | Function |
|:---|:---|:---|
| **Microcontroller** | ESP32-D (ESP32-WROOM-32, 30 pins) | Brain, WiFi + integrated BT/BLE |
| **2.4GHz Radio** | 2 x NRF24L01+ | Spectrum analyzer + jammer |
| **Screen** | TFT SPI ILI9488 | Display 480x320 |
| **Buttons** | 3 × push buttons 12mm (arcade-style) | Navigation: UP / OK / DOWN |
| **Buzzer** | Not assigned on this wiring | Audio disabled due to pin conflict |
| **Battery** | LiPo 3.7V 1000mAh | Portability |
| **Charge battery** | TP4056 module with protection | USB charging |
| **DC-DC Converter** | Step-Up MT3608 adjustable to 5V | Powers ESP32 and display |
| **Switch** | 2 position slide switch | Power on/off |
| **Prototype PCB** | Perforated plate 7x9cm (or similar) | Physical assembly |

### Optional
- Dupont jumper cables (female-male, male-male)
- Pin headers 2.54mm
- Case 3D printed (pending for a next version)

---

## 🔌 Connection diagram

### ESP32 ↔ TFT SPI ILI9488 screen

| TFT screen | ESP32 (GPIO) | Function |
|:---|:---:|:---|
| VCC | 3.3V | Feeding |
| GND | GND | Land |
| SCK | 18 | Shared SPI |
| SDI / MOSI | 23 | Shared SPI |
| SDO / MISO | Offline | TFT does not use reading |
| CS | 5 | Chip Select |
| RESET | 4 | Reset |
| DC /RS | 22 | Command/Data select |
| LED | 13 | Backlight |

### ESP32 ↔ NRF24L01 #1

| NRF24L01 #1 | ESP32 (GPIO) | Function |
|:---|:---:|:---|
| VCC | 3.3V | With 100μF capacitor |
| GND | GND | Land |
| SCK | 18 | Shared SPI |
| MOSI | 23 | shared SPI |
| MISO | 19 | Shared SPI |
| CE | 27 | Chip Enable |
| CSN | 14 | Chip Select Not |

### ESP32 ↔ NRF24L01 #2

| NRF24L01 #2 | ESP32 (GPIO) | Function |**By PepeAngell** · [Instagram](https://instagram.com/pepeangelll) · [Facebook](https://www.facebook.com/esp32tools/) · [GitHub](https://github.com/pepeangell5)

![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform: ESP32](https://img.shields.io/badge/platform-ESP32-red.svg)
![Framework: Arduino](https://img.shields.io/badge/framework-Arduino-00979D.svg)
![Built with: PlatformIO](https://img.shields.io/badge/built%20with-PlatformIO-orange.svg)
![Version: 2.0](https://img.shields.io/badge/version-2.0-brightgreen.svg)
[![Web Installer](https://img.shields.io/badge/⚡_FLASH_FROM_BROWSER-fa4500?style=for-the-badge)](https://pepeangell5.github.io/ESP32-TOOLS-PRO-480x320/)
</div>

---

## 🎬 Live demo

<div align="center">
<img src="img/ESP32.gif" width="500" alt="Firmware demo browsing all tools"/>

*Complete tour of firmware menus and tools*

</div>

---

## 🆕 What's new in version 2.0

v2.0 massively expands the firmware with **6 new tools**, a full **WiFi setup system** with virtual keyboard, and several quality of life extras:

- 🌐 **Evil Portal** — Captive portal with fake AP, DNS spoofing, and credential capture (SIMPLE mode + CLONE+Deauth mode).
- 🎭 **KARMA Attack** — Captures probe requests and announces them as existing networks to attract devices.
- 📡 **Probe Request Sniffer** — Discover networks that nearby mobile devices are searching for.
- 🌤️ **Clock & Weather** — NTP clock + live weather with IP location detection.
- ⌨️ **QWERTY Virtual Keyboard** — Reusable text input supporting symbols and special characters.
- 🌙 **Screensaver** — Bouncing axolotl DVD-style logo with uptime counter.
- 🔧 **WiFi Persistent Config** — Save credentials to NVS so you only have to enter them once.
- 🗑️ **Forget WiFi** — Option in Settings to clear saved credentials.

---

## 📖 What is ESP32-TOOLS?

**ESP32-TOOLS** is a comprehensive firmware for ESP32-based portable multi-tools, designed for WiFi and Bluetooth security testing. It includes a network scanner, spectrum analyzer, packet monitor, beacon generator, deauther, BLE disruptor, and more—all featuring a retro console-style UI hosted by our official mascot: a sunglasses-wearing axolotl. 😎

Inspired by the **Flipper Zero**, **ESP32 Marauder**, and **Bruce**, this project was built from the ground up to provide the Spanish-speaking maker community with a powerful, personalized security tool.

---

## ⚠️ Legal notice

This tool is designed for **educational and penetration testing purposes on your own networks or with explicit authorization**. Several functions (such as the Deauther, BT Disruptor, and KARMA attack) can cause interference or capture information.

**In Mexico and many other jurisdictions, using these tools against networks you do not own or have permission to test may be illegal.** The author is not responsible for misuse of this firmware. Use it responsibly.

---

## 🛠️ Tools included

<div align="center">

| Category | Tools |
|:---|:---|
| 📡 **WiFi** | WiFi Scanner · Beacon Spam · Deauther · **Evil Portal** 🆕 · **Probe Sniffer** 🆕 · **KARMA Attack** 🆕 |
| 🔵 **Bluetooth** | BLE Scanner · BLE Spam · BT Disruptor |
| 📻 **2.4GHz Radio** | Jammer · Spectrum Analyzer (3 modes) |
| 📊 **Monitoring** | Packet Monitor |
| ⚙️ **System** | Settings (with Forget WiFi 🆕) · System Info · **Clock & Weather** 🆕 |

</div>

**14 functional tools** powered by a custom system featuring a splash screen, screensaver, NVS persistence, and modular helper components.

---

## 📸 Gallery

### Carousel Main Menu
<div align="center">
<img src="img/menu.jpg" width="45%" alt="WIFI TOOLS"/>
<img src="img/menu2.jpg" width="45%" alt="RADIO TOOLS"/>
</div>

Flipper-style vertical navigation with 64x64 pixel art icons. Features smooth slide animations and audio feedback via beeps.

### Screensaver
<div align="center">
<img src="img/screensaver.jpg" width="50%" alt="Screensaver with axolotl bouncing"/>
</div>

Activates after 30 seconds of inactivity. Features a DVD-style bouncing axolotl with randomly rotating slogans and an uptime counter.

---

## 📡 WiFi Tools Detail

**WiFi Scanner** — Detects nearby 2.4GHz networks, displaying SSID, channel, signal strength (RSSI), encryption type, and identifies Mexican ISPs (Telmex, Totalplay, etc.) via OUI lookup.

**Beacon Spam** — Floods the area with hundreds of dummy WiFi networks. Choose from themed SSID lists:
- 🌶️ **Mexipicante** — Spicy Spanish terms.
- 🎭 **Classic Memes** — E.g., "FBI Surveillance Van".
- 😱 **Paranoia** — "Your Device is Compromised".
- 💀 **Chaos UTF-8** — Random symbols and emojis.
- 🎪 **Mix Total** — A combination of all of the above.

**Deauther** — Forces devices to disconnect from a WiFi network. 
- Individual AP scanning and selection.
- Client scanning in promiscuous mode.
- Targeted deauth or "Rambo Mode" (all nearby APs).

**Evil Portal** — Creates a rogue AP that redirects users to a phishing page.
- **Simple Mode:** Uses predefined common SSIDs.
- **Clone Mode:** Spoofs a real nearby SSID and Deauths clients to force them onto the fake portal.
- **Platforms:** Choose between Facebook, Google, Instagram, or TikTok login themes.

**KARMA Attack** — A two-phase attack:
1. **Listening:** Monitors probe requests to see which networks devices are looking for.
2. **Spoofing:** Broadcasts those specific SSIDs to trick devices into connecting automatically.

---

## 🔵 Bluetooth & Radio Tools

**BLE Scanner & Spam** — Scan for BLE devices (AirPods, watches, etc.) and send advertisement packets to trigger pop-ups on iPhones, Samsung, Google, and Windows devices.

**Radio Scanner (NRF24L01)** — Visualize the 2.4GHz spectrum in three modes:
- **Spectrum:** Real-time bar graph.
- **Waterfall:** Temporal heat map of signal activity.
- **WiFi Chans:** Recommends the least congested WiFi channel.

---

## 📁 Required Hardware

| Component | Recommended Model | Purpose |
|:---|:---|:---|
| **Microcontroller** | ESP32-WROOM-32 (30-pin) | Core CPU & Wireless |
| **Screen** | TFT SPI ILI9488 | User Interface |
| **2.4GHz Radios** | 2x NRF24L01+ | Spectrum Analysis & Jamming |
| **Input** | 3x Push Buttons | Navigation (Up/Down/OK) |
| **Power** | 3.7V LiPo + TP4056 + MT3608 | Portable Power |

---

## 🔌 Wiring Guide

### ESP32 ↔ TFT Screen
| TFT | ESP32 | Function |
|:---|:---:|:---|
| VCC | 3.3V | Power |
| GND | GND | Ground |
| SCK | 18 | SPI Clock |
| SDI/MOSI | 23 | SPI Data |
| CS | 5 | Chip Select |
| RESET | 4 | Reset |
| DC/RS | 22 | Data/Command |
| LED | 13 | Backlight |

### ESP32 ↔ NRF24L01 Modules
| NRF24 | ESP32 | Function |
|:---|:---:|:---|
| VCC | 3.3V | Power |
| GND | GND | Ground |
| SCK | 18 | Shared SPI |
| MOSI | 23 | Shared SPI |
| MISO | 19 | Shared SPI |
| CE | 27 / 17 | Chip Enable |
| CSN | 14 / 16 | Chip Select |

---

## 🚀 Installation

### Web Flasher (Easiest)
1. Open [Web Installer](https://pepeangell5.github.io/ESP32-TOOLS-PRO-480x320/) in Chrome or Edge.
2. Connect ESP32 via USB.
3. Click **⚡ INSTALL NOW ⚡**.

### From Source (PlatformIO)
1. Clone the repo: `git clone https://github.com/pepeangell5/ESP32-TOOLS-PRO-480x320.git`
2. Open in VS Code with PlatformIO installed.
3. Build and Upload.

**⚠️ Deauther Patch:** If compiling from source, you must apply the `objcopy` patch to `libnet80211.a` (see the "Patch for the Deauther" section in the source tree) to enable raw frame transmission.

---

## 📜 License
This project is open-source under the **MIT License**. Feel free to build, modify, and share.
