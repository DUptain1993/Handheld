from machine import SPI, Pin, UART
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

uart = UART(1, baudrate=115200, tx=1, rx=3)

spi = SPI(1,baudrate=SPI_W_SPEED,sck=Pin(LCD_SCK),mosi=Pin(LCD_SDA),miso=Pin(LCD_SDO))
mylcd = LCD_35_ST7796(spi, LCD_CS, LCD_RS, LCD_BL)
mytouch = XPT2046(spi, TOUCH_CS, lcd_speed = SPI_W_SPEED)

def case_0():
    mylcd.Draw_Hline(0, 0, 15, 0xFFFF)
    mylcd.Draw_line(0, 0, 15, 15, 0xFFFF)
    mylcd.Draw_Vline(0, 0, 15, 0xFFFF)
def case_1():
    mylcd.Draw_Hline(0, mylcd.lcd_height - 1, 15, 0xFFFF)
    mylcd.Draw_line(0, mylcd.lcd_height - 1, 15, mylcd.lcd_height - 1 - 15, 0xFFFF)
    mylcd.Draw_Vline(0, mylcd.lcd_height - 1 - 15, 15, 0xFFFF)
def case_2():
    mylcd.Draw_Hline(mylcd.lcd_width - 1 - 15, 0, 15, 0xFFFF)
    mylcd.Draw_line(mylcd.lcd_width - 1 - 15, 15, mylcd.lcd_width - 1, 0, 0xFFFF)
    mylcd.Draw_Vline(mylcd.lcd_width - 1, 0, 15, 0xFFFF)
def case_3():
    mylcd.Draw_Hline(mylcd.lcd_width - 1 - 15, mylcd.lcd_height - 1, 15, 0xFFFF)
    mylcd.Draw_line(mylcd.lcd_width - 1 - 15, mylcd.lcd_height - 1 - 15, mylcd.lcd_width - 1, mylcd.lcd_height - 1, 0xFFFF)
    mylcd.Draw_Vline(mylcd.lcd_width - 1, mylcd.lcd_height - 1 - 15, 15, 0xFFFF)
    
if __name__=='__main__':
    coord = [0xFFFF, 0xFFFF]
    val = [0, 0, 0, 0, 0, 0, 0, 0]
    mylcd.LCD_Set_Rotate(1)
    mylcd.LCD_Clear(0)
    mylcd.Show_String((mylcd.lcd_width - 208) // 2, (mylcd.lcd_height-16) // 2, "Touch corners as indicated", Font_8x16_EN, 0xF800)
    for i in range(4):
        mylcd.Fill_Rect(0, 0, mylcd.lcd_width, 16, 0)
        mylcd.Fill_Rect(0, mylcd.lcd_height-16, mylcd.lcd_width, 16, 0)
        switch = {
            0: case_0,
            1: case_1,
            2: case_2,
            3: case_3,
        }
        switch[i]()
        if i > 0:
            Delay_Ms(1000)
        for j in range(8):
            while True:
                if mytouch.Touch_Pressed(coord, 100):
                    break
            val[i*2] += coord[0]
            val[i*2+1] += coord[1]       
        val[i*2] //= 8
        val[i*2+1] //= 8
    #print(val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7], file=uart)
    if abs(val[0] - val[2]) > abs(val[1] - val[3]):
        mytouch.xyswap = 1
        mytouch.cal_x1 = (val[1] + val[3]) // 2
        mytouch.cal_x2 = (val[5] + val[7]) // 2
        mytouch.cal_y1 = (val[0] + val[4]) // 2
        mytouch.cal_y2 = (val[2] + val[6]) // 2
    else:
        mytouch.xyswap = 0
        mytouch.cal_x1 = (val[0] + val[2]) // 2
        mytouch.cal_x2 = (val[4] + val[6]) // 2
        mytouch.cal_y1 = (val[1] + val[5]) // 2
        mytouch.cal_y2 = (val[3] + val[7]) // 2
    mytouch.xflip = 0
    if mytouch.cal_x1 > mytouch.cal_x2:
        mytouch.xflip = 1
        tmp = mytouch.cal_x1
        mytouch.cal_x1 = mytouch.cal_x2
        mytouch.cal_x2 = tmp
    mytouch.yflip = 0
    if mytouch.cal_y1 > mytouch.cal_y2:
        mytouch.yflip = 1
        tmp = mytouch.cal_y1
        mytouch.cal_y1 = mytouch.cal_y2
        mytouch.cal_y2 = tmp
    mytouch.cal_x2 -= mytouch.cal_x1
    mytouch.cal_y2 -= mytouch.cal_y1
    if mytouch.cal_x1 == 0:
        mytouch.cal_x1 = 1
    if mytouch.cal_x2 == 0:
        mytouch.cal_x2 = 1
    if mytouch.cal_y1 == 0:
        mytouch.cal_y1 = 1
    if mytouch.cal_y2 == 0:
        mytouch.cal_y2 = 1
    mytouch.width = mylcd.lcd_width
    mytouch.height = mylcd.lcd_height
    data = (mytouch.xyswap<<2)|(mytouch.xflip<<1)|mytouch.yflip
    string = "mytouch.Set_Touch_Cal({}, {}, {}, {}, {}, {}, {})\n".format(mytouch.cal_x1, mytouch.cal_y1, mytouch.cal_x2, mytouch.cal_y2, mylcd.lcd_width, mylcd.lcd_height, data)
    print("Use this calibration code in initialization:",file=uart)
    uart.write(string)
    #uart.write("mytouch.Set_Touch_Rotation({})\n".format(mylcd.lcd_rotate))
    mylcd.LCD_Clear(0)
    mylcd.Show_String((mylcd.lcd_width - 176) // 2, (mylcd.lcd_height-16) // 2 - 8, "Calibration complete!", Font_8x16_EN, 0x07E0)
    mylcd.Show_String((mylcd.lcd_width - 296) // 2, (mylcd.lcd_height-16) // 2 + 8, "Calibration code sent to Serial port.", Font_8x16_EN, 0x07E0)
    Delay_Ms(4000)
    mylcd.LCD_Clear(0)
    mylcd.Show_String((mylcd.lcd_width - 168) // 2, (mylcd.lcd_height-16) // 2 - 8, "Touch screen to test!", Font_8x16_EN, 0x07E0)
    while True:
        if mytouch.Read_Touch(coord, 100):
            mylcd.Fill_Circle(coord[0], coord[1], 2, 0x07E0)