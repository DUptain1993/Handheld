#ifndef HTTP_H
#define HTTP_H

#include <Arduino.h>

void http_send_command(const char* endpoint, const char* params, String& response);

#endif
