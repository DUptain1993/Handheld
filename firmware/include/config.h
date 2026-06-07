#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
#define WIFI_SSID "Cyberdeck_Net"
#define WIFI_PASSWORD "cyberdeck123"

// Backend Configuration
#define BACKEND_HOST "192.168.4.1"
#define BACKEND_PORT 80

// UI Configuration
#define UI_BG_COLOR       0x0000 // Black
#define UI_TEXT_COLOR     0xFFFF // White
#define UI_ACCENT_COLOR   0x07E0 // Green
#define UI_SELECT_COLOR   0xFBE0 // Orange/Yellow
#define UI_BUTTON_COLOR   0x18E3 // Dark Gray/Blue
#define UI_HEADER_BG      0x0124 // Dark Blue

// Display Settings
#define DISPLAY_WIDTH  480
#define DISPLAY_HEIGHT 320
#define DISPLAY_ROTATION 1 // Landscape

// Touch Calibration (from hardware demo)
#define TOUCH_CAL_DATA { 263, 3443, 256, 3643, 4 }

// Memory Limits
#define MAX_RESPONSE_SIZE 2048

#endif
