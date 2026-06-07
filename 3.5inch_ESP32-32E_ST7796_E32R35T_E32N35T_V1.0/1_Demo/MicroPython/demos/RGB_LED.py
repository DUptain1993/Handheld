from machine import Pin,PWM
import time

RED_PIN = 22
GREEN_PIN = 16
BLUE_PIN = 17

LED_ON = 0
LED_OFF = 1

FREQ = 1000
PWM_LED = 22

if __name__=='__main__':
    red = Pin(RED_PIN,Pin.OUT,value = LED_OFF)
    green = Pin(GREEN_PIN,Pin.OUT,value = LED_OFF)
    blue = Pin(BLUE_PIN,Pin.OUT,value = LED_OFF)
    time.sleep_ms(1000)
    red(LED_ON)
    green(LED_ON)
    blue(LED_ON)
    time.sleep_ms(2000)
    while True:
        red(LED_ON)
        green(LED_OFF)
        blue(LED_OFF)
        time.sleep_ms(1500)
        for i in range(6):
            red(LED_OFF)
            time.sleep_ms(500)
            red(LED_ON)
            time.sleep_ms(500)
        red(LED_OFF)
        green(LED_ON)
        blue(LED_OFF)
        time.sleep_ms(1500)
        for i in range(6):
            green(LED_OFF)
            time.sleep_ms(500)
            green(LED_ON)
            time.sleep_ms(500)
        red(LED_OFF)
        green(LED_OFF)
        blue(LED_ON)
        time.sleep_ms(1500)
        for i in range(6):
            blue(LED_OFF)
            time.sleep_ms(500)
            blue(LED_ON)
            time.sleep_ms(500)
        red(LED_OFF)
        green(LED_OFF)
        blue(LED_OFF)
        pwm = PWM(Pin(PWM_LED),freq = FREQ)
        for i in range(1023,0,-5):
            pwm.duty(i)
            time.sleep_ms(20)
        for i in range(0,1024,5):
            pwm.duty(i)
            time.sleep_ms(20)
        time.sleep_ms(500)
        pwm.deinit()
        red = Pin(RED_PIN,Pin.OUT,value = LED_OFF)