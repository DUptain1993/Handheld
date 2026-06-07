from machine import Pin,SPI
import time
import ustruct
import random

#pin define
LCD_RS = 2
LCD_CS = 15
#LCD_RST = 27  #connect to ESP32 reset pin
LCD_SCK = 14
LCD_SDA = 13
LCD_SDO = 12
LCD_BL = 27

#mem size
MEM_SIZE = 5120  #5x1024

#LCD size
LCD_W = 320
LCD_H = 480

#color define
BLACK = 0x0000
WHITE = 0xFFFF
RED = 0xF800
GREEN = 0x07E0
BLUE = 0x001F
GRAY = 0x8430

class LCD_35_ST7796():
    def __init__(self):
        self.rs = Pin(LCD_RS,Pin.OUT)
        self.cs = Pin(LCD_CS,Pin.OUT)
        self.bl = Pin(LCD_BL,Pin.OUT)
        self.rs(1)
        self.cs(1)
        self.spi = SPI(1,80_000_000,sck=Pin(LCD_SCK),mosi=Pin(LCD_SDA),miso=Pin(LCD_SDO))
        self.LCD_init()
        self.bl(1)
    def LCD_Write_Reg(self,reg):
        self.cs(0)
        self.rs(0)
        self.spi.write(bytearray([reg]))
        self.cs(1)
    def LCD_Write_Data(self,dat):
        self.cs(0)
        self.rs(1)
        self.spi.write(bytearray([dat]))
        self.cs(1)
    def LCD_Set_Windows(self,x1,y1,x2,y2):
        self.LCD_Write_Reg(0x2A)
        self.LCD_Write_Data(x1>>8)
        self.LCD_Write_Data(x1&0xFF)
        self.LCD_Write_Data(x2>>8)
        self.LCD_Write_Data(x2&0xFF)
        self.LCD_Write_Reg(0x2B)
        self.LCD_Write_Data(y1>>8)
        self.LCD_Write_Data(y1&0xFF)
        self.LCD_Write_Data(y2>>8)
        self.LCD_Write_Data(y2&0xFF)
        self.LCD_Write_Reg(0x2C)
    def LCD_Fill(self,sx,sy,w,h,color):
        if sx >= LCD_W or sy >= LCD_H:
            return
        if (sx + w) > LCD_W or (sy + h) > LCD_H:
            return
        if (w < 1 or w > LCD_W) or (h < 1 or h > LCD_H):
            return
        self.LCD_Set_Windows(sx,sy,sx + w - 1,sy + h - 1)
        self.cs(0)
        self.rs(1)
        quo, rest = divmod(w*h,MEM_SIZE)
        if quo:
            buf = ustruct.pack(">H",color)*MEM_SIZE
            for i in range(quo):
                self.spi.write(buf)
        if rest != 0:
            buf = ustruct.pack(">H",color)*rest
            self.spi.write(buf)
        self.cs(1)
    def LCD_Clear(self,color):
        self.LCD_Fill(0,0,LCD_W,LCD_H,color)
    def LCD_init(self):
        self.LCD_Write_Reg(0x11)
        time.sleep_ms(120)
        
        self.LCD_Write_Reg(0x36)
        self.LCD_Write_Data(0x48)  
        
        self.LCD_Write_Reg(0x3A)
        self.LCD_Write_Data(0x55)
        
        self.LCD_Write_Reg(0xF0)
        self.LCD_Write_Data(0xC3)
        
        self.LCD_Write_Reg(0xF0)
        self.LCD_Write_Data(0x96)
        
        self.LCD_Write_Reg(0xB4)
        self.LCD_Write_Data(0x01) 

        self.LCD_Write_Reg(0xB7)
        self.LCD_Write_Data(0xC6)
  
        self.LCD_Write_Reg(0xC0)
        self.LCD_Write_Data(0x80)
        self.LCD_Write_Data(0x45)

        self.LCD_Write_Reg(0xC1)
        self.LCD_Write_Data(0x13)
  
        self.LCD_Write_Reg(0xC2)
        self.LCD_Write_Data(0xA7)

        self.LCD_Write_Reg(0xC5)
        self.LCD_Write_Data(0x20)
        
        self.LCD_Write_Reg(0xE8)
        self.LCD_Write_Data(0x40)
        self.LCD_Write_Data(0x8A)
        self.LCD_Write_Data(0x00)
        self.LCD_Write_Data(0x00)
        self.LCD_Write_Data(0x29)
        self.LCD_Write_Data(0x19)
        self.LCD_Write_Data(0xA5)
        self.LCD_Write_Data(0x33)

        self.LCD_Write_Reg(0xE0)
        self.LCD_Write_Data(0xD0)
        self.LCD_Write_Data(0x08)
        self.LCD_Write_Data(0x0F)
        self.LCD_Write_Data(0x06)
        self.LCD_Write_Data(0x06)
        self.LCD_Write_Data(0x33)
        self.LCD_Write_Data(0x30)
        self.LCD_Write_Data(0x33)
        self.LCD_Write_Data(0x47)
        self.LCD_Write_Data(0x17)
        self.LCD_Write_Data(0x13)
        self.LCD_Write_Data(0x13)
        self.LCD_Write_Data(0x2B)
        self.LCD_Write_Data(0x31)
        
        self.LCD_Write_Reg(0XE1)
        self.LCD_Write_Data(0xD0)
        self.LCD_Write_Data(0x0A)
        self.LCD_Write_Data(0x11)
        self.LCD_Write_Data(0x0B)
        self.LCD_Write_Data(0x09)
        self.LCD_Write_Data(0x07)
        self.LCD_Write_Data(0x2F)
        self.LCD_Write_Data(0x33)
        self.LCD_Write_Data(0x47)
        self.LCD_Write_Data(0x38)
        self.LCD_Write_Data(0x15)
        self.LCD_Write_Data(0x16)
        self.LCD_Write_Data(0x2C)
        self.LCD_Write_Data(0x32)
        
        self.LCD_Write_Reg(0xF0)
        self.LCD_Write_Data(0x3C)
        
        self.LCD_Write_Reg(0xF0)
        self.LCD_Write_Data(0x69)
        
        time.sleep_ms(120)

        self.LCD_Write_Reg(0X29)
if __name__=='__main__':
    mylcd = LCD_35_ST7796()
    while True:
        mylcd.LCD_Clear(RED)
        time.sleep_ms(500)
        mylcd.LCD_Clear(GREEN)
        time.sleep_ms(500)
        mylcd.LCD_Clear(BLUE)
        time.sleep_ms(500)
        mylcd.LCD_Clear(GRAY)
        time.sleep_ms(500)
        mylcd.LCD_Clear(WHITE)
        time.sleep_ms(500)
        mylcd.LCD_Clear(BLACK)
        time.sleep_ms(500)
        for i in range(2000):
            mylcd.LCD_Fill(random.randint(0,LCD_W-1),random.randint(0,LCD_H-1),random.randint(0,LCD_W),random.randint(0,LCD_H),random.randint(0,0xFFFF))