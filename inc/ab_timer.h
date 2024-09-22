#ifndef _AB_TIMER_H_
#define _AB_TIMER_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_timer.h"

typedef struct time_param_s {
	char timer_name[16];
	uint32_t round_time_seconds;
} round_timer_t;

void user_time_task(void *roundTime);

#endif
