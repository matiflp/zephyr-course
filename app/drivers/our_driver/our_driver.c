#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#include "our_driver.h"

#define DT_DRV_COMPAT our_driver

#define LED_NODE DT_ALIAS(app_led)

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

struct our_driver_data {
    int count;
};

static int our_driver_channel_get_impl (const struct device *dev, enum sensor_channel channel,
                                        struct sensor_value *val)
{
	LOG_INF("Hello from channel get implementation, channel: %d", channel);

	if (gpio_pin_set_dt(&led, 1) < 0)
		return 0;

	LOG_INF("Led Turned On");

	return 0;
}

static int our_driver_sample_fetch_impl (const struct device *dev, enum sensor_channel channel)
{
	LOG_INF("Hello from sample fetch implementation, channel: %d", channel);

	if (gpio_pin_set_dt(&led, 0) < 0)
		return 0;

	LOG_INF("Led Turned Off");

	return 0;
}

int our_driver_custom_function_get_count (const struct device *dev)
{
	LOG_INF("Hello from custom function get count implementation");

	const struct our_driver_data *data = dev->data;

	return data->count;
}

void our_driver_custom_function_set_count (const struct device *dev, const int newValue)
{
	LOG_INF("Hello from custom function set count implementation, newValue: %d", newValue);

	struct our_driver_data *data = dev->data;
	data->count = newValue;
}

static int init (const struct device *dev)
{
	if (!gpio_is_ready_dt(&led))
		return 0;

	if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0)
		return 0;

	LOG_INF("Device Initialized!");

	return 0;
}

static struct our_driver_data our_driver_data = {
	.count = 0
};

static DEVICE_API(sensor, our_driver_api) = {.channel_get  = our_driver_channel_get_impl,
                                             .sample_fetch = our_driver_sample_fetch_impl};

DEVICE_DT_INST_DEFINE(0, init, NULL, &our_driver_data, NULL, POST_KERNEL, 80, &our_driver_api);
