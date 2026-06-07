//How does this program connect to WiFi AP mode.

//pin usage as follow:
//                   CS  DC/RS  RESET    SDI/MOSI  SCK   SDO/MISO  BL      VCC    GND    
//ESP32-WROOM-32E:   15    2   ESP32-EN     13      14      12     27      5V     GND  

/***********************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE 
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**********************************************************************************/
#include <TFT_eSPI.h> 
#include <WiFi.h>

//AP mode SSID and PWD
const char *ssid = "ESP32_AP";
const char *password = "0123456789";

char t_buf[100] = {0};
TFT_eSPI my_lcd = TFT_eSPI(); 

void setup()
{
  Serial.begin(115200);
  my_lcd.begin();
  my_lcd.setRotation(0);
  my_lcd.fillScreen(TFT_WHITE);
  my_lcd.setTextColor(TFT_RED);
  my_lcd.drawString("Enable ESP32 WIFI AP mode...", 52,105,2);
  WiFi.softAP(ssid, password);
  my_lcd.setTextColor(TFT_BLUE);
  sprintf(t_buf, "SSID : %s", ssid);
  my_lcd.drawString(t_buf, 52,125,2);
  sprintf(t_buf, "PASSWORD : %s", password);
  my_lcd.drawString(t_buf, 52,145,2);
  sprintf(t_buf, "HOST IP : %s", WiFi.softAPIP().toString().c_str());
  my_lcd.drawString(t_buf, 52,165,2);
  sprintf(t_buf, "HOST MAC : %s", WiFi.softAPmacAddress().c_str());
  my_lcd.drawString(t_buf, 52,185,2);
  my_lcd.drawString("CONNECTED NUMBER : ", 52,215,2);
}

void loop()
{
  sprintf(t_buf, "%d", WiFi.softAPgetStationNum());
  my_lcd.fillRect(204, 215, my_lcd.width()-80, 25,TFT_WHITE);
  my_lcd.drawString(t_buf, 204,215,2);
  delay(1000);
}
