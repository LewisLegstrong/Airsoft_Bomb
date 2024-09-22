#include "ab_pwm.h"

void pwm_task( void *arg ) {
	ledc_timer_config_t ledc_timer = {
		.speed_mode = LEDC_LOW_SPEED_MODE,
		.duty_resolution = LEDC_TIMER_10_BIT,
		.timer_num = LEDC_TIMER_0,
		.freq_hz = PWM_FREQUENCY};
	ledc_timer_config(&ledc_timer);

	ledc_channel_config_t ledc_channel = {
		.channel = LEDC_CHANNEL_0,
		.duty = 0,
		.gpio_num = GPIO_NUM_10,
		.speed_mode = LEDC_LOW_SPEED_MODE,
		.timer_sel = LEDC_TIMER_0};
	ledc_channel_config(&ledc_channel);

	while (1)
	{
		// make a sound for 500ms
		ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
		ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
		vTaskDelay(700 / portTICK_PERIOD_MS);

		ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, PWM_DUTY);
		ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
		vTaskDelay(300 / portTICK_PERIOD_MS);
	}
}

void updatePwm ( uint16_t freqValue ) {
	if (freqValue == 0) {
		ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
		ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
	}
	else {
		ledc_set_freq(LEDC_LOW_SPEED_MODE, LEDC_TIMER_0, freqValue);
		ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
	}
}
