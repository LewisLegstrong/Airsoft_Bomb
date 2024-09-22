#include "ab_timer.h"

void user_time_task(void * pvParameters) {
	round_timer_t *roundTimer = ( round_timer_t * ) pvParameters;
	uint32_t start_time = esp_timer_get_time( );
	uint32_t end_time = start_time + (roundTimer->round_time_seconds * 1000000);

	printf( "%s - Round started \n", roundTimer->timer_name );
	while (esp_timer_get_time( ) < end_time) {
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
	printf( "%s - Round ended \n", roundTimer->timer_name );
	vTaskDelete( NULL );
	
}
