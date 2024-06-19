#include "pwm.h"

void pwm_task(void *arg) {
	ledc_timer_config_t ledc_timer = {
		.speed_mode = LEDC_HIGH_SPEED_MODE,
		.duty_resolution = LEDC_TIMER_10_BIT,
		.timer_num = LEDC_TIMER_0,
		.freq_hz = PWM_FREQUENCY};
	ledc_timer_config(&ledc_timer);

	ledc_channel_config_t ledc_channel = {
		.channel = LEDC_CHANNEL_0,
		.duty = 0,
		.gpio_num = GPIO_NUM_27,
		.speed_mode = LEDC_HIGH_SPEED_MODE,
		.timer_sel = LEDC_TIMER_0};
	ledc_channel_config(&ledc_channel);

	while (1)
	{
		// make a sound for 500ms
		ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0);
		ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
		vTaskDelay(500 / portTICK_PERIOD_MS);

		ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, PWM_DUTY);
		ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
		vTaskDelay(200 / portTICK_PERIOD_MS);
	}
}
