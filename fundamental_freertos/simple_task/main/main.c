#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_timer.h"
#include "freertos/task.h"

void myTask(){
    for (size_t i = 0; i<5;i++){
        printf("myTask %d: %lld\n", i, esp_timer_get_time() / 1000);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void app_main(void)
{
    printf("\ninitialization: %lld\n", esp_timer_get_time()/1000);
    xTaskCreate(myTask, "MyTask", 2048, NULL, 5, NULL);
    printf("\nFinishing program: %lld\n", esp_timer_get_time() / 1000);
}
