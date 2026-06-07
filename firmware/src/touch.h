#ifndef TOUCH_H
#define TOUCH_H

#include <stdint.h>

void touch_init();
bool touch_read(uint16_t *x, uint16_t *y);

#endif
