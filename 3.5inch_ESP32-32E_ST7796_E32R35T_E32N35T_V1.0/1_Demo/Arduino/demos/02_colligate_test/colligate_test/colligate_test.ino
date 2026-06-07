//This program is a demo of how to use most of the functions 
//of the library with a supported display modules.

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

#define CENTER 240

TFT_eSPI my_lcd = TFT_eSPI(); 

//display main surface
unsigned long show_text(void)
{
    unsigned long time_start = micros();
    my_lcd.fillRect(0, 0, my_lcd.width(), 15,0x201F);
    my_lcd.setTextColor(0x07E0);
    my_lcd.drawCentreString("* Universal Color TFT Display Library *",CENTER,3,1);
    my_lcd.fillRect(0, my_lcd.height()-15, my_lcd.width(), 15,0x8410);
    my_lcd.setTextColor(0xFFFF);
    my_lcd.drawCentreString("<http://www.lcdwiki.com>",CENTER,my_lcd.height()-11,1);
    
    my_lcd.drawRect(0, 14, my_lcd.width(), my_lcd.height()-30,TFT_RED); 
    return micros() - time_start;
}

//display triangle functions
unsigned long show_triangle_function(void)
{
     uint16_t i;
     unsigned long time_start = micros();
     // Draw crosshairs
     my_lcd.drawFastVLine(my_lcd.width()/2-1, 15, my_lcd.height()-32, TFT_BLUE); 
     my_lcd.drawFastHLine(1, my_lcd.height()/2-1, my_lcd.width()-2, TFT_BLUE);
    
     for(i = 1;i <= (my_lcd.height()- 32)/2/10;i++)
     {
         my_lcd.drawFastHLine(my_lcd.width()/2-1-2, my_lcd.height()/2-1-i*10, 5, TFT_BLUE);
         my_lcd.drawFastHLine(my_lcd.width()/2-1-2, my_lcd.height()/2-1+i*10, 5, TFT_BLUE);
     }
     for(i = 1;i <= (my_lcd.width()-2)/2/10;i++)
     {
         my_lcd.drawFastVLine(my_lcd.width()/2-1-i*10, my_lcd.height()/2-1-2, 5, TFT_BLUE);
         my_lcd.drawFastVLine(my_lcd.width()/2-1+i*10, my_lcd.height()/2-1-2, 5, TFT_BLUE);
     }
     
     // Draw sin lines
     my_lcd.setTextColor(0x07FF);
     my_lcd.drawString("sin",5,17,2);

     for (i=1; i<my_lcd.width()-2; i++)
     {
        my_lcd.drawPixel(i,my_lcd.height()/2-1+(sin(((i*1.13)*3.14)/180)*95),0x07FF);
     }

     // Draw cos lines
     my_lcd.setTextColor(0x07E0);
     my_lcd.drawString("cos",5,29,2);
     for (i=1; i<my_lcd.width()-2; i++)
     {
        my_lcd.drawPixel(i,my_lcd.height()/2-1+(cos(((i*1.13)*3.14)/180)*95),0x07E0);
     }

     // Draw tan lines
     my_lcd.setTextColor(0xFFE0);
     my_lcd.drawString("tan",5,41,2);

     for (i=1; i<my_lcd.width()-2; i++)
     {
        my_lcd.drawPixel(i,my_lcd.height()/2-1+(tan(((i*1.13)*3.14)/180)*10),0xFFE0);
     }

     // Draw cot lines
     my_lcd.setTextColor(0xF800);
     my_lcd.drawString("cot",5,53,2);
     for (i=1; i<my_lcd.width()-2; i++)
     {
        my_lcd.drawPixel(i,my_lcd.height()/2-1+1/(tan(((i*1.13)*3.14)/180)*0.1),0xF800);
     }
     return micros()-time_start;
}

// Draw a moving sinewave
unsigned long show_sinewave(void)
{
   uint16_t x = 1,i,y,color;
   uint8_t buf[my_lcd.width()-2];
   unsigned long time_start = micros();
   int16_t t = 15;
   float k = 0.7;

   my_lcd.drawFastVLine(my_lcd.width()/2-1, 15, my_lcd.height()-32, TFT_BLUE);
   my_lcd.drawFastHLine(1, my_lcd.height()/2-1, my_lcd.width()-2, TFT_BLUE);
   
   for (i=1; i<((my_lcd.width()-2)*t); i++) 
   {
      x++;
      if (x==my_lcd.width()-1)
      {
          x=1;
      }
      if (i>my_lcd.width()-1)
      {
          if ((x==my_lcd.width()/2-1)||(buf[x-1]==my_lcd.height()/2-1))
          {
              color = TFT_BLUE; 
          }
          else
          {
             color = TFT_BLACK; 
          }
          my_lcd.drawPixel(x,buf[x-1],color);
    }
    y=my_lcd.height()/2-1+(sin(((i*k)*3.14)/180)*(90-(i/100)));
    my_lcd.drawPixel(x,y,0xFA1F);
    buf[x-1]=y;
  }
  return micros()- time_start;  
}

// Draw some filled rectangles
unsigned long show_fill_rectangle(void)
{
    uint16_t i,color;
    unsigned long time_start = micros();
    uint16_t side_len = (my_lcd.height()-40)/5;
    uint16_t x_spec = (my_lcd.width()-5*side_len)/2;
    uint16_t y_spec = (my_lcd.height()-5*side_len)/2;
    for(i = 0;i<5;i++)
    {
          switch (i)
          {
            case 0:
              color = 0xF818;
              break;
            case 1:
              color = TFT_RED;
              break;
            case 2:
              color = TFT_GREEN;
              break;
            case 3:
              color = TFT_BLUE;
              break;
            case 4:
              color = 0xFFE0;
              break;
            default:
              break;
          }   
          my_lcd.fillRect(x_spec+i*side_len-1, y_spec+i*side_len-1, side_len, side_len,color);
          my_lcd.fillRect(x_spec+i*side_len-1, y_spec+(4-i)*side_len-1, side_len, side_len,color);
     }
     return micros()- time_start;   
}

// Draw some filled round rectangles
unsigned long show_fill_round_rectangle(void)
{
    uint16_t i,color;
    unsigned long time_start = micros();
    uint16_t side_len = (my_lcd.height()-40)/5;
    uint16_t x_spec = (my_lcd.width()-5*side_len)/2;
    uint16_t y_spec = (my_lcd.height()-5*side_len)/2;
    for(i = 0;i<5;i++)
    {
          switch (i)
          {
            case 0:
              color = 0xF818;
              break;
            case 1:
              color = TFT_RED;
              break;
            case 2:
              color = TFT_GREEN;
              break;
            case 3:
              color = TFT_BLUE;
              break;
            case 4:
              color = 0xFFE0;
              break;
            default:
              break;
          }   
          my_lcd.fillRoundRect(x_spec+i*side_len-1, y_spec+i*side_len-1, side_len, side_len,10,color);
          my_lcd.fillRoundRect(x_spec+i*side_len-1, y_spec+(4-i)*side_len-1, side_len, side_len,10,color); 
     }
     return micros()- time_start;   
}

// Draw some filled circles
unsigned long show_fill_circle(void)
{
    uint16_t i,color;
    unsigned long time_start = micros();
    uint16_t r_len = (my_lcd.height()-40)/5/2;
    uint16_t x_spec = (my_lcd.width()-5*r_len*2)/2;
    uint16_t y_spec = (my_lcd.height()-5*r_len*2)/2;
    for(i = 0;i<5;i++)
    {
          switch (i)
          {
            case 0:
              color = 0xF818;
              break;
            case 1:
              color = TFT_RED;
              break;
            case 2:
              color = TFT_GREEN;
              break;
            case 3:
              color = TFT_BLUE;
              break;
            case 4:
              color = 0xFFE0;
              break;
            default:
              break;
          }   
          my_lcd.fillCircle(x_spec+r_len+i*r_len*2-1, y_spec+r_len+i*r_len*2-1,r_len,color);
          my_lcd.fillCircle(x_spec+r_len+i*r_len*2-1, y_spec+(5-i)*r_len*2-r_len-1,r_len,color); 
     }
     return micros()- time_start;   
 }

// Draw some filled triangles
unsigned long show_fill_triangle(void)
{
    uint16_t i,color;
    unsigned long time_start = micros();
    uint16_t h_len = (my_lcd.height()-40)/5;
    uint16_t side_len = (h_len*115)/100;
    uint16_t x_spec = (my_lcd.width()-5*side_len)/2;
    uint16_t y_spec = (my_lcd.height()-5*h_len)/2;
    for(i = 0;i<5;i++)
    {
          switch (i)
          {
            case 0:
              color = 0xF818;
              break;
            case 1:
              color = TFT_RED;
              break;
            case 2:
              color = TFT_GREEN;
              break;
            case 3:
              color = TFT_BLUE;
              break;
            case 4:
              color = 0xFFE0;
              break;
            default:
              break;
          } 
          my_lcd.fillTriangle(x_spec+i*side_len-1,y_spec+(i+1)*h_len-1,x_spec+side_len/2+i*side_len-1,y_spec+i*h_len-1,x_spec+(i+1)*side_len-1,y_spec+(i+1)*h_len-1,color); 
          my_lcd.fillTriangle(x_spec+i*side_len-1,y_spec+(5-i)*h_len-1,x_spec+side_len/2+i*side_len-1,y_spec+(4-i)*h_len-1,x_spec+(i+1)*side_len-1,y_spec+(5-i)*h_len-1,color);  
     }
     return micros()- time_start;   
}

// Draw some lines in a pattern
unsigned long show_grid_lines(void)
{
    uint16_t i;
    unsigned long time_start = micros();
   float k=1.6;
    for (i=16; i<my_lcd.height()-17; i+=5)
    {
       my_lcd.drawLine(1, i, (i*k)-10, my_lcd.height()-18, TFT_RED);
     }
     for (i=my_lcd.height()-17; i>16; i-=5)
    {
      my_lcd.drawLine(my_lcd.width()-2, i, (i*k)-11, 16, TFT_RED);
    }
    for (i=my_lcd.height()-16; i>16; i-=5)
    {
      my_lcd.drawLine(1, i, (my_lcd.height()-17)*k+10-(i*k), 16, 0x07FF);
    }
    for (int i=15; i<my_lcd.height()-17; i+=5)
    {
        my_lcd.drawLine(my_lcd.width()-2, i, (my_lcd.height()-17)*k+10-(i*k), my_lcd.height()-18, 0x07FF);
    }
    return micros()- time_start;   
}

// Draw some random pixels
unsigned long show_random_pixels(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    for(i = 0;i< 5000;i++)
    {
       my_lcd.drawPixel(2+random(my_lcd.width()-4),17+random(my_lcd.height()-34),random(0xFFFF));
    }
    return micros()- time_start; 
}

// Draw some random lines
unsigned long show_random_lines(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    for(i = 0;i< 300;i++)
    {
       my_lcd.drawLine(2+random(my_lcd.width()-4),17+random(my_lcd.height()-34),2+random(my_lcd.width()-4),17+random(my_lcd.height()-34),random(0xFFFF));
    }
    return micros()- time_start; 
}

// Draw some random rectangles
unsigned long show_random_rectangles(void)
{
    uint16_t i,x,y,x1,y1,r;
    unsigned long time_start = micros();
    for(i = 0;i< 150;i++)
    {
      x = 2+random(my_lcd.width()-4);
      y = 17+random(my_lcd.height()-34);
      x1 = 2+random(my_lcd.width()-4);
      y1 = 17+random(my_lcd.height()-34);
      if (x1<x) 
      {
        r=x;x=x1;x1=r;
      }
      if (y1<y) 
      {
        r=y;y=y1;y1=r;
      }
      my_lcd.drawRect(x,y,x1-x,y1-y,random(0xFFFF));
    }
    return micros()- time_start; 
}

// Draw some random round rectangles
unsigned long show_random_round_rectangles(void)
{
     uint16_t i,x,y,x1,y1,r;
    unsigned long time_start = micros();
    for(i = 0;i< 150;i++)
    {
      x = 2+random(my_lcd.width()-4);
      y = 17+random(my_lcd.height()-34);
      x1 = 2+random(my_lcd.width()-4);
      y1 = 17+random(my_lcd.height()-34);
      if (x1<x) 
      {
        r=x;x=x1;x1=r;
      }
      if (y1<y) 
      {
        r=y;y=y1;y1=r;
      }
       my_lcd.drawRoundRect(x,y,x1-x,y1-y,5,random(0xFFFF));
    }
    return micros()- time_start; 
}

// Draw some random circles
unsigned long show_random_circles(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    for(i = 0;i< 150;i++)
    {
       my_lcd.drawCircle(41+random(my_lcd.width()-82), 56+random(my_lcd.height()-112), random(40),random(0xFFFF));
    }
    return micros()- time_start; 
}

// Draw some random triangles
unsigned long show_random_triangles(void)
{
    uint16_t i;
    unsigned long time_start = micros();
    for(i = 0;i< 150;i++)
    {
       my_lcd.drawTriangle(2+random(my_lcd.width()-4),17+random(my_lcd.height()-34),2+random(my_lcd.width()-4),17+random(my_lcd.height()-34),2+random(my_lcd.width()-4),17+random(my_lcd.height()-34),random(0xFFFF));
    }
    return micros()- time_start; 
}

//Clear the screen
void clear_screen(void)
{
   delay(2000);  
   my_lcd.fillRect(1, 15, my_lcd.width()-2,my_lcd.height()-32,TFT_BLACK);
}

unsigned long (*show_function[])(void) = 
 {
                                          show_text,
                                          show_triangle_function,
                                          show_sinewave,
                                          show_fill_rectangle,
                                          show_fill_round_rectangle,
                                          show_fill_circle,
                                          show_fill_triangle,
                                          show_grid_lines,
                                          show_random_pixels,
                                          show_random_lines,
                                          show_random_rectangles,
                                          show_random_round_rectangles,
                                          show_random_circles,
                                          show_random_triangles,
                                          };

 const char* show_str[] =
 {
                       "TEST_TX  :", 
                       "TEST_TF  :",
                       "TEST_SW  :",
                       "TEST_FR  :",
                       "TEST_FRR :",
                       "TEST_FC  :",
                       "TEST_FT  :",
                       "TEST_GL  :",
                       "TEST_RP  :",
                       "TEST_RL  :",
                       "TEST_RR  :",
                       "TEST_RRR :",
                       "TEST_RC  :",
                       "TEST_RT  :",
                     };
//display the running time of programs 
unsigned long show_total_time(void)
{
     uint16_t i;
     unsigned long buf[14];
     unsigned long time_start = micros();
     for(i = 0;i< 14;i++)
     {
        buf[i] = show_function[i](); 
        clear_screen();  
     }
     for(i = 0;i<14; i++)
     {
         my_lcd.setTextColor(0xFD20);
         my_lcd.drawString(show_str[i], (my_lcd.width()-260)/2-1, (my_lcd.height()-230)/2+i*16-1,2);

         my_lcd.setTextColor(TFT_GREEN);
         my_lcd.drawNumber(buf[i], (my_lcd.width()-260)/2-1+200, (my_lcd.height()-230)/2+i*16-1,2);
     }
     delay(5000);
     return micros()- time_start; 
}

//display ending and total running time
void show_end(unsigned long run_time)
{
    my_lcd.fillScreen(0x07FF);
    my_lcd.fillRoundRect(my_lcd.width()/2-1-120+1, my_lcd.height()/2-1-60+1, 240, 120,5,TFT_RED);
    my_lcd.setTextColor(0x07FF);
    my_lcd.drawCentreString("Running over!",CENTER,my_lcd.height()/2-1-40,1);
    my_lcd.drawCentreString("That's ok!",CENTER,my_lcd.height()/2-1-30,1);
    my_lcd.drawCentreString("After a few seconds,",CENTER,my_lcd.height()/2-1-20,1);
    my_lcd.drawCentreString("it will restart.",CENTER,my_lcd.height()/2-1-10,1);
    my_lcd.drawCentreString("Please wait ...",CENTER,my_lcd.height()/2-1,1);
    my_lcd.setTextColor(0xFFE0);
    my_lcd.drawString("Total runtime(us):  ", my_lcd.width()/2-1-90,my_lcd.height()/2-1+40,2);
    my_lcd.setTextColor(TFT_GREEN);
    my_lcd.drawNumber(run_time, my_lcd.width()/2-1+30, my_lcd.height()/2-1+40,2);
    delay(10000);   
}

void setup() 
{
  my_lcd.init();
  my_lcd.setRotation(1);
}

void loop() 
{
    unsigned long total_time;
      my_lcd.fillScreen(TFT_BLACK); 
    total_time = show_total_time();
    show_end(total_time);    
}
