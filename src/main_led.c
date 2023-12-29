#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

// static const struct device *gpio_ct_dev = DEVICE_DT_GET(DT_NODELABEL(gpioc));
// Anstracted away in stm32_min_dev_blue.overlay
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_NODELABEL(blinking_led),gpios);

void main(void)
{
	if(!device_is_ready(led.port)) {
		return;
	}

	int ret;
	// ret = gpio_pin_configure(gpio_ct_dev, 13, GPIO_OUTPUT_ACTIVE);
	// Anstracted away in stm32_min_dev_blue.overlay
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret != 0) {
		return;
	}
	while(true) {
		// ret = gpio_pin_set_raw(gpio_ct_dev, 13, 1);
		// Anstracted away in stm32_min_dev_blue.overlay
		ret = gpio_pin_toggle_dt(&led);
		if (ret !=0) {
			return;
		}
		k_msleep(1000);
	}
}
