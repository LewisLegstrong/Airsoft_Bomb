idf_component_register(SRCS
	"main.c"
	"../src/ab_gpio.c"
	"../src/ab_uart.c"
	"../src/ab_pwm.c"
	"../src/ab_timer.c"
	"../src/ab_menus.c"
	"../managed_components/HD44780/HD44780.c"

	INCLUDE_DIRS "../inc/"
	"../managed_components/HD44780/include"
	)

