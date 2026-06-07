#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "esp_timer.h"
#include "lv_demos.h"

static void inc_lvgl_tick(void *arg)
{
    lv_tick_inc(10);
}

void app_main(void)
{
    lv_init();            //init lvgl
    lv_port_disp_init();  //init display
    lv_port_indev_init(); //init touch screen
    /* 为LVGL提供时基单元 */
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &inc_lvgl_tick,
        .name = "lvgl_tick"
    };
    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, 10 * 1000));

    lv_demo_widgets();

    while (1)
    {
	    vTaskDelay(pdMS_TO_TICKS(10));
	    lv_task_handler();
    }
}
