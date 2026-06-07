//This example is to build a UDP conntion

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
#include <AsyncUDP.h>


//Manually modifying parameters
const char *ssid = "yourssid";
const char *password = "yourpwd";

char t_buf[100] = {0};

AsyncUDP udp;                      //Creating UDP Objects
unsigned int localUdpPort = 10000; //Local port number

unsigned int broadcastPort = localUdpPort;
const char *broadcastData = "broadcast UDP data";

TFT_eSPI my_lcd = TFT_eSPI(); 

void onPacketCallBack(AsyncUDPPacket packet)
{
  my_lcd.fillRect(10, 185, my_lcd.width()-1, 150,TFT_WHITE);
  sprintf(t_buf, "REMOTE IP : %s", packet.remoteIP().toString().c_str());
  my_lcd.drawString(t_buf, 10,185,2);
  sprintf(t_buf, "REMOTE PORT : %d", packet.remotePort());
  my_lcd.drawString(t_buf, 10,205,2);
  sprintf(t_buf, "LOCAL IP : %s", packet.localIP().toString().c_str());
  my_lcd.drawString(t_buf, 10,225,2);
  sprintf(t_buf, "LOCAL PORT : %d", packet.localPort());
  my_lcd.drawString(t_buf, 10,245,2);
  sprintf(t_buf, "DATA LEN : %d", packet.length());
  my_lcd.drawString(t_buf, 10,265,2);
  sprintf(t_buf, "DATA : %s", packet.data());
  my_lcd.drawString(t_buf, 10,285,2);
  packet.print("reply data");
  broadcastPort = packet.remotePort();
}

void setup()
{
  Serial.begin(115200);
  my_lcd.begin();
  my_lcd.setRotation(0);
  my_lcd.fillScreen(TFT_WHITE);
  my_lcd.setTextColor(TFT_RED);
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  my_lcd.drawString("Start connecting to WiFi ...", 10,55,2);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  my_lcd.fillRect(10, 55, my_lcd.width()-1, 25,TFT_WHITE);
  my_lcd.setTextColor(TFT_GREEN);
  my_lcd.drawString("Connection WIFI successful!!!", 10,55,2);
  my_lcd.setTextColor(TFT_BLUE);
  sprintf(t_buf, "SSID : %s", ssid);
  my_lcd.drawString(t_buf, 10,75,2);
  sprintf(t_buf, "  IP : %s", WiFi.localIP().toString().c_str());
  my_lcd.drawString(t_buf, 10,95,2);
  sprintf(t_buf, " MAC : %s", WiFi.macAddress().c_str());
  my_lcd.drawString(t_buf, 10,115,2);
  sprintf(t_buf, "LOCAL PORT : %d", localUdpPort);
  my_lcd.drawString(t_buf, 10,135,2);
  my_lcd.setTextColor(TFT_RED);
  my_lcd.drawString("Waiting for UDP listening ...", 10,155,2);

  while (!udp.listen(localUdpPort)) //Waiting for UDP listening settings to succeed
  {
  }
  my_lcd.fillRect(10, 155, my_lcd.width()-1, 25,TFT_WHITE);
  my_lcd.drawString("UDP listening settings successful !", 10,155,2);
  udp.onPacket(onPacketCallBack); //Registration received packet event
}

void loop()
{
  delay(5000);
  udp.broadcastTo(broadcastData, broadcastPort); //This method can be used to broadcast information
}
