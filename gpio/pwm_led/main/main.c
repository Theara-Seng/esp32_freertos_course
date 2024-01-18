#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

void ledc_init(){

    ledc_timer_config_t ledc_timer = {
    .duty_resolution = LEDC_TIMER_10_BIT, // Example: 10-bit resolution
    .freq_hz = 5000,                      // Frequency in Hz
    .speed_mode = LEDC_HIGH_SPEED_MODE,   // Speed mode
    .timer_num = LEDC_TIMER_0             // Timer index
    // .clk_cfg = LEDC_AUTO_CLK              // Optional: Clock configuration
    };
    ledc_timer_config(&ledc_timer);
    // LED 1 Configuration
    ledc_channel_config_t ledc_channel_1 = {
        .channel    = LEDC_CHANNEL_0,
        .duty       = 0,
        .gpio_num   = 2,  // Change to your LED 1 GPIO
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_TIMER_0
    };
    ledc_channel_config(&ledc_channel_1);

    // LED 2 Configuration
    ledc_channel_config_t ledc_channel_2 = {
        .channel    = LEDC_CHANNEL_1,
        .duty       = 0,
        .gpio_num   = 19,  // Change to your LED 2 GPIO
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_TIMER_0
    };
    ledc_channel_config(&ledc_channel_2);

}
void app_main(){
    ledc_init();
    while (true)
    {
        // Example: Set LED 1 to 50% brightness
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 20); // 50% of 1024
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
        vTaskDelay(10/portTICK_PERIOD_MS);
        // Example: Set LED 2 to 75% brightness
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, 768); // 75% of 1024
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
    
}