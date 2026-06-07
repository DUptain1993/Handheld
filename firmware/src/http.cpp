#include "http.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "../include/config.h"

void http_send_command(const char* endpoint, const char* params, String& response) {
    response = "";
    if (WiFi.status() != WL_CONNECTED) {
        response = "ERROR: WiFi not connected";
        return;
    }

    HTTPClient http;
    char url[256];
    snprintf(url, sizeof(url), "http://%s:%d%s%s%s", 
             BACKEND_HOST, BACKEND_PORT, endpoint, 
             (params && strlen(params) > 0) ? "?" : "",
             (params && strlen(params) > 0) ? params : "");

    http.setTimeout(10000); 
    http.begin(url);
    
    int httpCode = http.GET();

    if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
            response = http.getString();
            if (response.length() > MAX_RESPONSE_SIZE) {
                response = response.substring(0, MAX_RESPONSE_SIZE);
                response += "\n[TRUNCATED]";
            }
        } else {
            response = "ERROR: HTTP " + String(httpCode);
        }
    } else {
        response = "ERROR: Connection failed";
    }

    http.end();
}
