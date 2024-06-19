#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_timer.h"

#include "driver/gpio.h"

#include "pwm.h"
#include "uart.h"

typedef struct  time_param{
	uint32_t round_time_s;
} round_timer_t;

void task_user_input() {
	gpio_config_t io_conf = {};
		io_conf.intr_type = GPIO_INTR_DISABLE;		// disable interrupt
		io_conf.mode = GPIO_MODE_INPUT;				// set as output mode
		io_conf.pin_bit_mask = (1ULL<<GPIO_NUM_39);	// bit mask of the pins that you want to set
		io_conf.pull_down_en = 0; 					// disable pull-down mode
		io_conf.pull_up_en = 0;						// disable pull-up mode
	gpio_config(&io_conf);							// configure GPIO with the given settings
	while(1){
		if (gpio_get_level(GPIO_NUM_39)){
			printf("Button pressed\n");
		}
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}

void task_user_time(void *roundTime) {
	round_timer_t *params = (round_timer_t *)roundTime;
	uint32_t round_time_s = params->round_time_s;
	uint32_t start_time = esp_timer_get_time();
	uint32_t end_time = start_time + round_time_s * 1000000;

	while (1)
	{
		printf("Round started \n");
		while (esp_timer_get_time() < end_time)
		{
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
		printf("Round ended \n");
		start_time = esp_timer_get_time();
		end_time = start_time + round_time_s * 1000000;
	}
}

void app_main(void) {
	round_timer_t roundTime;
	roundTime.round_time_s = 5;
	xTaskCreate(task_user_time, "task_user_time", 2048, &roundTime, 5, NULL);
	xTaskCreate(task_user_input, "task_user_input", 2048, NULL, 5, NULL);
	xTaskCreate(pwm_task, "pwm_task", 2048, NULL, 5, NULL);
	xTaskCreate(uart_task, "uart_task", 2048, NULL, 5, NULL);
}

