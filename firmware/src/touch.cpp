#include "touch.h"
#include "display.h"
#include "../include/config.h"
#include <Arduino.h>

void touch_init() {
    uint16_t calData[5] = TOUCH_CAL_DATA;
    tft.setTouch(calData);
}

bool touch_read(uint16_t *x, uint16_t *y) {
    static unsigned long last_touch_time = 0;
    static bool was_touched = false;
    
    uint16_t tx, ty;
    bool is_touched = tft.getTouch(&tx, &ty, 600);
    
    if (is_touched) {
        if (!was_touched && (millis() - last_touch_time > 300)) {
            was_touched = true;
            last_touch_time = millis();
            *x = tx;
            *y = ty;
            return true;
        }
    } else {
        was_touched = false;
    }
    
    return false;
}
