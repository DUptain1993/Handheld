//This program is used to operate RGB tricolor lights

//pin usage as follow:
//                   RED  GREEN  BLUE   VCC    GND    
//ESP32-WROOM-32E:   22    16     17    5V     GND  

//Low level  -- turn on LED light
//High level -- turn off LED light

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

#include <Arduino.h>

#define RED_PIN 22
#define GREEN_PIN 16
#define BLUE_PIN 17

#define LED_ON  0
#define LED_OFF 1

int freq = 2000;    // frequency
int channel = 0;    // aisle
int resolution = 8;   // Resolution

const int led = RED_PIN;
void setup()
{
  //Initialize GPIO, turn off tricolor light

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(RED_PIN, LED_OFF);  //RED
  digitalWrite(GREEN_PIN, LED_OFF); //GREEN
  digitalWrite(BLUE_PIN, LED_OFF); //GREEN
  delay(1000);
  digitalWrite(RED_PIN, LED_ON);  //RED
  digitalWrite(GREEN_PIN, LED_ON); //GREEN
  digitalWrite(BLUE_PIN, LED_ON); //GREEN
  delay(2000);
  ledcSetup(channel, freq, resolution); // set channel
  //ledcAttachPin(led, channel);  // Connect the channel to the corresponding pin
}

void loop()
{
  int i = 0;
  digitalWrite(GREEN_PIN, LED_OFF); 
  digitalWrite(BLUE_PIN, LED_OFF);
  digitalWrite(RED_PIN, LED_ON);
  delay(1500);
  for(i=0;i<6;i++)
  {
     digitalWrite(RED_PIN, LED_OFF);
     delay(500);
     digitalWrite(RED_PIN, LED_ON);
     delay(500);  
  }
  digitalWrite(RED_PIN, LED_OFF); 
  digitalWrite(BLUE_PIN, LED_OFF);
  digitalWrite(GREEN_PIN, LED_ON);
  delay(1500);
  for(i=0;i<6;i++)
  {
     digitalWrite(GREEN_PIN, LED_OFF);
     delay(500);
     digitalWrite(GREEN_PIN, LED_ON);
     delay(500);  
  }
  digitalWrite(RED_PIN, LED_OFF); 
  digitalWrite(GREEN_PIN, LED_OFF);
  digitalWrite(BLUE_PIN, LED_ON);
  delay(1500);
  for(i=0;i<6;i++)
  {
     digitalWrite(BLUE_PIN, LED_OFF);
     delay(500);
     digitalWrite(BLUE_PIN, LED_ON);
     delay(500);  
  }
  digitalWrite(RED_PIN, LED_OFF);  //RED
  digitalWrite(GREEN_PIN, LED_OFF); //GREEN
  digitalWrite(BLUE_PIN, LED_OFF); //GREEN
  ledcAttachPin(led, channel);
  // gradually brighten
   for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle = dutyCycle - 5)
  {
    ledcWrite(channel, dutyCycle);  // output PWM
    delay(100);
  }
  // gradually darken
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle = dutyCycle + 5)
  {
    ledcWrite(channel, dutyCycle);  // output PWM
    delay(100);
  }
  delay(500);
  ledcDetachPin(RED_PIN);
}
