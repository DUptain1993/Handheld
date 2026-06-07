//How does this program search for WiFi

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
#include "WiFi.h"

char wifi_name[40];   //wifi name
char wifi_rssi[6];    //WiFi signal strength 
char wifi_enc[10];    // WiFi security type

TFT_eSPI my_lcd = TFT_eSPI(); 

void setup() 
{
    my_lcd.begin();
    my_lcd.setRotation(1);
    WiFi.mode(WIFI_STA);    //The mode selection for WIFI is STA mode
    WiFi.disconnect();      //Disconnect any previous WIFI connections
    delay(100);
}

void loop() 
{
    my_lcd.fillScreen(TFT_WHITE);
    my_lcd.setTextColor(TFT_RED);
    my_lcd.setFreeFont(&FreeSans18pt7b);
    my_lcd.drawString("WIFI Scan Start", 105, 148);
    int network_cnt = WiFi.scanNetworks();  //Start scanning available networks
    my_lcd.setTextColor(TFT_BLUE);
    my_lcd.fillRect(0, 145, my_lcd.width()-1, 40,TFT_WHITE);
    my_lcd.drawString("WIFI Scan Done!", 105, 148);    
    delay(500);
    my_lcd.fillScreen(TFT_WHITE);
    my_lcd.setTextColor(TFT_RED);
    my_lcd.setTextFont(2);
    if (network_cnt == 0) 
    { 
        my_lcd.drawString("no wifi networks found!", 10, 0); 
    }
    else 
    {
        my_lcd.drawNumber(network_cnt, 10, 0);
        my_lcd.drawString("networks found", 30, 0); 
        my_lcd.setTextColor(TFT_BLUE);
        my_lcd.drawString(" Nr |                   SSID                    | RSSI  |  CH | ENC_TYPE", 10, 20);
      
        int wifi_info_show = (network_cnt > 17 ? 17 : network_cnt);       //Display up to 17 WiFi messages
        for (int i = 0; i < wifi_info_show; ++i)   
        {
            my_lcd.drawNumber(i + 1, 18, 40 + i * 16);                //Display WiFi index values

            sprintf(wifi_name, "%-30s", WiFi.SSID(i).c_str());        //Get the name of the network (also known as SSID)
             my_lcd.drawString(wifi_name, 50, 40 + i * 16); 
                
            sprintf(wifi_rssi, "%4ddB", WiFi.RSSI(i));                //Obtain the signal strength of the network in dBm
            my_lcd.drawString(wifi_rssi, 298, 40 + i * 16);

            my_lcd.drawNumber(WiFi.channel(i), 362, 40 + i * 16);    //Obtain channel number

            switch (WiFi.encryptionType(i))                                // WiFi security type
            {
                case WIFI_AUTH_OPEN:
                    sprintf(wifi_enc, "%s", "OPEN");             
                    break;
                case WIFI_AUTH_WEP:
                    sprintf(wifi_enc, "%s", "WEP");             
                    break;
                case WIFI_AUTH_WPA_PSK:   
                    sprintf(wifi_enc, "%s", "WPA");    
                    break;
                case WIFI_AUTH_WPA2_PSK:
                    sprintf(wifi_enc, "%s", "WPA2");
                    break;
                case WIFI_AUTH_WPA_WPA2_PSK:
                    sprintf(wifi_enc, "%s", "WPA+WPA2");
                    break;
                case WIFI_AUTH_WPA2_ENTERPRISE:
                    sprintf(wifi_enc, "%s", "WPA2-EAP");
                    break;
                case WIFI_AUTH_WPA3_PSK:
                    sprintf(wifi_enc, "%s", "WPA3");
                    break;
                case WIFI_AUTH_WPA2_WPA3_PSK:
                    sprintf(wifi_enc, "%s", "WPA2+WPA3");
                    break;
                case WIFI_AUTH_WAPI_PSK:
                    sprintf(wifi_enc, "%s", "WAPI");
                    break;
                default:
                    sprintf(wifi_enc, "%s", "unknown");
            }
            my_lcd.drawString(wifi_enc, 398, 40 + i * 16);
            delay(10);
        }
    }
    WiFi.scanDelete();
    delay(5000);
    my_lcd.fillScreen(TFT_WHITE);
}
