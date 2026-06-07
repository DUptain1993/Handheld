//This program is a demo of drawing

//pin usage as follow:
//                   CS  DC/RS  RESET    SDI/MOSI  SCK   SDO/MISO  BL  TOUCH_CS   VCC    GND    
//ESP32-WROOM-32E:   15    2   ESP32-EN     13      14      12     27     33      5V     GND 

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
#include <TFT_eSPI.h> 
#include <SPI.h>

TFT_eSPI my_lcd = TFT_eSPI();

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

uint16_t px0 = 0, px1 = 0, py0 = 0, py1 = 0;

void LCD_Draw_Line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t Size,uint16_t colour)
{
  uint16_t t; 
  int xerr=0,yerr=0,delta_x,delta_y,distance; 
  int incx,incy,uRow,uCol; 
  if(x1<Size||x2<Size||y1<Size||y2<Size)
  {
    return;  
  }
  delta_x=x2-x1; //计算坐标增量 
  delta_y=y2-y1; 
  uRow=x1; 
  uCol=y1; 
  if(delta_x>0)incx=1; //设置单步方向 
  else if(delta_x==0)incx=0;//垂直线 
  else {incx=-1;delta_x=-delta_x;} 
  if(delta_y>0)incy=1; 
  else if(delta_y==0)incy=0;//水平线 
  else{incy=-1;delta_y=-delta_y;} 
  if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
  else distance=delta_y; 
  for(t=0;t<=distance+1;t++ )//画线输出 
  {  
     my_lcd.fillCircle(uRow, uCol, Size,colour);
    //gui_circle(uRow, uCol,color, size, 1);
    //LCD_DrawPoint(uRow,uCol);//画点 
    xerr+=delta_x ; 
    yerr+=delta_y ; 
    if(xerr>distance) 
    { 
      xerr-=distance; 
      uRow+=incx; 
    } 
    if(yerr>distance) 
    { 
      yerr-=distance; 
      uCol+=incy; 
    } 
  }  
}

void setup(void) 
{
  my_lcd.init();
  my_lcd.setRotation(0); 
  uint16_t calData[5] = { 263, 3443, 256, 3643, 4 };
  my_lcd.setTouch(calData);
  my_lcd.fillScreen(WHITE);
  my_lcd.setTextColor(BLUE);
  my_lcd.drawString("RST",my_lcd.width()-36,0,2);
}

void loop()
{
      if(my_lcd.getTouch(&px0, &py0, 600)) 
      {
        if((px0 < my_lcd.width())&&(py0 < my_lcd.height())) 
        {
          if(px1 == 0xFFFF)
          {
            px1 = px0;
            py1 = py0;
          }
           if(px0 > (my_lcd.width()-36)&&(py0 < 16))
           {
              my_lcd.fillScreen(WHITE);
              my_lcd.setTextColor(BLUE);
              my_lcd.drawString("RST",my_lcd.width()-36,0,2);
            } 
            else
            {
                LCD_Draw_Line(px1,py1,px0,py0,2,RED);
            }          
            px1 = px0;
            py1 = py0;
          }
       }
       else
       {
          px1 = 0xFFFF;
        }
}
