#include "board_io.h"

#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>
#include <errno.h>

LOG_MODULE_REGISTER(board_io, LOG_LEVEL_ERR);


int io_init(void)
{

    if (!gpio_is_ready_dt(&led)) {

        LOG_ERR("Led gpio not ready\n");
        return -errno;
    }

    if (!gpio_is_ready_dt(&button)) {

        LOG_ERR("Button gpio not ready\n");
        return -errno;
    }

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_LOW) < 0) {

        LOG_ERR("Unable to set led pin as output\n");
        return -errno;
    }


    if (gpio_pin_configure_dt(&button, GPIO_INPUT) < 0) {

        LOG_ERR("Unable to set button pin as input\n");
        return -errno;
    }

    return 0;
}

int led_set(bool on)
{
	if (gpio_pin_set_dt(&led, on) < 0) {

		LOG_ERR("Unable to set led pin state\n");
        return -errno;
    }
  return 0;
}

int button_read(void)
{
    int button_state = gpio_pin_get_dt(&button);
	if (button_state < 0) {

	  LOG_ERR("Unable to get button pin state\n");
      return -1;
    }
    return button_state;
}
