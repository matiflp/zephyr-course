#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "our_driver.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

namespace {
	void test ()
	{
	    int count = 0;
		const struct device *driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
		struct sensor_value value;

		if (!device_is_ready(driver)) {
			return;
		}

		// count = our_driver_custom_function_get_count(driver);
		// LOG_INF("count: %d", count);
		// sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &value);
		// k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
		// our_driver_custom_function_set_count(driver, count + 1);
		// sensor_sample_fetch(driver);
		k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
	}
} // namespace

int main (void)
{
	while (1) {
		test();
	}
	return 0;
}
