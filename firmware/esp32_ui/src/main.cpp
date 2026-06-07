#include <Arduino.h>
#include "display.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Cyberdeck ESP32-32E UI Initializing...");
    
    display_init();
    display_test();
    
    Serial.println("Phase 1: Display Test Complete.");
}

void loop() {
    // Phase 1: Minimal logic
    delay(1000);
}
