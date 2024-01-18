#include <stdio.h>
#include "driver/gpio.h"
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <esp_timer.h>
#define LED_GPIO_PIN GPIO_NUM_2 

void app_main() {

	gpio_set_direction(LED_GPIO_PIN, GPIO_MODE_OUTPUT);
	while (1) {

		gpio_set_level(LED_GPIO_PIN, 1);//Turn the LED on
		vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for a second

		gpio_set_level(LED_GPIO_PIN, 0);//Turn the LED off
		vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for a second
	}

}