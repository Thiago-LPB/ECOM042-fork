/*******************************************************************
 * @file main.c
 *
 * @brief Main file.
 * @author João Matheus Nascimento Dias (jmnd@ic.ufal.br)
 * @author José Félix de Oliveira Neto (jfon@ic.ufal.br)
 * @version 0.1
 * @date 26/08/2026
 *******************************************************************/

#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio/gpio_emul.h>
#include <errno.h>

#include "board_io.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_ERR);


int main(void)
{

	if (io_init() < 0) {

		LOG_ERR("Error running io_init\n");
		return -errno;
	}

	for (int i = 0; i < 4; i++) {
		int button_value = button_read();
	    int led_value = gpio_emul_output_get_dt(&led);

        printk("Button: %d -> LED: %d\n", button_value, led_value);
        gpio_emul_input_set(button.port, button.pin, !button_value);
        k_msleep(200);
        led_set(button_read());
    }
	return 0;
}
