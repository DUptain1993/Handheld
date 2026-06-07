#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>

extern TFT_eSPI tft;

void display_init();
void display_clear();
void display_print(const char* text, int x, int y, int size, uint16_t color);

#endif
