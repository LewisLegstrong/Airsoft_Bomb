#include "gpio.h"

void gpioSetup(uint8_t pin, gpio_mode_t mode, gpio_pull_mode_t pull, gpio_int_type_t intr_type)
{
	gpio_config_t io_conf = {};
	io_conf.intr_type = intr_type;		  // disable interrupt
	io_conf.mode = mode;				  // set as output mode
	io_conf.pin_bit_mask = (1ULL << pin); // bit mask of the pins that you want to set
	io_conf.pull_down_en = pull;		  // disable pull-down mode
	io_conf.pull_up_en = pull;			  // disable pull-up mode
	gpio_config(&io_conf);				  // configure GPIO with the given settings
}

void task_user_input()
{
	gpioSetup(GPIO_NUM_39, GPIO_MODE_INPUT, GPIO_PULLUP_ONLY, GPIO_INTR_POSEDGE);
	while (1)
	{
		if (gpio_get_level(GPIO_NUM_39))
		{
			printf("Button pressed\n");
		}
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}
