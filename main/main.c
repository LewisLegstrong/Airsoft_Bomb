#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h" // Include if using esp_timer for run-time stats
#include "esp_chip_info.h"
#include "esp_flash.h"

#include "ab_pwm.h"
#include "ab_uart.h"
#include "ab_gpio.h"
#include "ab_timer.h"

// LCD Test functions
#include <driver/i2c.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include "sdkconfig.h"
#include "HD44780.h"

#define LCD_ADDR 0x27
#define SDA_PIN  21
#define SCL_PIN  22
#define LCD_COLS 16
#define LCD_ROWS 2

void LCD_DemoTask(void* param)
{
    char num[20];
    while (true) {
        LCD_home();
        LCD_clearScreen();
        LCD_writeStr("16x2 I2C LCD");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        LCD_clearScreen();
        LCD_writeStr("Lets Count 0-10!");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        LCD_clearScreen();
        for (int i = 0; i <= 10; i++) {
            LCD_setCursor(8, 2);
            sprintf(num, "%d", i);
            LCD_writeStr(num);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
  
    }
}


void app_main(void) {
	// uint8_t button_state[4] = {0};
	ButtonState_t buttonA = OFF_BTN_STATE;
	ButtonState_t buttonB = OFF_BTN_STATE;

	round_timer_t gameTimer = { 
		.timer_name = "game_time",
		.round_time_seconds = 10
	};
	round_timer_t userTimer = { 
		.timer_name = "user_time",
		.round_time_seconds = 5 };

	createGPIOButton(GPIO_NUM_4, &buttonA);
	createGPIOButton(GPIO_NUM_3, &buttonB);

	LCD_init(LCD_ADDR, SDA_PIN, SCL_PIN, LCD_COLS, LCD_ROWS);
    xTaskCreate(&LCD_DemoTask, "Demo Task", 2048, NULL, 5, NULL);

	xTaskCreate(pwm_task, "task_user_time", 2048, NULL, 2, NULL);

	xTaskCreate(user_time_task, "task_game_time", 2048, &gameTimer, 5, NULL);
	uint32_t start_time = esp_timer_get_time();
	while ((esp_timer_get_time() - start_time) < 5000000 ) {
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}

	xTaskCreate(user_time_task, "task_user_time", 2048, &userTimer, 3, NULL);
	
	while (1) {
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}
