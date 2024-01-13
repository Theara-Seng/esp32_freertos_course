#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"


int sharedVariable = 0; // Shared variable
SemaphoreHandle_t xMutex; // Mutex handle
void task1(void *params)
{
    while (1)
    {
        // Attempt to take the mutex. Block for 10 ticks if the mutex is not available
        if (xSemaphoreTake(xMutex, 1000/portTICK_PERIOD_MS))
        {
            sharedVariable++;// Critical section
            printf("Task 1: sharedVariable = %d\n", sharedVariable);
            xSemaphoreGive(xMutex);// Release the mutex
            vTaskDelay(1000 / portTICK_PERIOD_MS);// Delay for demonstration purposes
        }
    }
}

void task2(void *params)
{
    while (1)
    {
        // Attempt to take the mutex. Block for 1000ms if the mutex is not available
        if (xSemaphoreTake(xMutex, 1000/portTICK_PERIOD_MS))
        {
            sharedVariable+=2; // Critical section
            printf("Task 2: sharedVariable = %d\n", sharedVariable);
            xSemaphoreGive(xMutex);// Release the mutex
            vTaskDelay(1000 / portTICK_PERIOD_MS);// Delay for demonstration purposes
        }
    }
}

void app_main(void)
{
    xMutex = xSemaphoreCreateMutex(); // Create the mutex
    if (xMutex != NULL)  // Check if mutex creation was successful
    {
        xTaskCreate(task1, "Task 1", 2048, NULL, 2, NULL);
        xTaskCreate(task2, "Task 2", 2048, NULL, 2, NULL);
    }
}
