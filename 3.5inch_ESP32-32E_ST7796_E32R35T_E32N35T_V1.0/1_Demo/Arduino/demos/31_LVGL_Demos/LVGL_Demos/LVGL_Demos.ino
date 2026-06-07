//This example is a demonstration of LVGL

//pin usage as follow:
//                   CS  DC/RS  RESET    SDI/MOSI  SCK   SDO/MISO  BL  TOUCH_CS   VCC   GND    
//ESP32-WROOM-32E:   15    2   ESP32-EN     13      14      12     27     33      5V    GND 

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
#include <lvgl.h>
#include <demos/lv_demos.h>
#include <examples/lv_examples.h>
#include <TFT_eSPI.h> 

static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;
static lv_disp_draw_buf_t disp_buf;
static lv_color_t buf[screenWidth*20];

TFT_eSPI my_lcd = TFT_eSPI();

#if USE_LV_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    my_lcd.setAddrWindow(area->x1, area->y1,  w, h);
    my_lcd.pushColors((uint16_t *)&color_p->full, w*h, true);
    lv_disp_flush_ready(disp);
}

/* Reading input device (simulated encoder here) */
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    uint16_t touchX, touchY;

    bool touched = my_lcd.getTouch( &touchX, &touchY, 600 );

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;

       // Serial.print( "Data x " );
       // Serial.println( touchX );

       // Serial.print( "Data y " );
       // Serial.println( touchY );
    }
}

void setup()
{
    Serial.begin(115200); /* prepare for possible serial debug */
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
    my_lcd.init();
    my_lcd.fillScreen(0xFFFF);
    my_lcd.setRotation(1); 
    uint16_t calData[5] = { 245, 3664, 259, 3471, 7 };
    my_lcd.setTouch(calData);
 
    lv_init();
    delay(10);

#if USE_LV_LOG != 0
    lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

    lv_disp_draw_buf_init(&disp_buf, buf, NULL, screenWidth*20);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = my_lcd.width();
    disp_drv.ver_res = my_lcd.height();
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    // uncomment one of these demos
     lv_demo_widgets();           
    // lv_demo_benchmark();        
    // lv_demo_keypad_encoder();    
    // lv_demo_music();             
    // lv_demo_stress();             
}


void loop()
{
    lv_task_handler(); /* let the GUI do its work */
    delay(5);
}
