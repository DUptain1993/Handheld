from machine import SPI, Pin
from ST7796 import LCD_35_ST7796, SPI_W_SPEED, SPI_R_SPEED, Delay_Ms
from touch import XPT2046
from Font_8x16_EN import Font_8x16_EN
import time

#pin define
LCD_RS = 2
LCD_CS = 15
#LCD_RST = 27  #connect to ESP32 reset pin
LCD_SCK = 14
LCD_SDA = 13
LCD_SDO = 12
LCD_BL = 27
TOUCH_CS = 33

spi = SPI(1,baudrate=SPI_W_SPEED,sck=Pin(LCD_SCK),mosi=Pin(LCD_SDA),miso=Pin(LCD_SDO))
mylcd = LCD_35_ST7796(spi, LCD_CS, LCD_RS, LCD_BL)
mytouch = XPT2046(spi, TOUCH_CS, lcd_speed = SPI_W_SPEED)

if __name__=='__main__':
    coord = [0xFFFF, 0xFFFF]
    mylcd.LCD_Set_Rotate(0)
    mytouch.Set_Touch_Cal(253, 240, 3464, 3622, 320, 480, 1)
    mylcd.LCD_Clear(0xFFFF)
    mylcd.Show_String(mylcd.lcd_width - 36, 0, "RST", Font_8x16_EN, 0x001F)
    while True:
        if mytouch.Read_Touch(coord, 100):
            if coord[0] < mylcd.lcd_width and coord[1] < mylcd.lcd_height:
                if coord[0] > mylcd.lcd_width - 36 and coord[1] < 16:
                    mylcd.LCD_Clear(0xFFFF)
                    mylcd.Show_String(mylcd.lcd_width - 36, 0, "RST", Font_8x16_EN, 0x001F)
                else:
                    mylcd.Fill_Circle(coord[0], coord[1], 2, 0xF800)
        else:
            coord = [0xFFFF, 0xFFFF]
        