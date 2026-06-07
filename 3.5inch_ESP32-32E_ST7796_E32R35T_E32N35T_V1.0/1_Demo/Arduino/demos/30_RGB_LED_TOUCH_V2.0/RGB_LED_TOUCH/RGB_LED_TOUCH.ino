//This program controls RGB three color lights through touch screen buttons

//pin usage as follow:
//                   CS  DC/RS  RESET    SDI/MOSI  SCK   SDO/MISO  BL  TOUCH_CS  RED  GREEN  BLUE  VCC   GND    
//ESP32-WROOM-32E:   15    2   ESP32-EN     13      14      12     27     33      22    16    17   5V    GND 

/*********************************************************************************
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
#include "TFT_eSPI.h" /* Please use the TFT library provided in the library. */

#define RED_PIN 22
#define GREEN_PIN 16
#define BLUE_PIN 17

#define LED_ON  0
#define LED_OFF 1

int freq = 2000;    // frequency
int channel = 0;    // aisle
int resolution = 8;   // Resolution

const int led = RED_PIN;

uint8_t led_on_flag = 0;

//key numbers
#define NUM_KEYS 3

// Keypad start position, key sizes and spacing
#define KEY_X 110 // Centre of key
#define KEY_Y 80
#define KEY_W 100 // Width and height
#define KEY_H 50
#define KEY_SPACING_X 30 // X and Y gap
#define KEY_SPACING_Y 1
#define KEY_TEXTSIZE 2   // Font size multiplier

uint16_t k_color[NUM_KEYS] = {TFT_RED, TFT_GREEN, TFT_BLUE};

TFT_eSPI tft = TFT_eSPI();

TFT_eSPI_Button key_b[NUM_KEYS];

void light_led(uint8_t led_num, bool statue)
{
  ledcDetachPin(led);  
  switch(led_num)
  {
    case 0:
      digitalWrite(RED_PIN, statue);  
      break;
    case 1:
      digitalWrite(GREEN_PIN, statue);  
      break;
    case 2:
      digitalWrite(BLUE_PIN, statue); 
      break;
    default:
        break;
  } 
}

void led_flick(uint8_t led_num)
{
  uint8_t i =0, pin;
  ledcDetachPin(led);  
  switch(led_num)
  {
   case 0:
      pin = RED_PIN;
      break;
   case 1:
      pin = GREEN_PIN;
      break;
   case 2:
      pin = BLUE_PIN;
      break;
   default:
      break;  
  }
  for(i=0;i<6;i++)
  {
     digitalWrite(pin, LED_OFF);
     delay(500);
     digitalWrite(pin, LED_ON);
     delay(500);  
  }  
}

void setup()
{
  tft.begin();
  tft.setRotation(1);
  uint16_t calData[5] = { 245, 3664, 259, 3471, 7 };
  tft.setTouch(calData);
  tft.fillScreen(TFT_BLACK);
  //Initialize GPIO, turn off tricolor light
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(RED_PIN, LED_OFF);  //RED
  digitalWrite(GREEN_PIN, LED_OFF); //GREEN
  digitalWrite(BLUE_PIN, LED_OFF); //GREEN
  ledcSetup(channel, freq, resolution); // set channel
  tft.setCursor(80, 25);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println("Press the button to turn the RGB light on or off :");
  tft.setTextSize(2);
  tft.setCursor(tft.width()/2-170, 213);
  tft.println("0");
    tft.setCursor(tft.width()/2+150, 213);
  tft.println("255");
  tft.fillRoundRect(tft.width()/2-138, 219, 276, 21,10,0x8430);
  tft.fillCircle(tft.width()/2-128, 229,10,TFT_MAGENTA);

  tft.setTextColor(0xFFE0);
  tft.drawNumber(0, tft.width()/2-15, 155,2);
  tft.setFreeFont(&FreeSansBold9pt7b);
  //draw button
  for (int i = 0; i < NUM_KEYS; i++)
  {
    key_b[i].initButton(&tft,
                      KEY_X + i * (KEY_W + KEY_SPACING_X),
                      KEY_Y + 0 * (KEY_H + KEY_SPACING_Y), // x, y, w, h, outline, fill, text
                      KEY_W,
                      KEY_H,
                      TFT_WHITE, // Outline
                      k_color[i], // Fill
                      TFT_WHITE, // Text
                      "", // 10 Byte Label
                      KEY_TEXTSIZE);

    // Adjust button label X delta according to array position
    // setLabelDatum(uint16_t x_delta, uint16_t y_delta, uint8_t datum)
    key_b[i].setLabelDatum(13 - (KEY_W/2), 2, ML_DATUM);

    // Draw button and specify label string
    // Specifying label string here will allow more than the default 10 byte label
    key_b[i].drawButton(false, "OFF");
  }
}

void loop()
{
  uint16_t t_x = 0, t_y = 0; // To store the touch coordinates
  uint8_t i = 0;
  bool pressed = tft.getTouch(&t_x, &t_y);
  for (i = 0; i < NUM_KEYS; i++)
  {
    if (pressed && key_b[i].contains(t_x, t_y))
    { 
      key_b[i].press(true);  // tell the button it is pressed
    }
    else
    {
      key_b[i].press(false);  // tell the button it is NOT pressed
    }
  }

    // Check if any key has changed state
  for (i = 0; i < NUM_KEYS; i++) 
  {
    // If button was just pressed, redraw inverted button
    if (key_b[i].justPressed())
    {
      if(led_on_flag == 0)
      {
        key_b[i].drawButton(true, "OFF");
      }
      else if(led_on_flag == 1) 
      {
        key_b[i].drawButton(true, "ON");
      }
      else
      {
        key_b[i].drawButton(true, "FLI");
      }
    }
    // If button was just released, redraw normal color button
    if (key_b[i].justReleased()) 
    {
      if(led_on_flag == 0)
      {
        key_b[i].drawButton(false, "ON");
        light_led(i, LED_ON);
      }
      else if(led_on_flag == 1)
      {
        key_b[i].drawButton(false, "FLI");
        led_flick(i);
      }
      else
      {
        key_b[i].drawButton(false, "OFF");
        light_led(i, LED_OFF);
      }
      if(led_on_flag++ >= 2)
      {
          led_on_flag = 0;
      }
    }
  }
  if(pressed && ((t_x>=tft.width()/2-128)&&(t_x<tft.width()/2+128)&&t_y > 219&&t_y < 239))
  {
    ledcAttachPin(led, channel);
    tft.setTextColor(0xFFE0, TFT_BLACK);
    tft.fillRoundRect(t_x-10, 219, tft.width()/2+138-t_x+10, 21,10,0x8430);
    tft.fillRoundRect(tft.width()/2-138, 219, t_x-tft.width()/2+148, 21,10,0x07FF);
    tft.fillCircle(t_x, 229,10,TFT_MAGENTA);
    tft.setTextPadding(50);
    tft.drawNumber((long)t_x-(tft.width()/2-128), tft.width()/2-15, 155,2);
    ledcWrite(channel, 255-(t_x-(tft.width()/2-128)));
  }
}
