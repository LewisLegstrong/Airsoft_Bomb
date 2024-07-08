#ifndef _PWM_H_
#define _PWM_H_

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/ledc.h"
#include "driver/gpio.h"


#define PWM_FREQUENCY 2000 // PWM signal frequency in Hz
#define PWM_DUTY 50		   // PWM duty cycle in percentage (0-100)

void pwm_task(void *arg);
void updatePwm(uint16_t freqValue);

#endif // _PWM_H_
