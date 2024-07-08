#ifndef _GPIO_H_
#define _GPIO_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "iot_button.h"
#include "esp_timer.h"
#include "esp_log.h"

static const char *TAG = "Airsoft_Bomb: ";

#define MICROSECONDS 1000000
#define BEEP_TIME 3 * MICROSECONDS

void gpioSetup(uint8_t pin, gpio_mode_t mode, gpio_pull_mode_t pull, gpio_int_type_t intr_type);
void createGPIOButton( int32_t gpioPin);
void button_single_click_cb(void *arg, void *usr_data);
void button_long_press_cb(void *arg);

void task_user_input();

#endif
