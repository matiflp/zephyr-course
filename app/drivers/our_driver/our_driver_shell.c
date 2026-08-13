#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>

static int shell_subcmd_fetch_handler(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    const struct device *dev = shell_device_get_binding("our_driver");
    if (dev == NULL) {
        shell_print(sh, "Device not found\n");
        return 0;
    }

    struct sensor_value value;
    if (sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &value) < 0) {
        shell_print(sh, "Failed to get ambient temperature\n");
        return 0;
    }

    return 0;
}

static int shell_subcmd_read_handler(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    const struct device *dev = shell_device_get_binding("our_driver");
    if (!dev) {
        shell_print(sh, "No device found\n");
        return 0;
    }

    int ret = sensor_sample_fetch(dev);
    if (ret < 0) {
        shell_print(sh, "Failed to fetch sample: %d\n", ret);
        return 0;
    }

    return 0;
}

static int shell_subcmd_info_handler(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    shell_print(sh, "Version: 1.0\n");
    shell_print(sh, "State: ready\n");

    return 0;
}


SHELL_STATIC_SUBCMD_SET_CREATE(sub_sensor,
    SHELL_CMD(fetch, NULL, "Fetch sensor data", shell_subcmd_fetch_handler),
    SHELL_CMD(read, NULL, "Read sensor data", shell_subcmd_read_handler),
    SHELL_CMD(info, NULL, "Get sensor info", shell_subcmd_info_handler),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_sensor, "Sensor commands", NULL);
