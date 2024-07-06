#ifndef _GPIO_H_
#define _GPIO_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "esp_timer.h"

#define MICROSECONDS 1000000
#define BEEP_TIME 3 * MICROSECONDS

void gpioSetup (uint8_t pin, gpio_mode_t mode, gpio_pull_mode_t pull, gpio_int_type_t intr_type);

void task_user_input();

#endif
