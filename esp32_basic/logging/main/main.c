#include <stdio.h>
#include "esp_log.h"

static const char *TAG = "esp32";

void app_main(void)
{
    ESP_LOGE(TAG, "This is an error message");
    ESP_LOGW(TAG, "This is a warning message");
    ESP_LOGI(TAG, "This is an info message");
    ESP_LOGD(TAG, "This is a debug message");
    ESP_LOGV(TAG, "This is a verbose message");
}
