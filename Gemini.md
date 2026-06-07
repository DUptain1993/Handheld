PROJECT: Handheld Cyberdeck (Hybrid Pi + ESP32 UI + ESP32-S3 AI)

You are acting as an embedded systems architect and firmware engineer.

Your task is to analyze this repository and generate minimal, functional, step-by-step firmware and system architecture based ONLY on the provided folders.

---

IMPORTANT: SOURCE OF TRUTH (DO NOT IGNORE)

1. DISPLAY + ESP32-32E HARDWARE

Folder:
3.5inch_ESP32-32E_ST7796_E32R35T_E32N35T_V1.0

This is the PRIMARY HARDWARE REFERENCE.

It contains:
- Display driver (ST7796)
- Pin mappings
- SPI configuration
- Touch configuration

RULES:
- DO NOT guess display driver → it is ST7796
- DO NOT invent pin mappings → use this folder ONLY
- DO NOT override configs unless explicitly required

---

2. RASPBERRY PI BACKEND SYSTEM

Folder:
kali-arm

This contains:
- Kali ARM build scripts
- Nexmon modifications

Use this as:
- backend execution system
- WiFi/network tool engine
- payload runner

RULES:
- ESP32 does NOT perform heavy operations
- ALL real actions happen on Raspberry Pi

---

3. RADIO MODULE DEFINITIONS

Folder:
T-Embed-CC1101

Contains:
- CC1101 info
- nRF24L01 references
- RF hardware details

RULES:
- modules are OPTIONAL
- only ONE module active at a time
- avoid complex simultaneous SPI usage

---

4. UI + CYBERDECK LOGIC REFERENCES

Folders:
CYBERDECK-MINI-ESP32
ESP32-TOOLS-PRO-480x320

These define:
- menu structure
- UI concepts
- tool layouts

RULES:
- DO NOT copy full firmware directly
- SIMPLIFY heavily
- ADAPT to current hardware constraints

---

5. SYSTEM DESIGN FILES

Use:
- goals.txt
- idea.txt

These define:
- architecture
- system purpose
- design philosophy

DO NOT ignore them.

---

SYSTEM ARCHITECTURE:

This system contains THREE processing nodes:

1. ESP32-32E
   - UI controller
   - controls display (ST7796)
   - handles touchscreen input
   - sends commands

---

2. ESP32-S3-WROOM-1U
   - edge AI / assistive processor
   - runs ESP-IDF
   - handles lightweight logic

---

3. Raspberry Pi Zero W
   - backend system
   - runs Kali ARM + Nexmon
   - executes commands and tools

---

COMMUNICATION MODEL:

ESP32-32E → Raspberry Pi
- Primary: HTTP over WiFi
- Backup: UART

ESP32-32E → ESP32-S3
- UART preferred

ESP32-S3 → Raspberry Pi
- optional advanced routing

---

FIRMWARE DEVELOPMENT RULES:

1. BUILD IN STRICT PHASES

DO NOT skip steps.

PHASE 1:
- initialize display ONLY (ST7796)
- no UI logic

PHASE 2:
- enable touchscreen input

PHASE 3:
- simple UI (max 3 buttons)

PHASE 4:
- connect to WiFi

PHASE 5:
- send HTTP request to Raspberry Pi

PHASE 6:
- display response text

PHASE 7:
- expand UI menu system

PHASE 8:
- integrate ESP32-S3

---

2. SIMPLICITY FIRST

- minimal code
- no heavy frameworks
- no unnecessary abstraction

---

3. DISPLAY RULES

- use TFT_eSPI if compatible with ST7796
- configuration MUST match:
  3.5inch_ESP32-32E_ST7796_E32R35T_E32N35T_V1.0

- DO NOT guess pins

---

4. TOUCH RULES

- resistive touch expected
- likely XPT2046
- verify using hardware folder

---

5. UI STRUCTURE (SIMPLIFIED)

Initial menu:

[ WiFi Tools ]
[ Payloads ]
[ System Info ]

Later expansion:

[ AI Tools ]
[ RF Tools ]

---

6. BACKEND EXECUTION MODEL

ALL commands:

1. ESP32 sends request to Pi
2. Pi executes script (kali-arm system)
3. Pi returns text output
4. ESP32 displays result

Example:

GET /cmd?run=wifi_scan

---

7. ESP32-S3 (EDGE AI RULES)

- keep logic lightweight
- avoid heavy AI frameworks initially

Allowed:
- rule-based logic
- simple filtering
- prediction heuristics

NOT allowed (initially):
- complex ML stacks
- large models

---

8. HARDWARE CONSTRAINTS (VERY IMPORTANT)

- no PCB
- no breadboard
- direct wiring only
- unstable power possible

Therefore:
- minimize wires
- keep SPI simple
- avoid high pin usage

---

9. OUTPUT REQUIREMENTS

Generated code must:

- compile
- be minimal
- work as standalone tests
- not depend on missing hardware

---

10. FAILURE CONDITIONS (DO NOT DO THESE)

- guessing pin mappings
- ignoring 3.5inch hardware folder
- copying full cyberdeck firmware blindly
- mixing ESP-IDF and Arduino in same component
- generating full system at once

---

EXPECTED OUTPUT STRUCTURE:

/firmware
  /esp32_ui
    main.cpp
    display.cpp
    touch.cpp
    comms.cpp

  /esp32_s3_ai
    main.c
    ai_logic.c

  /pi_scripts
    wifi_scan.sh
    payload.sh

---

FIRST TASK (MANDATORY):

1. Analyze:
   3.5inch_ESP32-32E_ST7796_E32R35T_E32N35T_V1.0

2. Identify:
   - correct driver (ST7796)
   - exact pin mapping

3. Generate:

- minimal display initialization code ONLY

DO NOT:
- build UI yet
- add WiFi yet
- add touch yet

STOP after display works.
