#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/gpio.h"
#define button 5
#define led 2

void button_led(void* pvParameter){
    int last_button  = gpio_get_level(button);
    int led_state = 0;
    while (1){
        int new_button = gpio_get_level(button);
        if (last_button == 1 && new_button == 0){
            led_state = 1-led_state;
            gpio_set_level(led, led_state);
            // vTaskDelay(10/portTICK_PERIOD_MS);
        }
        last_button = new_button;
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}
void app_main(void)
{
    gpio_config_t button_config ={
        .pin_bit_mask = 1ULL<<button,
        .intr_type =GPIO_INTR_NEGEDGE,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE
    };
    gpio_config(&button_config);
    gpio_config_t led_config = {
        .pin_bit_mask = 1ULL<<led,  
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };
    gpio_config(&led_config);

    xTaskCreate(button_led, "button_led", 2048, NULL, 5, NULL);
}
