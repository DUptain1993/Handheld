//How does this program connect to WiFi AP mode.

//pin usage as follow:
//                   CS  DC/RS  RESET    SDI/MOSI  SCK   SDO/MISO  BL      VCC    GND    
//ESP32-WROOM-32E:   15    2   ESP32-EN     13      14      12     27      5V     GND  

//ESPTOUCH APP URL:https://www.espressif.com.cn/en/support/download/apps

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
#include <Preferences.h>
#include <TFT_eSPI.h> 
#include <WiFi.h>

#define KEY_PIN  0

char ssid[50] = {0};
char password[50] = {0};
bool wflag = false;
unsigned long prv_millis = 0;

char t_buf[100] = {0};
TFT_eSPI my_lcd = TFT_eSPI(); 

Preferences my_prefs;

void ESP32_SmartWifiConfig()
{
  WiFi.mode(WIFI_AP_STA);
  my_lcd.drawString("Start WiFi smartconfig", 10,140,2);
  WiFi.beginSmartConfig();
  while (!WiFi.smartConfigDone())
  {
    delay(500);
    Serial.print(".");
  }
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  my_prefs.putBool("wifi_flag", true);
  my_prefs.putString("wifi_ssid", WiFi.SSID().c_str());
  my_prefs.putString("wifi_pswd", WiFi.psk().c_str());
  my_lcd.drawString("WiFi smartconfig successful", 10,160,2);
  sprintf(t_buf, "SSID : %s", WiFi.SSID().c_str());
  my_lcd.drawString(t_buf, 10,180,2);
  sprintf(t_buf, "PASSWORD : %s", WiFi.psk().c_str());
  my_lcd.drawString(t_buf, 10,200,2);
  sprintf(t_buf, "  IP : %s", WiFi.localIP().toString().c_str());
  my_lcd.drawString(t_buf, 10,220,2);
  sprintf(t_buf, " MAC : %s", WiFi.macAddress().c_str());
  my_lcd.drawString(t_buf, 10,240,2);
}

bool ESP32_autoConfig()
{
  my_lcd.drawString("Start automatically connecting to WiFi", 10,100,2);
  //WiFi.disconnect(true,true);
  my_prefs.getString("wifi_ssid", ssid, sizeof(ssid));
  my_prefs.getString("wifi_pswd", password, sizeof(password));
  WiFi.begin(ssid, password);
  for (size_t i = 0; i < 20; i++)
  {
    if(WiFi.status() == WL_CONNECTED)
    {
      my_lcd.fillRect(10, 120, my_lcd.width()-1, 20,TFT_WHITE);
      my_lcd.drawString("Successfully connected to WiFi automatically", 10,120,2);
      sprintf(t_buf, "SSID : %s", WiFi.SSID().c_str());
      my_lcd.drawString(t_buf, 10,140,2);
      sprintf(t_buf, "PASSWORD : %s", WiFi.psk().c_str());
      my_lcd.drawString(t_buf, 10,160,2);
      sprintf(t_buf, "  IP : %s", WiFi.localIP().toString().c_str());
      my_lcd.drawString(t_buf, 10,180,2);
      sprintf(t_buf, " MAC : %s", WiFi.macAddress().c_str());
      my_lcd.drawString(t_buf, 10,200,2);
      return 1;
    }
    else
    {
      delay(1000);
      my_lcd.fillRect(10, 120, my_lcd.width()-1, 20,TFT_WHITE);
      my_lcd.drawString("Waiting for automatic wifi connection", 10,120,2);
    }
  }
  my_lcd.fillRect(10, 120, my_lcd.width()-1, 20,TFT_WHITE);
  my_lcd.drawString("Automatic connection to WiFi failed", 10,120,2);
  return 0;
}

void setup()
{
  Serial.begin(115200);
  pinMode(KEY_PIN,INPUT_PULLUP);
  my_prefs.begin("wificonfig");
  my_lcd.begin();
  my_lcd.setRotation(0);
  my_lcd.fillScreen(TFT_WHITE);
  my_lcd.setTextColor(TFT_RED);
  wflag = my_prefs.getBool("wifi_flag", false);
  delay(3000);
  if(wflag)
  {
    if(!ESP32_autoConfig())
    {
      ESP32_SmartWifiConfig();
    }
  }
  else
  {
    ESP32_SmartWifiConfig();
  }
}

void loop()
{
  if(!digitalRead(KEY_PIN))
  {
    delay(10);
    if(!digitalRead(KEY_PIN))
    {
      prv_millis = millis();
      while(!digitalRead(KEY_PIN))
      {
         if((millis() - prv_millis) >= 3000)  //Long press for 3 seconds to clear wifi information and reconfigure the network
         {
            my_prefs.putBool("wifi_flag", false);
            my_prefs.putString("wifi_ssid", "yourssid");
            my_prefs.putString("wifi_pswd", "yourpswd");  
            ESP.restart();  // Restart ESP
         }
      }
    }
  }
  //delay(1000);
}
