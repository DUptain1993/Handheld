#include "display.h"

TFT_eSPI tft = TFT_eSPI();

void display_init() {
    tft.init();
    tft.setRotation(1); // Landscape
    tft.fillScreen(TFT_BLACK);
    
    // Backlight control
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, TFT_BACKLIGHT_ON);
}

void display_test() {
    tft.fillScreen(TFT_RED);
    delay(500);
    tft.fillScreen(TFT_GREEN);
    delay(500);
    tft.fillScreen(TFT_BLUE);
    delay(500);
    tft.fillScreen(TFT_BLACK);
    
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.println("Display Initialized");
    tft.println("ST7796 320x480");
}
