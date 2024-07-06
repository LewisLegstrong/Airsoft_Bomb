#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"

#include "esp_chip_info.h"
#include "esp_flash.h"

#include "pwm.h"
#include "uart.h"
#include "gpio.h"
#include "timer.h"

void app_main(void) {
	//Setup, starting GPIO and Timers alike
	// gpioSetup(GPIO_NUM_13, GPIO_MODE_INPUT, GPIO_PULLDOWN_ONLY, GPIO_INTR_DISABLE)
	int isButPressed = 0;
	TaskHandle_t x_pwmHandle = NULL;
	gpioSetup(GPIO_NUM_4, GPIO_MODE_INPUT, GPIO_PULLUP_ONLY, GPIO_INTR_DISABLE);
	gpioSetup(GPIO_NUM_3, GPIO_MODE_INPUT, GPIO_PULLUP_ONLY, GPIO_INTR_DISABLE);

	xTaskCreate(task_user_input, "gpio_task", 2048, &isButPressed, 10, NULL);

	// xTaskCreate(task_user_input, "task_user_input", 2048, NULL, 10, NULL);
	while (1){
		if (isButPressed && x_pwmHandle == NULL){
			xTaskCreate(pwm_task, "pwm_task", 2048, NULL, 10, &x_pwmHandle);
		}
		if (!isButPressed && x_pwmHandle != NULL){
			vTaskDelete(x_pwmHandle);
			x_pwmHandle = NULL;
		}
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}
