//This example function displays the time using RTC

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
#include <ESP32Time.h>    //ESP32Time library installation required

ESP32Time esp32_rtc;
char t_buf[100];          //Store RTC information

TFT_eSPI my_lcd = TFT_eSPI(); 
 
void setup() 
{
    Serial.begin(115200);
    my_lcd.begin();
    my_lcd.setRotation(1);
    my_lcd.fillScreen(TFT_WHITE);
    my_lcd.setFreeFont(&FreeSansBold24pt7b);
    my_lcd.setTextColor(TFT_RED);
    my_lcd.drawString("ESP32 RTC TEST", 30, 30);
    my_lcd.setTextFont(4);
    esp32_rtc.setTime(28, 15, 16, 5, 7, 2024);  //Set initial time: 2024-07-05, 16:15:28
}

void loop() 
{
    sprintf(t_buf, "Time : %02d:%02d:%02d", esp32_rtc.getHour(true), esp32_rtc.getMinute(), esp32_rtc.getSecond());   
    my_lcd.fillRect(112, 130, my_lcd.width()/2, 32,TFT_WHITE);   
    my_lcd.drawString(t_buf, 30, 130); 
    sprintf(t_buf, "Date : %04d-%02d-%02d", esp32_rtc.getYear(), esp32_rtc.getMonth() + 1, esp32_rtc.getDay());
    my_lcd.fillRect(112, 170, my_lcd.width()/2, 32,TFT_WHITE); 
    my_lcd.drawString(t_buf, 30, 170); 
    sprintf(t_buf, "Week : %d", esp32_rtc.getDayofWeek());
    my_lcd.fillRect(120, 210, my_lcd.width()/2, 32,TFT_WHITE); 
    my_lcd.drawString(t_buf, 30, 210); 
    delay(1000);
}
