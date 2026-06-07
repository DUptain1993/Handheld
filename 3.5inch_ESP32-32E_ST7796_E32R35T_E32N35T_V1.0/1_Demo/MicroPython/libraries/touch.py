from machine import Pin
import ustruct
import time

XCMD = 0xD0
YCMD = 0x90
ERRRANGE = 20

SPI_TOUCH_SPEED = 5000000

class XPT2046(object):
    def __init__(self, spi, cs, irq = None, lcd_speed = None):
        self.spi = spi
        self.tp_cs = Pin(cs, Pin.OUT)
        if irq is not None:
            self.tp_irq = Pin(irq, Pin.IN)
        self.tp_cs(1)
        if lcd_speed is not None:
            self.lcd_speed = lcd_speed
        else:
            self.lcd_speed = 0
        self.press_time = 0
        self.cal_x1 = 300
        self.cal_x2 = 3600
        self.cal_y1 = 300
        self.cal_y2 = 4095
        self.width = 320
        self.height = 480
        self.xyswap = 0
        self.xflip = 0
        self.yflip = 0
    def Set_Touch_Speed(self):
        self.tp_cs(0)
        if self.lcd_speed != 0:
            self.spi.init(baudrate=SPI_TOUCH_SPEED)
    def Set_LCD_Speed(self):
        self.tp_cs(1)
        if self.lcd_speed != 0:
            self.spi.init(baudrate=self.lcd_speed)
    def Read_XY_ADC(self):
        self.Set_Touch_Speed()
        self.spi.write(bytearray([XCMD]))
        self.spi.read(2)
        self.spi.write(bytearray([XCMD]))
        self.spi.read(2)
        self.spi.write(bytearray([XCMD]))
        self.spi.read(2)
        self.spi.write(bytearray([XCMD]))
        tmp = self.spi.read(2)
        adc = tmp[0] << 5
        adc |= (0x1F & (tmp[1] >> 3))
        x = adc
        self.spi.write(bytearray([YCMD]))
        self.spi.read(2)
        self.spi.write(bytearray([YCMD]))
        self.spi.read(2)
        self.spi.write(bytearray([YCMD]))
        self.spi.read(2)
        self.spi.write(bytearray([YCMD]))
        tmp = self.spi.read(2)
        adc = tmp[0] << 5
        adc |= 0x1F & (tmp[1] >> 3)
        y = adc
        self.Set_LCD_Speed()
        return x, y
    def Read_Z_Pressure(self):
        tz = 0xFFF
        #buf = bytearray(2)
        self.Set_Touch_Speed()
        self.spi.write(bytearray([0xB0]))
        buf = self.spi.read(2)
        tmp = int.from_bytes(buf, 'big')
        tz += tmp >> 3
        self.spi.write(bytearray([0xC0]))
        buf = self.spi.read(2)
        tmp = int.from_bytes(buf, 'big')
        tz -= tmp >> 3
        self.Set_LCD_Speed()
        if tz == 4095:
            tz = 0
        return tz
    def Touch_Pressed(self, coord, threshold):
        z1 = 1
        z2 = 0
        while z1 > z2:
            z2 = z1
            z1 = self.Read_Z_Pressure()
            time.sleep_ms(1)
        if z1 <= threshold:
            return False
        x1, y1 = self.Read_XY_ADC()
        time.sleep_ms(1)
        if self.Read_Z_Pressure() <= threshold:
            return False
        time.sleep_ms(2)
        x2, y2 = self.Read_XY_ADC()
        if abs(x1 - x2) > ERRRANGE:
            return False
        if abs(y1 - y2) > ERRRANGE:
            return False
        if x1 < 0 and x1 > 4095:
            return False
        if y1 < 0 and y1 > 4095:
            return False
        coord[0] = x1
        coord[1] = y1
        return True
    def Read_Touch(self, coord, threshold):
        tmp = [0xFFFF, 0xFFFF]
        p = 0
        n = 5
        if threshold < 20:
            threshold = 20
        if self.press_time > int(time.time() * 1000):
            threshold = 20
        while n:
            if self.Touch_Pressed(tmp, threshold):
                p += 1
            n -= 1
        if p < 1:
            self.press_time = 0
            return False
        self.press_time = int(time.time() * 1000) + 50
        self.Get_XY_Coordinates(tmp)
        coord[0] = tmp[0]
        coord[1] = tmp[1]
        if coord[0] < 0 and coord[0] > self.width:
            return False
        if coord[1] < 0 and coord[1] > self.height:
            return False
        return True
    def Get_XY_Coordinates(self, coord): 
        if self.xyswap == 0:
            cx = (coord[0] - self.cal_x1) * self.width // self.cal_x2
            cy = (coord[1] - self.cal_y1) * self.height // self.cal_y2
        else:
            cx = (coord[1] - self.cal_x1) * self.width // self.cal_x2
            cy = (coord[0] - self.cal_y1) * self.height // self.cal_y2
        if self.xflip:
            cx = self.width - cx
        if self.yflip:
            cy = self.height - cy
        coord[0] = cx
        coord[1] = cy
    def Set_Touch_Cal(self, x1, y1, x2, y2, w, h, val):
        self.cal_x1 = x1
        self.cal_y1 = y1
        self.cal_x2 = x2
        self.cal_y2 = y2
        self.width = w
        self.height = h
        self.xyswap = (val >> 2) & 0x1
        self.xflip = (val >> 1) & 0x1
        self.yflip = val & 0x1

        
        