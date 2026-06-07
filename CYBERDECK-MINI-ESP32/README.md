# CYBERDECK MINI ESP32

[![Web Flasher](https://img.shields.io/badge/WEB_FLASHER-INSTALL-1dff8f?style=for-the-badge&logo=espressif&logoColor=001008)](https://pepeangell5.github.io/CYBERDECK-MINI-ESP32/)

Firmware for a portable cyberdeck based on the ESP32-S3, featuring a ST7789 240x320 TFT screen, dual nRF24L01 radios, NEO-6M GPS, microSD card slot, rotary encoder, and physical buttons. This project is designed for educational purposes, defensive monitoring, hardware diagnostics, and cybersecurity demonstrations within a legal and ethical framework.

> Use this firmware only on your own networks, devices, or in laboratories with explicit authorization. The radio, WiFi, and Bluetooth tools are intended for responsible testing and educational use.

## Web Flasher

You can flash the complete firmware directly from your browser using ESP Web Tools via Chrome, Edge, or Opera:

https://pepeangell5.github.io/CYBERDECK-MINI-ESP32/

![Main Menu](img/menu_principal.JPG)

## Project Status

- Interface adapted for the ST7789 240x320 TFT screen in landscape orientation.
- Navigation via 4 physical buttons and a rotary encoder.
- Opening splash screen featuring the axolotl mascot.
- Dedicated SPI bus for the microSD card.
- **GPS Tools Pro**: Includes a professional dashboard, CSV logger, motion-based compass, and waypoint system.
- **MicroSD Manager**: File browser with text viewer for `.txt`, `.csv`, `.log`, `.json`, `.md`, `.nmea`, and `.gps` files.
- Defensive security tools for WiFi, BLE, and 2.4 GHz radio.
- Capability to export reports directly to the microSD card.

## Gallery

| Main Menu | WiFi Tools |
| --- | --- |
| ![Main Menu](img/menu_principal.JPG) | ![WiFi tools](img/wifi_tool.JPG) |

| WiFi Tools 2 | Radio Tools |
| --- | --- |
| ![WiFi tools 2](img/wifi_tool_2.JPG) | ![Radio tools](img/radio_tool.JPG) |

| Bluetooth | Packet Monitor |
| --- | --- |
| ![Bluetooth](img/bluetooth.JPG) | ![Packet monitor](img/pkt_monitor.JPG) |

| System | System Tools |
| --- | --- |
| ![System](img/system.JPG) | ![System tools](img/system2.JPG) |

| Threat Monitor |
| --- |
| ![Threat monitor](img/threat_mon.JPG) |

## Target Hardware

- ESP32-S3 DevKitC-1 N8 or compatible.
- ST7789 SPI TFT Screen (240x320).
- 2 x nRF24L01 modules.
- NEO-6M GPS module (via UART1).
- MicroSD card reader (dedicated SPI).
- Rotary encoder with push-button.
- 4 x physical push-buttons (UP, DOWN, ENTER, BACK).
- Passive buzzer.
- Battery voltage monitoring via ADC (2.2k / 1k resistive divider).

## Pinout

| Peripheral | Function | GPIO |
| --- | --- | --- |
| TFT ST7789 | SCK | 12 |
| TFT ST7789 | MOSI | 11 |
| TFT ST7789 | MISO | 13 |
| TFT ST7789 | CS | 10 |
| TFT ST7789 | DC | 21 |
| TFT ST7789 | RST | 14 |
| nRF24 #1 | CE / CSN | 4 / 5 |
| nRF24 #2 | CE / CSN | 6 / 7 |
| microSD | SCK / MOSI / MISO / CS | 36 / 35 / 37 / 16 |
| GPS NEO-6M | RX / TX | 18 / 17 |
| Buttons | UP / DOWN / ENTER / BACK | 1 / 2 / 42 / 41 |
| Encoder | CLK / DT / SW | 40 / 39 / 38 |
| Buzzer | Signal | 15 |
| Battery ADC | VBAT | 9 |

## Navigation

- `UP` / `DOWN`: Change selection.
- Rotary Encoder: Navigate menus and compatible tools.
- `ENTER` / `OK`: Select, open, or execute action.
- `BACK`: Return or exit.
- `HOLD OK`: Alternative back button or secondary action (when indicated on screen).

## Main Features

### WiFi
- **WiFi Scanner**: Detailed view of SSID, BSSID, channel, signal strength (RSSI), and encryption.
- **Threat Monitor**: Detects anomalous activity such as beacon spam or deauth/disassociation events.
- **WiFi Audit**: Identification of open, weak, or hidden networks and potential clones.
- **Probe Sniffer**: Passive monitoring of probe requests.
- Ability to export findings to the microSD card.

### 2.4 GHz Radio
- **Spectrum Analyzer**: Three different visualization modes.
- **RF Baseline**: Established a baseline of current activity to detect future changes.
- **Export**: Save baseline as `/RF_BASELINE.txt` on microSD.
- Support for dual nRF24L01 modules.

### Bluetooth / BLE
- **BLE Defense**: Passive auditing of nearby BLE devices.
- **BLE Scanner**: Lists nearby devices with detailed info.
- **Export**: Save scan logs as `/BLE_AUDIT.txt` on microSD.

### GPS Tools Pro
- **Pro Dashboard**: Real-time display of fixes, satellites, HDOP, age, lat/long, altitude, speed, heading, and UTC.
- **Track Logger**: Logs coordinates to `/GPS_TRACK.csv`.
- **Waypoint Mark**: Saves current location to `/GPS_MARKS.csv`.
- **Heading Compass**: GPS-based movement compass.
- **Snapshot**: Saves current status to `/GPS_SNAPSHOT.txt`.
- **NMEA Console**: Live view for diagnostic purposes.

### MicroSD Manager
- **File Browser**: View and read `.txt`, `.csv`, `.log`, `.json`, `.md`, `.nmea`, and `.gps` files.
- **Quick Reports**: One-click access to generated reports.
- **Folder Management**: Pre-created folders (`/GPS`, `/REPORTS`, `/LOGS`, etc.).
- **Secure Clean**: Confirm via long-press to wipe reports.
- **SD Info**: Displays card capacity, type, and SPI speed.

### System
- **Mission Dashboard**: General status for battery, GPS, SD card, and radios.
- **Battery**: Estimates remaining capacity for 1S Li-ion/LiPo batteries.
- **General Utilities**: Clock & Weather, System Info, Settings, and About.

## Generated Files (on MicroSD)

| File | Origin |
| --- | --- |
| `/GPS_TRACK.csv` | GPS Track Logger |
| `/GPS_MARKS.csv` | Dashboard Pro / Waypoint Mark |
| `/GPS_SNAPSHOT.txt` | Export Snapshot |
| `/THREAT_REPORT.txt` | Threat Monitor |
| `/WIFI_DEFENSE.txt` | WiFi Audit |
| `/WIFI_AUDIT.csv` | Audit Reports |
| `/RF_BASELINE.txt` | RF Baseline |
| `/BLE_AUDIT.txt` | BLE Defense |
| `/BATTERY_STATUS.txt` | Battery report |
| `/SD_INDEX.txt` | MicroSD Manager |

## Compilation

Install PlatformIO and execute:

```powershell
pio run
```

## Uploading to ESP32-S3

Connect your device via USB and run:

```powershell
pio run -t upload
```

*Note: If the port is not detected, check your USB cable, drivers, or put the ESP32-S3 into BOOT mode.*

## Flashing Options

| Method | Use Case | File/Link |
| --- | --- | --- |
| **Web Flasher** | Quick installation from browser | [Web Installer](https://pepeangell5.github.io/CYBERDECK-MINI-ESP32/) |
| **Merged Bin** | Single file flash for external tools | `archivos bin/CYBERDECK-MINI-ESP32-firmware-merged.bin` at `0x0` |
| **Separate Bin** | Advanced manual flashing | `bootloader.bin` (0x0), `partitions.bin` (0x8000), `boot_app0.bin` (0xE000), `firmware.bin` (0x10000) |
| **PlatformIO** | Development and source mods | `pio run -t upload` |

## Project Structure

```text
include/      Firmware headers
src/          Core implementation
img/          README screenshots
archivos bin/ Binaries for web flashing/external tools
```

## Socials
- Web Flasher: https://pepeangell5.github.io/CYBERDECK-MINI-ESP32/

## License
Refer to `LICENSE` file for details.
