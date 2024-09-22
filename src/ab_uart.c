#include "ab_uart.h"

void uart_task(void *arg)
{
	uart_config_t uart_config = {
		.baud_rate = UART_BAUD_RATE,
		.data_bits = UART_DATA_8_BITS,
		.parity = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
	uart_param_config(UART_NUM, &uart_config);
	uart_set_pin(UART_NUM, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	uart_driver_install(UART_NUM, 1024, 0, 0, NULL, 0);

	uint8_t data;
	while (1)
	{
		if (uart_read_bytes(UART_NUM, &data, 1, 0) > 0)
		{
			// Process received data
			printf("Received: %c\n", data);
		}
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}
