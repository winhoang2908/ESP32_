#ifndef INPUT_IO_H
#define INPUT_IO_H
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"


typedef enum{
    LO_TO_HI = 1,
    HI_TO_LO = 2,
    ANY_EDGE = 3
} interrupt_type_edge_t;


typedef void (*input_callback_t) (int);

void input_io_create(gpio_num_t gpio_num, interrupt_type_edge_t type_interrupt);
int input_io_get_level(gpio_num_t gpio_num);
void input_set_callback(input_callback_t cb);

#endif /* INPUT_IO_H */
