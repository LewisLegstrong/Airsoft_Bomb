#include "timer.h"

void task_user_time(void *roundTime) {
	round_timer_t *params = (round_timer_t *)roundTime;
	uint32_t round_time_s = params->round_time_s;
	uint32_t start_time = esp_timer_get_time();
	uint32_t end_time = start_time + round_time_s * 1000000;

	while (1) {
		printf("Round started \n");
		while (esp_timer_get_time() < end_time) {
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
		printf("Round ended \n");
		start_time = esp_timer_get_time();
		end_time = start_time + round_time_s * 1000000;
	}
}
