#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
int val = 0;

void app_main() {
    adc2_config_channel_atten(ADC2_CHANNEL_0, ADC_ATTEN_DB_11);

    while (1) {
        adc2_get_raw(ADC2_CHANNEL_0, ADC_WIDTH_BIT_12, &val);
        printf("ADC Value: %d\n", val);
        vTaskDelay(10/ portTICK_PERIOD_MS);
    }
}
        