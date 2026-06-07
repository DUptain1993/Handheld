//How does this program connect to WiFi

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

//Manually modifying parameters
const char *ssid = "yourssid";
const char *password = "yourpwd";

char t_buf[100] = {0};

int i = 0;

TFT_eSPI my_lcd = TFT_eSPI(); 

void setup()
{
  Serial.begin(115200);
  my_lcd.begin();
  my_lcd.setRotation(0);
  my_lcd.fillScreen(TFT_WHITE);
  my_lcd.setTextColor(TFT_RED);
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  my_lcd.drawString("Start connecting to WiFi...", 52,105,2);
  WiFi.begin(ssid, password);
  while(WiFi.status()!= WL_CONNECTED)
  {
      i++;
      delay(500);
      Serial.print(".");
      if(i>360)
      {
        break;  
      }
  }
  if(i>360)
  {
    while(1)
    {
      my_lcd.fillRect(52, 105, my_lcd.width()-1, 25,TFT_WHITE);
      delay(500); 
      my_lcd.drawString("connection failed!!!", 52,105,2);
      delay(500); 
    } 
  }
  else
  {
     my_lcd.fillRect(52, 105, my_lcd.width()-1, 25,TFT_WHITE);
     my_lcd.setTextColor(TFT_GREEN);
     my_lcd.drawString("Connection successful!!!", 52,105,2);
     my_lcd.setTextColor(TFT_BLUE);
     sprintf(t_buf, "SSID : %s", ssid);
     my_lcd.drawString(t_buf, 52,125,2);
     sprintf(t_buf, "  IP : %s", WiFi.localIP().toString().c_str());
     my_lcd.drawString(t_buf, 52,145,2);
     sprintf(t_buf, " MAC : %s", WiFi.macAddress().c_str());
     my_lcd.drawString(t_buf, 52,165,2);
  }
}
void loop()
{
  delay(1000);
}
