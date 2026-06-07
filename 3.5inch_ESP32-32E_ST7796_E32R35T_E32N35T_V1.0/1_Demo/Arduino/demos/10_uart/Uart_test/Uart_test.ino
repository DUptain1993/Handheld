//This program is a demo of how to use uart to send and receive messages

//pin usage as follow:
//                   CS  DC/RS  RESET    SDI/MOSI  SCK   SDO/MISO  BL    VCC    GND    
//ESP32-WROOM-32E:   15    2   ESP32-EN     13      14      12     27    5V     GND  

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


String r_data;

TFT_eSPI my_lcd = TFT_eSPI(); 

void setup() 
{
  Serial.begin(115200); //Set the serial port baud rate 115200
  my_lcd.begin();
  my_lcd.setRotation(0);
  my_lcd.fillScreen(TFT_BLACK);
  my_lcd.setTextColor(TFT_GREEN);
  my_lcd.drawString("This is uart test!!",0,10,2);
  my_lcd.drawString("receive data :",0,25,2);
  my_lcd.setTextColor(TFT_WHITE);
  Serial.println(55, BIN); //Binary
  Serial.println(55, OCT); //octonary
  Serial.println(55, DEC); //decimalism
  Serial.println(55, HEX); //hexadecimal
  Serial.println(9.19999, 0); //Keep 0 decimal places
  Serial.println(9.11999, 1); //Keep 1 decimal places
  Serial.println(9.11119, 4); //Keep 4 decimal places
  Serial.println('Q');
  Serial.println("Hello! this send.");
  Serial.print("x =");
  Serial.print(20);
  Serial.print(",y =");
  Serial.print(40);
  Serial.print('\n');
}
void loop() 
{
  int i = 0,j=0;
  String temp;
  if(Serial.available() > 0)//Serial port receives data
  {
      r_data = Serial.readString();//Obtain the data received by the serial port
      Serial.println(r_data);
      //Serial.println(r_data.length());
      my_lcd.fillRect(0, 40, my_lcd.width(), my_lcd.height()-40,TFT_BLACK);
      if((r_data.length()-1)<39)
      {
        my_lcd.drawString(r_data,5,40,2);   
      }
      else
      {
        for(i=0; i<=((r_data.length()-1)/38); i++)
        {
          j = r_data.length()-i*38;
          if(j<38)
          {
              temp = r_data.substring(38*i);
          }
          else
          {
            temp = r_data.substring(38*i,38*i+38);
          }
          my_lcd.drawString(temp,5,40+15*i,2);
        }
      }
  }
  delay(1000);
}
