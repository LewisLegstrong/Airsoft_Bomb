#ifndef _AB_UART_H_
#define _AB_UART_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#define UART_NUM UART_NUM_0
// USB to UART pins
#define UART_TX_PIN GPIO_NUM_1
#define UART_RX_PIN GPIO_NUM_3
#define UART_BAUD_RATE 115200

void uart_task(void *arg);

#endif
