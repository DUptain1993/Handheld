#include "ui.h"
#include "display.h"
#include "../include/config.h"

void ui_init() {
    display_clear();
}

void ui_draw_header(const char* title) {
    tft.fillRect(0, 0, DISPLAY_WIDTH, 40, UI_HEADER_BG);
    tft.drawFastHLine(0, 40, DISPLAY_WIDTH, UI_ACCENT_COLOR);
    display_print(title, 10, 10, 2, UI_TEXT_COLOR);
}

void ui_draw_button(int x, int y, int w, int h, const char* label, bool highlighted) {
    uint16_t color = highlighted ? UI_SELECT_COLOR : UI_BUTTON_COLOR;
    uint16_t textColor = highlighted ? UI_BG_COLOR : UI_TEXT_COLOR;
    
    tft.fillRoundRect(x, y, w, h, 8, color);
    tft.drawRoundRect(x, y, w, h, 8, UI_ACCENT_COLOR);
    
    int tw = strlen(label) * 12;
    display_print(label, x + (w - tw) / 2, y + (h - 16) / 2, 2, textColor);
}

void ui_draw_list_item(int x, int y, int w, int h, const char* label, bool selected) {
    uint16_t color = selected ? UI_SELECT_COLOR : UI_BG_COLOR;
    uint16_t textColor = selected ? UI_BG_COLOR : UI_TEXT_COLOR;
    
    tft.fillRect(x, y, w, h, color);
    if (!selected) {
        tft.drawFastHLine(x, y + h - 1, w, UI_BUTTON_COLOR);
    }
    
    display_print(label, x + 10, y + (h - 16) / 2, 2, textColor);
}

void ui_draw_output_box(int x, int y, int w, int h, const String& text) {
    tft.fillRect(x, y, w, h, 0x0841); // Console background
    tft.drawRect(x, y, w, h, UI_ACCENT_COLOR);
    tft.setTextColor(UI_TEXT_COLOR);
    tft.setTextSize(1);
    tft.setCursor(x + 5, y + 5);
    
    // Simple line-by-line print for the console view
    tft.print(text);
}
