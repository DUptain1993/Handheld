//The function of this program is to use PWM to control the backlight brightness of the LCD screen

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

#define BACKLIGHT_PIN 27

// PWM related parameter settings
int freq = 2000;
int channel = 0;
int resolution = 8;

TFT_eSPI my_lcd = TFT_eSPI(); 

void setup()
{
  Serial.begin(115200);
  my_lcd.begin();
  my_lcd.setRotation(1);
  uint16_t calData[5] = { 245, 3664, 259, 3471, 7 };
  my_lcd.setTouch(calData);
  my_lcd.fillScreen(TFT_WHITE);
  my_lcd.setTextColor(TFT_BLACK, TFT_WHITE);
  my_lcd.setTextSize(2);
  my_lcd.setCursor(my_lcd.width()/2-170, 183);
  my_lcd.println("0");
  my_lcd.setCursor(my_lcd.width()/2+150, 183);
  my_lcd.println("255");
  my_lcd.fillRoundRect(my_lcd.width()/2-138, 180, 276, 21,10,0x8430);
  my_lcd.fillCircle(my_lcd.width()/2+128, 190,10,TFT_MAGENTA);
  my_lcd.setTextColor(TFT_RED);
  my_lcd.drawNumber(255, my_lcd.width()/2-15, 115,2);
  ledcAttachChannel(BACKLIGHT_PIN, freq, resolution, channel);
  ledcWrite(BACKLIGHT_PIN, 255);
}
 
void loop()
{
  uint16_t t_x = 0, t_y = 0; // To store the touch coordinates
  if(my_lcd.getTouch(&t_x, &t_y))
  {
    if((t_x>=my_lcd.width()/2-128)&&(t_x<my_lcd.width()/2+128)&&t_y > 179&&t_y < 199)
    {
      my_lcd.setTextColor(TFT_RED, TFT_WHITE);
      my_lcd.fillRoundRect(t_x-10, 180, my_lcd.width()/2+138-t_x+10, 21,10,0x8430);
      my_lcd.fillRoundRect(my_lcd.width()/2-138, 180, t_x-my_lcd.width()/2+148, 21,10,0x07FF);
      my_lcd.fillCircle(t_x, 190,10,TFT_MAGENTA);
      my_lcd.setTextPadding(50);
      my_lcd.drawNumber((long)t_x-(my_lcd.width()/2-128), my_lcd.width()/2-15, 115,2);
      ledcWrite(BACKLIGHT_PIN, t_x-(my_lcd.width()/2-128));
    }
  }
}
