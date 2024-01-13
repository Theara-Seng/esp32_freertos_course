#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_timer.h"
void function1(){
    for (size_t i=0;i<5;i++){
        printf("Function 1 %d: %lld\n", i, esp_timer_get_time()/1000);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}

void function2(){
    for (size_t i=0;i<5;i++){
        printf("Function 2 %d: %lld\n", i, esp_timer_get_time()/1000);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}
void app_main(void)
{
    printf("\n Starting the program in millisecond : %lld\n\n", esp_timer_get_time()/1000);
    function1();
    printf("\n");
    function2();
    printf("\n Finishing the program: %lld\n", esp_timer_get_time()/1000);
}
