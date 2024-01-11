#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define GPIO_OUTPUT_IO_2    2 // GPIO 2

void app_main(void)
{
  char c = 0;
  char str[100];
  int str_len = 0;
  memset(str, 0, sizeof(str));

  gpio_set_direction(GPIO_OUTPUT_IO_2, GPIO_MODE_OUTPUT);

  while (c != '\n')
  {
    c = getchar();
    if (c != 0xff)
    {
      str[str_len++] = c;
      printf("%c", c);
    }
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
  
  str_len = str_len - 1;

  printf("you typed: %d\n", str_len);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    if (strncmp(str, "set2high", strlen("set2high")) == 0)
    {
        // Set GPIO 2 to high
        gpio_set_level(GPIO_OUTPUT_IO_2, 1);
        printf("GPIO 2 set to HIGH\n");
    }
}
