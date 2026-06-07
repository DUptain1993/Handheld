#ifndef UI_H
#define UI_H

#include <Arduino.h>

void ui_init();
void ui_draw_header(const char* title);
void ui_draw_button(int x, int y, int w, int h, const char* label, bool highlighted);
void ui_draw_list_item(int x, int y, int w, int h, const char* label, bool selected);
void ui_draw_output_box(int x, int y, int w, int h, const String& text);

#endif
