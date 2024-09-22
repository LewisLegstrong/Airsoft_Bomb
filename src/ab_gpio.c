#include "ab_gpio.h"
#include "ab_pwm.h"


#define LEFT_BUTTON GPIO_NUM_3
#define RIGHT_BUTTON GPIO_NUM_4

static const char *TAG = "GPIO: ";

void createGPIOButton( int32_t gpioPin, ButtonState_t *buttonState  ) {	// create gpio button
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
	iot_button_register_cb(gpio_btn, BUTTON_LONG_PRESS_START, button_long_press_cb, buttonState);
	// Register a callback for single click
	iot_button_register_cb(gpio_btn, BUTTON_SINGLE_CLICK, button_single_click_cb, buttonState);
}

// Callback for a long press
void button_long_press_cb(void *arg, void *usr_data) {
	ESP_LOGI(TAG, "LONG PRESS CALLBACK CALLED");
	*((ButtonState_t*)usr_data) = LONG_PRESS_BTN_STATE;
	ESP_LOGI(TAG, "usr_data value is %d", *((ButtonState_t*)usr_data));
}


// Callback for a single click
void button_single_click_cb(void *arg, void *usr_data) {
	ESP_LOGI(TAG, "SHORT PRESS CALLBACK CALLED");
	*((ButtonState_t*)usr_data) = SHORT_PRESS_BTN_STATE;
	ESP_LOGI(TAG, "usr_data value is %d", *((ButtonState_t*)usr_data));
}
