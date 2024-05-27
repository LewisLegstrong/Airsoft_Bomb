#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_timer.h"

#include "driver/gpio.h"
#include "driver/ledc.h"

#define PWM_FREQUENCY 2000 // PWM signal frequency in Hz
#define PWM_DUTY 50		   // PWM duty cycle in percentage (0-100)

typedef struct  time_param{
	uint32_t round_time_s;
} round_timer_t;

void task_user_input() {
	gpio_config_t io_conf = {};
		io_conf.intr_type = GPIO_INTR_DISABLE;// disable interrupt
		io_conf.mode = GPIO_MODE_INPUT;// set as output mode
		io_conf.pin_bit_mask = (1ULL<<GPIO_NUM_39);// bit mask of the pins that you want to set
		io_conf.pull_down_en = 0;// disable pull-down mode
		io_conf.pull_up_en = 0;// disable pull-up mode
	gpio_config(&io_conf);	// configure GPIO with the given settings
	while(1){
		if (!gpio_get_level(GPIO_NUM_39)){
			printf("Button pressed\n");
		}
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}

void task_user_time(void *roundTime)
{
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

void pwm_task(void *arg){
	ledc_timer_config_t ledc_timer = {
		.speed_mode = LEDC_HIGH_SPEED_MODE,
		.duty_resolution = LEDC_TIMER_10_BIT,
		.timer_num = LEDC_TIMER_0,
		.freq_hz = PWM_FREQUENCY
	};
	ledc_timer_config(&ledc_timer);

	ledc_channel_config_t ledc_channel = {
		.channel = LEDC_CHANNEL_0,
		.duty = 0,
		.gpio_num = GPIO_NUM_27,
		.speed_mode = LEDC_HIGH_SPEED_MODE,
		.timer_sel = LEDC_TIMER_0
	};
	ledc_channel_config(&ledc_channel);

	while(1){
		//make a sound for 500ms
		ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0);
		ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
		vTaskDelay(500 / portTICK_PERIOD_MS);

		ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, PWM_DUTY);
		ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
		vTaskDelay(200 / portTICK_PERIOD_MS);
	}
}

void app_main(void)
{
	round_timer_t roundTime;
	roundTime.round_time_s = 5;
	xTaskCreate(task_user_time, "task_user_time", 2048, &roundTime, 5, NULL);
	xTaskCreate(task_user_input, "task_user_input", 2048, NULL, 5, NULL);
	xTaskCreate(pwm_task, "pwm_task", 2048, NULL, 5, NULL);
}

