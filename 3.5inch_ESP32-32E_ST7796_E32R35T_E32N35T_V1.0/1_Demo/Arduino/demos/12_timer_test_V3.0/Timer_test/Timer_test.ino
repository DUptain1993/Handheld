//How to use a timer to control LED lights in this program

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

hw_timer_t * timer = NULL;
 
volatile byte state = LED_OFF;
 
void IRAM_ATTR onTimer(){
  state = !state;
  digitalWrite(GREEN_PIN, state);
}
 
void setup() {
  Serial.begin(115200);
   //Initialize GPIO, turn off blue and green lights

  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(RED_PIN, LED_OFF);
  digitalWrite(BLUE_PIN, LED_OFF);
  //Initialize red light
  pinMode(GREEN_PIN, OUTPUT);
 
  
  /*  1/(80MHZ/80) = 1us  */
  timer = timerBegin(1000000);
 
  /* Attach the onTimer function to our timer */
  timerAttachInterrupt(timer, &onTimer);
 
  /* *Set the alarm clock to call the onTimer function every second 1 tick is 1us => 1 second is 1000000us * / 
  / *Repeat alarm (third parameter)*/
 
  timerAlarm(timer, 1000000, true, 0);
 
  Serial.println("start timer");
}
 
void loop()
{
    delay(10);
}
