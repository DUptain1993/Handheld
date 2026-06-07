//This example is to build a TCP client-side

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

const IPAddress serverIP(192,168,4,52); //The server address to be accessed (based on actual settings)
uint16_t serverPort = 8080;         //Server port number

char t_buf[100] = {0};

WiFiClient client;  //Declare a client object

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
    sprintf(t_buf, "SERVER PORT : %d", serverPort);
    my_lcd.drawString(t_buf, 10,135,2);
    my_lcd.setTextColor(TFT_RED);
    my_lcd.drawString("Attempting to access server ...", 10,155,2);
}

void loop()
{
    if (client.connect(serverIP, serverPort)) //Attempting to access server
    {
        my_lcd.fillRect(10, 155, my_lcd.width()-1, 25,TFT_WHITE);
        my_lcd.drawString("Access successful !", 10,155,2);
        client.print("Hello, this is client!");          //Send data to the server
        while (client.connected() || client.available()) //If connected or received unread data
        {
            if (client.available())  //If there is data that can be read
            {
                String line = client.readStringUntil('\n'); //Read data to line breaks
                my_lcd.fillRect(10, 175, my_lcd.width()-1, 25,TFT_WHITE);
                my_lcd.drawString("Received: " + line, 10,185,2);
                client.write(line.c_str()); //Send back the received data
            }
        }
        my_lcd.fillRect(10, 155, my_lcd.width()-1, 25,TFT_WHITE);
        my_lcd.drawString("Close current connection.", 10,155,2);
        client.stop(); //Close client
    }
    else
    {
        my_lcd.fillRect(10, 155, my_lcd.width()-1, 25,TFT_WHITE);
        my_lcd.drawString("Access failed, Close client !", 10,155,2);
        client.stop(); //Close client
    }
    delay(5000);
}
