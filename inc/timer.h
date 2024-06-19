#ifndef _TIMER_H_
#define _TIMER_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_timer.h"

typedef struct time_param {
	uint32_t round_time_s;
} round_timer_t;

void task_user_time(void *roundTime);

#endif
