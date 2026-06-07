#include "display.h"
#include "../include/config.h"

TFT_eSPI tft = TFT_eSPI();

void display_init() {
    tft.init();
    tft.setRotation(DISPLAY_ROTATION);
    tft.fillScreen(UI_BG_COLOR);
    
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, TFT_BACKLIGHT_ON);
}

void display_clear() {
    tft.fillScreen(UI_BG_COLOR);
}

void display_print(const char* text, int x, int y, int size, uint16_t color) {
    tft.setTextColor(color);
    tft.setTextSize(size);
    tft.setCursor(x, y);
    tft.print(text);
}
