//This example is to build a TCP server-side

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
int port = 10000;

WiFiServer server(port); //Declare server objects

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
    my_lcd.drawString("Start connecting to WiFi ...", 10,55,2);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
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
    sprintf(t_buf, " PORT : %d", port);
    my_lcd.drawString(t_buf, 10,135,2);
    my_lcd.setTextColor(TFT_RED);
    server.begin(); //Start server 
    my_lcd.drawString("Waiting for client connection", 10,155,2);
}

void loop()
{
    WiFiClient client = server.available(); //Attempting to establish a customer object
    if(client) //If the current customer is available
    {
        my_lcd.fillRect(10, 155, my_lcd.width()-1, 25,TFT_WHITE);
        my_lcd.drawString("Client connected.", 10,155,2);
        String readBuff = "";          // make a String to hold incoming data from the client
        while (client.connected())     //loop while the client's connected
        {
            if (client.available())    // if there's bytes to read from the client
            {
                char c = client.read(); // read a byte
                Serial.write(c);
                readBuff += c;
               if(c == '\r') //Send in hexadecimal 0x0D
                {
                    client.print("Received: " + readBuff); //Send to client
                    my_lcd.fillRect(10, 175, my_lcd.width()-1, 25,TFT_WHITE);
                     my_lcd.drawString("Received: " + readBuff, 10,175,2);
                    readBuff = "";
                }
            }
        }
        client.stop(); //结束当前连接:
        my_lcd.fillRect(10, 155, my_lcd.width()-1, 25,TFT_WHITE);
        my_lcd.drawString("Client Disconnected.", 10,155,2);
    }
}
