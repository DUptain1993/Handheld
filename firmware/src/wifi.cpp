#include "wifi.h"
#include <WiFi.h>
#include "../include/config.h"

static unsigned long last_wifi_check = 0;

void wifi_init() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

bool wifi_is_connected() {
    return WiFi.status() == WL_CONNECTED;
}

void wifi_update() {
    if (millis() - last_wifi_check > 5000) {
        last_wifi_check = millis();
        if (WiFi.status() != WL_CONNECTED) {
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        }
    }
}
