//This program is a demo of how to display picture and 
//how to use rotate function to display string.

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
#include <SPI.h>


TFT_eSPI mylcd = TFT_eSPI(); 

//define some colour values
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//clear screen
void fill_screen_test()
{
  mylcd.fillScreen(BLACK);delay(500);  
  mylcd.fillScreen(RED);delay(500); 
  mylcd.fillScreen(GREEN);delay(500); 
  mylcd.fillScreen(BLUE);delay(500); 
  mylcd.fillScreen(BLACK);delay(500); 
}

//display some strings
void text_test()
{
  mylcd.fillScreen(BLACK);  
  mylcd.setTextColor(WHITE);
  mylcd.drawString("Hello World!", 2,2,1);
  
  mylcd.setTextColor(YELLOW);
  mylcd.drawFloat(1234.56, 3, 2, 10,2);

  mylcd.setTextColor(RED);
  mylcd.drawNumber(0xDEADBEF, 0, 24,4);

  mylcd.setTextColor(BLUE);
  mylcd.drawString("apmp", 2,46,6);
  mylcd.setTextColor(GREEN);
  mylcd.drawString("I implore thee,", 2,96,2);

  mylcd.drawString("my foonting turlingdromes.", 2, 112,1);
  mylcd.drawString("And hooptiously drangle me", 2, 120,1);
  mylcd.drawString("with crinkly bindlewurdles,", 2, 128,1);
  mylcd.drawString("Or I will rend thee", 2, 136,1);
  mylcd.drawString("in the gobberwarts", 2, 144,1);
  mylcd.drawString("with my blurglecruncheon,", 2, 152,1);
  mylcd.drawString("see if I don't!", 2, 160,1);
}

//draw some oblique lines
void lines_test(void)
{
    int i=0;
    mylcd.fillScreen(BLACK); 
    for(i = 0; i< mylcd.width();i+=5)
    {
       mylcd.drawLine(0, 0, i, mylcd.height()-1,GREEN);
     }
     for(i = mylcd.height()-1; i>= 0;i-=5)
     {
       mylcd.drawLine(0, 0, mylcd.width()-1, i,GREEN);
     }
     
     mylcd.fillScreen(BLACK); 
    for(i = mylcd.width() -1; i>=0;i-=5)
    {
      mylcd.drawLine(mylcd.width()-1, 0, i, mylcd.height()-1,RED);
     }
    for(i = mylcd.height()-1; i>=0;i-=5)
    {
      mylcd.drawLine(mylcd.width()-1, 0, 0, i,RED);
     }
     
     mylcd.fillScreen(BLACK); 
     for(i = 0; i < mylcd.width();i+=5)
    {
      mylcd.drawLine(0, mylcd.height()-1, i, 0,GREEN);
     }
     for(i = 0; i < mylcd.height();i+=5)
    {
      mylcd.drawLine(0, mylcd.height()-1, mylcd.width()-1, i,GREEN);
     }

      mylcd.fillScreen(BLACK); 
     for(i = mylcd.width()-1; i >=0;i-=5)
    {
      mylcd.drawLine(mylcd.width()-1, mylcd.height()-1, i, 0,YELLOW);
     }
     for(i = 0; i<mylcd.height();i+=5)
    {
      mylcd.drawLine(mylcd.width()-1, mylcd.height()-1, 0, i,YELLOW);
     }
}

//draw some vertical lines and horizontal lines
void h_l_lines_test(void)
{
    int i=0;
    mylcd.fillScreen(BLACK);
    for(i =0;i<mylcd.height();i+=5)
    {
      mylcd.drawFastHLine(0,i,mylcd.width(),GREEN); 
      delay(5);
    }
     for(i =0;i<mylcd.width();i+=5)
    {
      mylcd.drawFastVLine(i,0,mylcd.height(),BLUE); 
           delay(5);
    }
}

//draw some rectangles
void rectangle_test(void)
{
  int i = 0;
   mylcd.fillScreen(BLACK);
   for(i = 0;i<mylcd.width()/2;i+=4)
   {
      mylcd.drawRect(i,(mylcd.height()-mylcd.width())/2+i,mylcd.width()-2*i,mylcd.width()-2*i,GREEN);  
        delay(5);
   }
}

//draw some filled rectangles
void fill_rectangle_test(void)
{
  int i = 0;
   mylcd.fillScreen(BLACK);
   mylcd.fillRect(0,(mylcd.height()-mylcd.width())/2,mylcd.width(),mylcd.width(),YELLOW);
   for(i = 0;i<mylcd.width()/2;i+=4)
   {
      mylcd.drawRect(i,(mylcd.height()-mylcd.width())/2+i,mylcd.width()-2*i,mylcd.width()-2*i,MAGENTA);  
        delay(5);
   }
   for(i = 0;i<mylcd.width()/2;i+=4)
   {
      mylcd.fillRect(i,(mylcd.height()-mylcd.width())/2+i,mylcd.width()-2*i,mylcd.width()-2*i,random(0xFFFF));  
        delay(5);
   }
}

//draw some filled circles
void fill_circles_test(void)
{
  int r=10,i=0,j=0;
   mylcd.fillScreen(BLACK);
  for(i=r;i<mylcd.width();i+=2*r)
  {
    for(j=r;j<mylcd.height();j+=2*r)
    {
      mylcd.fillCircle(i, j, r,MAGENTA);
    }
  }
}

//draw some circles
void circles_test(void)
{
  int r=10,i=0,j=0;
  for(i=0;i<mylcd.width()+r;i+=2*r)
  {
    for(j=0;j<mylcd.height()+r;j+=2*r)
    {
      mylcd.drawCircle(i, j, r,GREEN);
    }
  }  
}

//draw some triangles
void triangles_test(void)
{
   int i = 0;
   mylcd.fillScreen(BLACK);
   for(i=0;i<mylcd.width()/2;i+=5)
   {
      mylcd.drawTriangle(mylcd.width()/2-1,mylcd.height()/2-1-i,
                    mylcd.width()/2-1-i,mylcd.height()/2-1+i,
                    mylcd.width()/2-1+i,mylcd.height()/2-1+i,mylcd.color565(0, i+64, i+64));                   
   }
}

//draw some filled triangles
void fill_triangles_test(void)
{
   int i = 0;
   mylcd.fillScreen(BLACK);
    for(i=mylcd.width()/2-1;i>0;i-=5)
   {
      mylcd.fillTriangle(mylcd.width()/2-1,mylcd.height()/2-1-i,
                    mylcd.width()/2-1-i,mylcd.height()/2-1+i,
                    mylcd.width()/2-1+i,mylcd.height()/2-1+i,mylcd.color565(0, i+64, i+64));                   
      mylcd.fillTriangle(mylcd.width()/2-1,mylcd.height()/2-1-i,
                    mylcd.width()/2-1-i,mylcd.height()/2-1+i,
                    mylcd.width()/2-1+i,mylcd.height()/2-1+i,mylcd.color565(i, 0, i));                   
   }
}

//draw some round rectangles
void round_rectangle(void)
{
   int i = 0;
   mylcd.fillScreen(BLACK);
     for(i = 0;i<mylcd.width()/2;i+=4)
   {
      mylcd.fillRoundRect(i,(mylcd.height()-mylcd.width())/2+i,mylcd.width()-2*i,mylcd.width()-2*i,8,mylcd.color565(255-i,0,160-i));
        delay(5);
   } 
}

//draw some filled round rectangles
void fill_round_rectangle(void)
{
   int i = 0;
   mylcd.fillScreen(BLACK);
   for(i = 0;i<mylcd.width()/2;i+=4)
   {
      mylcd.fillRoundRect(i,(mylcd.height()-mylcd.width())/2+i,mylcd.width()-2*i,mylcd.width()-2*i,8,mylcd.color565(255-i,160-i,0));
        delay(5);
   } 
}

void setup() 
{
  mylcd.init();
}

void loop() 
{
  mylcd.setRotation(0);
  fill_screen_test();
  delay(500);
  text_test();
  delay(500);
  lines_test();
  delay(500);
  h_l_lines_test();
  delay(500);
  rectangle_test();
  delay(500);
  fill_rectangle_test();
  delay(500);
  fill_circles_test();
  delay(500);
  circles_test();
  delay(500);
  triangles_test();
  delay(500);
  fill_triangles_test();
  delay(500);
  round_rectangle();
  delay(500);
  fill_round_rectangle();
  delay(500);
 for(uint8_t rotation=0; rotation<4; rotation++) 
 {
    mylcd.setRotation(rotation);
    text_test();
    delay(1500);
 }
}
