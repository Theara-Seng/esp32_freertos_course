#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
void ledc_init(){

    ledc_timer_config_t ledc_timer = {
    .duty_resolution = LEDC_TIMER_10_BIT, 
    .freq_hz = 5000,                     
    .speed_mode = LEDC_HIGH_SPEED_MODE,   
    .timer_num = LEDC_TIMER_0             
    };
    ledc_timer_config(&ledc_timer);
      
    ledc_channel_config_t ledc_channel_1 = {
        .channel    = LEDC_CHANNEL_0,
        .duty       = 0,
        .gpio_num   = 2,  
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_TIMER_0
    };
    ledc_channel_config(&ledc_channel_1);


}
void app_main(){
    ledc_fade_func_install(0);

    ledc_init();
    int target_duty1 = 10;
    int fade_time1 = 2000;
    int target_duty2 = 1000;
    int fade_time2 = 2000;
    while (true)
    {
        ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, target_duty1, fade_time1);
        ledc_fade_start(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, LEDC_FADE_NO_WAIT);
        vTaskDelay(10/portTICK_PERIOD_MS);
        
        ledc_set_fade_with_time(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, target_duty2, fade_time2);
        ledc_fade_start(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, LEDC_FADE_NO_WAIT);
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
    
}