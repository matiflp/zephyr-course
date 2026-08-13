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

    shell_print(sh, "Version: 1.0");
    shell_print(sh, "State: ready");

    return 0;
}

static int shell_subcmd_set_handler(const struct shell *sh, size_t argc, char **argv)
{
    int err = 0;
    long value;

    if (argc < 2) {
        shell_error(sh, "Missing value. Usage: sensor set <integer>");
        return -EINVAL;
    }

    value = shell_strtol(argv[1], 10, &err);
    if (err != 0) {
        shell_error(sh, "Invalid value '%s': expected an integer", argv[1]);
        return err;
    }

    shell_print(sh, "Value: %ld", value);

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_sensor,
    SHELL_CMD(fetch, NULL, "Fetch sensor data", shell_subcmd_fetch_handler),
    SHELL_CMD(read, NULL, "Read sensor data", shell_subcmd_read_handler),
    SHELL_CMD(info, NULL, "Get sensor info", shell_subcmd_info_handler),
    SHELL_CMD_ARG(set, NULL, "Set sensor data: set <integer>",
                  shell_subcmd_set_handler, 1, 1),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_sensor, "Sensor commands", NULL);
