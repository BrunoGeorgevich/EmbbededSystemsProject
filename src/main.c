#include <zephyr.h>
#include <misc/printk.h>
#include <board.h>
#include <gpio.h>
#include <device.h>
#include <string.h>
#include <pwm.h>

#include <display/mb_display.h>

#include "uart_driver.h"

static void button_pressed(struct device *dev, struct gpio_callback *cb,
                           u32_t pins)
{
    if (pins & BIT(SW0_GPIO_PIN)) {
        printk("A pressed\n");
    } else {
        printk("B pressed\n");
    }
}

static void configure_buttons(void)
{
    static struct gpio_callback button_cb;
    struct device *gpio;

    gpio = device_get_binding(SW0_GPIO_NAME);

    gpio_pin_configure(gpio, SW0_GPIO_PIN,
                       (GPIO_DIR_IN | GPIO_INT | GPIO_INT_EDGE |
                        GPIO_INT_ACTIVE_LOW));
    gpio_pin_configure(gpio, SW1_GPIO_PIN,
                       (GPIO_DIR_IN | GPIO_INT | GPIO_INT_EDGE |
                        GPIO_INT_ACTIVE_LOW));
    gpio_init_callback(&button_cb, button_pressed,
                       BIT(SW0_GPIO_PIN) | BIT(SW1_GPIO_PIN));
    gpio_add_callback(gpio, &button_cb);

    gpio_pin_enable_callback(gpio, SW0_GPIO_PIN);
    gpio_pin_enable_callback(gpio, SW1_GPIO_PIN);
}

int main() {
    struct mb_display *disp = mb_display_get();
    configure_buttons();
    return 0;
}
