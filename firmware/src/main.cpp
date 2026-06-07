#include <Arduino.h>
#include "display.h"
#include "touch.h"
#include "ui.h"
#include "menu.h"
#include "wifi.h"

void setup() {
    Serial.begin(115200);
    
    display_init();
    touch_init();
    ui_init();
    wifi_init();
    menu_init();
    
    Serial.println("Cyberdeck Validation Complete. System Ready.");
}

void loop() {
    wifi_update();
    menu_update();
    delay(5);
}
