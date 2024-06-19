#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"

#include "esp_chip_info.h"
#include "esp_flash.h"

#include "pwm.h"
#include "uart.h"
#include "gpio.h"
#include "timer.h"

void app_main(void) {
	round_timer_t roundTime;
	roundTime.round_time_s = 5;
	xTaskCreate(task_user_time, "task_user_time", 2048, &roundTime, 5, NULL);
	xTaskCreate(task_user_input, "task_user_input", 2048, NULL, 5, NULL);
	xTaskCreate(pwm_task, "pwm_task", 2048, NULL, 5, NULL);
	xTaskCreate(uart_task, "uart_task", 2048, NULL, 5, NULL);
}

