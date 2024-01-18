#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "example";
#define LED_GPIO 2  
#define BUTTON_GPIO 5 

void button_task(void *pvParameter){
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    gpio_reset_pin(BUTTON_GPIO);
    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_GPIO, GPIO_PULLUP_ONLY);
    
    int led_state = 0;  // LED starts in the off state

    while (1) {
        int button_state = gpio_get_level(BUTTON_GPIO);
        if (button_state == 0) {
            led_state = 1;  // Toggle the LED state
            gpio_set_level(LED_GPIO, led_state);
            ESP_LOGI(TAG, "LED State: %d", led_state);
        }else{
            led_state = 0;
            gpio_set_level(LED_GPIO, led_state);
            ESP_LOGI(TAG, "LED State: %d", led_state);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);  // Delay for 10ms to debounce
    }
}
void app_main() {
    xTaskCreate(button_task, "button_task", 2048, NULL, 5, NULL);
}
