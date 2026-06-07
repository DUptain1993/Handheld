from machine import SPI, Pin
from ST7796 import LCD_35_ST7796, SPI_W_SPEED, Delay_Ms
from Font_8x16_EN import Font_8x16_EN
from Font_6x8_EN import Font_6x8_EN
from Font_6x12_EN import Font_6x12_EN
from Font_12x24_EN import Font_12x24_EN
from Font_16x32_EN import Font_16x32_EN
from Font_16x16_CN import Font_16x16_CN
from Font_24x24_CN import Font_24x24_CN
from Font_32x32_CN import Font_32x32_CN

#pin define
LCD_RS = 2
LCD_CS = 15
#LCD_RST = 27  #connect to ESP32 reset pin
LCD_SCK = 14
LCD_SDA = 13
LCD_SDO = 12
LCD_BL = 27

#color define
BLACK = 0x0000
WHITE = 0xFFFF
RED = 0xF800
GREEN = 0x07E0
BLUE = 0x001F
MAGENAT = 0xF81F
DARKBLUE = 0x01CF
LIGHTGREEN = 0x841F
YELLOW = 0xFFE0

spi = SPI(1,baudrate=SPI_W_SPEED,sck=Pin(LCD_SCK),mosi=Pin(LCD_SDA),miso=Pin(LCD_SDO))
mylcd = LCD_35_ST7796(spi, LCD_CS, LCD_RS, LCD_BL)

def Show_english():
    mylcd.LCD_Clear(WHITE)
    mylcd.Show_String(20, 20, "6x8: 1234567890abcdeABCDE*%^,.{}()", Font_6x8_EN, RED)
    mylcd.Show_String(20, 30, "6x8: 1234567890abcdeABCDE*%^,.{}()", Font_6x8_EN, GREEN, MAGENAT)
    mylcd.Show_String(20, 40, "6x12: 1234567890abcdeABCDE*%^,.{}()", Font_6x12_EN, BLUE)
    mylcd.Show_String(20, 55, "6x12: 1234567890abcdeABCDE*%^,.{}()", Font_6x12_EN, BLACK, YELLOW)
    mylcd.Show_String(20, 70, "8x16: 1234567890abcdeABCDE*%^,.{}()", Font_8x16_EN, MAGENAT)
    mylcd.Show_String(20, 88, "8x16: 1234567890abcdeABCDE*%^,.{}()", Font_8x16_EN, WHITE, BLACK)
    mylcd.Show_String(20, 106, "12x24: 123450abeABE%^,.{)", Font_12x24_EN, DARKBLUE)
    mylcd.Show_String(20, 132, "12x24: 123450abeABE%^,.{)", Font_12x24_EN, YELLOW, RED)
    mylcd.Show_String(20, 160, "16x32: 123abABC%{)", Font_16x32_EN, BLUE)
    mylcd.Show_String(20, 195, "16x32: 123abABC%{)", Font_16x32_EN, RED, YELLOW)
    Delay_Ms(1500)
def Show_chinese():
    mylcd.LCD_Clear(WHITE)
    mylcd.Show_String(20, 20, "16x16:", Font_8x16_EN, RED)
    mylcd.Show_String(68, 20, "中文汉字显示", Font_16x16_CN, RED)
    mylcd.Show_String(20, 38, "16x16:", Font_8x16_EN, DARKBLUE, YELLOW)
    mylcd.Show_String(68, 38, "中文汉字显示", Font_16x16_CN, DARKBLUE, YELLOW)
    mylcd.Show_String(20, 56, "24x24:", Font_12x24_EN, BLACK)
    mylcd.Show_String(92, 56, "中文汉字显示", Font_24x24_CN, BLACK)
    mylcd.Show_String(20, 82, "24x24:", Font_12x24_EN, WHITE, BLACK)
    mylcd.Show_String(92, 82, "中文汉字显示", Font_24x24_CN, WHITE, BLACK)
    mylcd.Show_String(20, 108, "32x32:", Font_16x32_EN, BLUE)
    mylcd.Show_String(116, 108, "中文汉字显示", Font_32x32_CN, BLUE)
    mylcd.Show_String(20, 142, "32x32:", Font_16x32_EN, YELLOW, RED)
    mylcd.Show_String(116, 142, "中文汉字显示", Font_32x32_CN, YELLOW, RED)
    Delay_Ms(1500)
if __name__=='__main__':
    while True:
        Show_english()
        Show_chinese()