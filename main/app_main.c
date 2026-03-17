/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
//hello cả nhà yêu dấu
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"
#include "input_iot.h"
//định nghĩa chân GPIO được sử dụng cho LED 2
#define BLINK_GPIO CONFIG_BLINK_GPIO

void input_event_callback(gpio_num_t pin)
{
    if(pin == GPIO_NUM_0) {
      static int x = 0;
      //đặt mức logic của chân GPIO được chỉ định bởi BLINK_GPIO 2
      gpio_set_level(BLINK_GPIO, x);   
      x = !x;
    }
}

void app_main(void)
{
    //tạo sườn cho nút GPIO_NUM 0 
    input_io_create(GPIO_NUM_0, HI_TO_LO);
    input_set_callback(input_event_callback);
     
    while (1) {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
}
