#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define BUTTON_PIN GPIO_NUM_5
#define ESP_INTR_FLAG_DEFAULT 0

// Queue for interrupt handling
QueueHandle_t gpio_evt_queue = NULL;

// Button interrupt handler task
void button_task(void* arg) {
    int count=0;
    uint32_t io_num;
    for(;;) {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            printf("Button pressed on GPIO %ld for %d time\n", io_num, count++);
        }
    }
}

// GPIO interrupt handler
static void IRAM_ATTR gpio_isr_handler(void* arg) {
    uint32_t gpio_num = (uint32_t) 67;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}
void app_main() {
    // Initialize GPIO pin as input with pull-down resistor
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_NEGEDGE; // Set interrupt on rising edge
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << BUTTON_PIN);
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    // Create a queue to handle GPIO event from ISR
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    // Start button task
    xTaskCreate(button_task, "button_task", 2048, NULL, 10, NULL);

    // Install GPIO ISR service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    
    // Attach the interrupt service routine
    gpio_isr_handler_add(BUTTON_PIN, gpio_isr_handler, (void*) BUTTON_PIN);
}
