//The function of this program is to control LED lights with buttons

//pin usage as follow:
//                     RED   GREEN   BLUE   KEY   VCC    GND    
//ESP32-WROOM-32E:      22     16     17     0    5V     GND  

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

#define RED_PIN 22
#define GREEN_PIN 16
#define BLUE_PIN 17

#define LED_ON  0
#define LED_OFF 1

#define KEY_PIN  0

int key_num = 0;

void setup()
{
  //Initialize LED GPIO, turn off tricolor light
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(RED_PIN, LED_OFF);  //RED
  digitalWrite(GREEN_PIN, LED_OFF); //GREEN
  digitalWrite(BLUE_PIN, LED_OFF); //GREEN
  //Initialize KEY GPIO
  pinMode(KEY_PIN,INPUT_PULLUP);
}

void loop()
{ 
  if(!digitalRead(KEY_PIN))
  {
    delay(10);
    if(!digitalRead(KEY_PIN))
   {
      while(!digitalRead(KEY_PIN));
      ++key_num;
      switch(key_num)
      {
        case 1:
          digitalWrite(RED_PIN, LED_ON);
          break;
        case 2:
          digitalWrite(GREEN_PIN, LED_ON);
          break;
        case 3:
          digitalWrite(BLUE_PIN, LED_ON);
          break;
        case 4:
          key_num = 0;
          digitalWrite(RED_PIN, LED_OFF);  
          digitalWrite(GREEN_PIN, LED_OFF); 
          digitalWrite(BLUE_PIN, LED_OFF); 
          break;
        default:
          break;
      }
    }
  }
}
