#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_timer.h"
#include "freertos/task.h"

void task1(){
    for (size_t i = 0; i<5;i++){
        printf("task1 %d: %lld\n", i, esp_timer_get_time() / 1000);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void task2(){
    for (size_t i = 0; i<5;i++){
        printf("task2 %d: %lld\n", i, esp_timer_get_time() / 1000);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void app_main(void)
{
    printf("\ninitialization: %lld\n", esp_timer_get_time()/1000);
    xTaskCreate(task1, "task1", 2048, NULL, 1, NULL);
    xTaskCreate(task2, "task1", 2048, NULL, 5, NULL);
    printf("\nFinishing program: %lld\n", esp_timer_get_time() / 1000);
}
