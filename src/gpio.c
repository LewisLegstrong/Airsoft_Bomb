#include "gpio.h"

void gpioSetup(uint8_t pin, gpio_mode_t mode, gpio_pull_mode_t pull, gpio_int_type_t intr_type) {
	gpio_config_t io_conf = {};

	io_conf.pin_bit_mask = (1ULL << pin);
	io_conf.intr_type = intr_type;		  // disable interrupt
	io_conf.mode = mode;				  // set as output mode

	if (pull == GPIO_PULLDOWN_ONLY) {
		io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE; // disable pull-down mode
		io_conf.pull_up_en = GPIO_PULLUP_DISABLE;	 // disable pull-up mode
	}
	else if (pull == GPIO_PULLUP_ONLY) {
		io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; // disable pull-down mode
		io_conf.pull_up_en = GPIO_PULLUP_ENABLE;	  // disable pull-up mode
	}
	else {
		io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
		io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
	}

	gpio_config(&io_conf);				  // configure GPIO with the given settings
}

void task_user_input(void *pvParameters) {
	int *buttonPressed = (int *)pvParameters;
	volatile uint64_t beepTimeStart = 0;

	while (1)
	{
		if (!gpio_get_level(GPIO_NUM_4)) {
			printf("Button 4 pressed\n");
			beepTimeStart = esp_timer_get_time();
			*buttonPressed = 1;
		}
		if ( !gpio_get_level(GPIO_NUM_3) || (((esp_timer_get_time() - beepTimeStart) >= BEEP_TIME) && *buttonPressed == 1) ) {
			printf("Button 3 pressed\n");
			*buttonPressed = 0;
		}

		vTaskDelay(75 / portTICK_PERIOD_MS);
	}
}
