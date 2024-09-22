#ifndef _AB_GPIO_H_
#define _AB_GPIO_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "iot_button.h"
#include "esp_timer.h"
#include "esp_log.h"

#define MICROSECONDS 1000000
#define BEEP_TIME 3 * MICROSECONDS

typedef enum {
	OFF_BTN_STATE = 0,
	LONG_PRESS_BTN_STATE = 1,
	SHORT_PRESS_BTN_STATE = 2,
} ButtonState_t;

void createGPIOButton( int32_t gpioPin, ButtonState_t *buttonState );
void button_single_click_cb( void *arg, void *usr_data );
void button_long_press_cb( void *arg, void *usr_data );

#endif
