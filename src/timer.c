#include "timer.h"

void task_user_time(void * pvParameters) {
	round_timer_t *roundTimer = ( round_timer_t * ) pvParameters;
	uint32_t round_time_s = roundTimer->round_time_s;
	uint32_t start_time = esp_timer_get_time( );
	uint32_t end_time = start_time + round_time_s * 1000000;

	while (1) {
		printf( "Round started \n" );
		while (esp_timer_get_time( ) < end_time) {
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
		printf( "Round ended \n" );
		vTaskDelete( NULL );
	}
}
