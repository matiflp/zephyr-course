#include <zephyr/init.h>
#include <zephyr/sys/printk.h>

static int board_our_board_from_scratch_method_init(void)
{
    printk("Board Initialized\n");
    return 0;
}

SYS_INIT(board_our_board_from_scratch_method_init,
         APPLICATION,
         CONFIG_APPLICATION_INIT_PRIORITY);