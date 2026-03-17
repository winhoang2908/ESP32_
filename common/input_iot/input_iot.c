#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "input_iot.h"

static input_callback_t input_callback = NULL;

/* ISR handler */
static void IRAM_ATTR gpio_input_handler(void *arg)
{
    //chuyển đổi tham số arg thành gpio_num_t để xác định chân GPIO co the sai
    gpio_num_t gpio_num = (gpio_num_t)(uint32_t)arg;

    if (input_callback != NULL) {
        //Gọi hàm callback đã đăng ký, truyền vào
        input_callback(gpio_num);
    }
}

/* Create input GPIO with interrupt */
void input_io_create(gpio_num_t gpio_num, interrupt_type_edge_t type_interrupt)
{
    //cấu hình chân GPIO là input
    gpio_set_direction(gpio_num, GPIO_MODE_INPUT);
    
    //cấu hình chế độ pull-up cho chân GPIO, 
    //giúp đảm bảo tín hiệu ổn định khi không có tín hiệu đầu vào
    gpio_set_pull_mode(gpio_num, GPIO_PULLUP_ONLY);

    //cấu hình loại ngắt cho chân GPIO, 
    //có thể là ngắt khi tín hiệu chuyển từ thấp lên cao (LO_TO_HI),
    // từ cao xuống thấp (HI_TO_LO) hoặc bất kỳ sự thay đổi nào (ANY_EDGE)
    gpio_set_intr_type(gpio_num, type_interrupt);

 //tao 1 task de xu ly ngat, neu khong co task thi khi co ngat se khong xu ly duoc
    gpio_install_isr_service(0);

//dang ky ham xu ly ngat cho GPIO, 
//khi co ngat xay ra thi ham gpio_input_handler se duoc goi de xu ly ngat
    gpio_isr_handler_add(gpio_num, gpio_input_handler, (void*) gpio_num);
}

/* Get level of input */
int input_io_get_level(gpio_num_t gpio_num)
{
    return gpio_get_level(gpio_num);
}

/* Register callback */
void input_set_callback(input_callback_t cb)
{
    input_callback = cb;
}