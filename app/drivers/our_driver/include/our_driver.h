#ifndef OUR_DRIVER_H_
#define OUR_DRIVER_H_

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

int our_driver_custom_function_get_count(const struct device *dev);
void our_driver_custom_function_set_count(const struct device *dev,
                                          int new_value);

#ifdef __cplusplus
}
#endif

#endif /* OUR_DRIVER_H_ */
