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

	while (1) {
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

void createGPIOButton( int32_t gpioPin ) {	// create gpio button
	button_config_t gpio_btn_cfg = {
		.type = BUTTON_TYPE_GPIO,
		.long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS,
		.short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS,
		.gpio_button_config = {
			.gpio_num = gpioPin,
			.active_level = 0,
		},
	};

	button_handle_t gpio_btn = iot_button_create(&gpio_btn_cfg);
	if (NULL == gpio_btn) {
		ESP_LOGE(TAG, "Button create failed");
	}

	// Register a callback for long press
	iot_button_register_cb(gpio_btn, BUTTON_LONG_PRESS_START, button_long_press_cb, NULL);

	// Register a callback for single click
	iot_button_register_cb(gpio_btn, BUTTON_SINGLE_CLICK, button_single_click_cb, NULL);
}

// Callback for a long press
void button_long_press_cb(void *arg) {
	ESP_LOGI(TAG, "Button long pressed");
}

// Callback for a single click
void button_single_click_cb(void *arg, void *usr_data) {
	ESP_LOGI(TAG, "BUTTON_SINGLE_CLICK");
}
