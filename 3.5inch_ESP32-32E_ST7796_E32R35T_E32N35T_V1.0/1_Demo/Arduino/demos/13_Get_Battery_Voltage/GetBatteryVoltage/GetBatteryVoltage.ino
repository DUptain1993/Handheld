//This program is used to display the battery level

//pin usage as follow:
//                   CS  DC/RS  RESET    SDI/MOSI  SCK   SDO/MISO  BL   BAT_VOLT_ADC   VCC    GND    
//ESP32-WROOM-32E:   15    2   ESP32-EN     13      14      12     27        34        5V     GND  

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


#include "Arduino.h"
#include "TFT_eSPI.h" /* Please use the TFT library provided in the library. */
#include <esp_adc_cal.h>

#define PIN_BAT_VOLT    34

TFT_eSPI tft = TFT_eSPI();
unsigned long targetTime = 0;

unsigned int bv = 0;

void setup()
{
    Serial.begin(115200);
    tft.begin();
    tft.setRotation(0);
    tft.setTextSize(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawRoundRect(tft.width()/2-51, tft.height()/2, 102, 22, 3, TFT_WHITE);
    tft.fillRect(tft.width()/2+51, tft.height()/2+6, 5, 10, TFT_WHITE);
}

void loop()
{
    if (millis() > targetTime) 
    {
        esp_adc_cal_characteristics_t adc_chars;
        // Get the internal calibration value of the chip
        esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
        uint32_t raw = analogRead(PIN_BAT_VOLT);
        uint32_t v1 = esp_adc_cal_raw_to_voltage(raw, &adc_chars) * 2; //The partial pressure is one-half

        tft.setCursor(tft.width()/2-50, tft.height()/4);

        tft.print(v1);
        tft.print("mV");

        if(v1<=2500)
        {
          bv = 0;  
        }
        else if((v1>2500)&&(v1<=4200))
        {
          bv = (v1 - 2500)/17;  
        }
        else
        {
          bv = 100;  
        }
        tft.fillRoundRect(tft.width()/2-50, tft.height()/2+1,100, 20, 3, TFT_BLACK);
        tft.fillRoundRect(tft.width()/2-50, tft.height()/2+1, bv, 20, 3, TFT_GREEN);
        targetTime = millis() + 1000;
    }
    delay(20);
}
