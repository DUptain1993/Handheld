//The function of this program is to control LED lights using interrupt buttons

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

bool interrupt_flag = false;

int numberOfInterrupts = 0;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Monitoring interrupts: ");
  //Initialize LED GPIO, turn off tricolor light
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(RED_PIN, LED_OFF);  //RED
  digitalWrite(GREEN_PIN, LED_OFF); //GREEN
  digitalWrite(BLUE_PIN, LED_OFF); //GREEN
  //Initialize KEY GPIO
  pinMode(KEY_PIN,INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(KEY_PIN), handleInterrupt, FALLING);
}

void handleInterrupt() 
{
  delay(50);
  if(!digitalRead(KEY_PIN))
  {
    portENTER_CRITICAL_ISR(&mux);
    interrupt_flag = true;
    portEXIT_CRITICAL_ISR(&mux);
  }
  //detachInterrupt(KEY_PIN);
}

void loop()
{
  if(interrupt_flag)
  {
      portENTER_CRITICAL(&mux);
      interrupt_flag = false;
      portEXIT_CRITICAL(&mux);
      Serial.print("An interrupt has occurred. Total: ");
      switch(numberOfInterrupts%4)
      {
        case 0:
          digitalWrite(RED_PIN, LED_ON);
          break;
        case 1:
          digitalWrite(GREEN_PIN, LED_ON);
          break;
        case 2:
          digitalWrite(BLUE_PIN, LED_ON);
          break;
        case 3:
          digitalWrite(RED_PIN, LED_OFF);  
          digitalWrite(GREEN_PIN, LED_OFF); 
          digitalWrite(BLUE_PIN, LED_OFF); 
          break;
        default:
          break;
      }
      numberOfInterrupts++;
      Serial.println(numberOfInterrupts);
  }
}
