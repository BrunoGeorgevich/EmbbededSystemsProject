#include "configure.h"

struct state state_machine[4] = {
{MAGNETOMETER  , HELLOWORLD    , TEMPERATURE   ,    helloworld_showcase},
{HELLOWORLD    , TEMPERATURE   , ACCELETOMETER ,    temperature_showcase},
{TEMPERATURE   , ACCELETOMETER , MAGNETOMETER  ,    accelerometer_showcase},
{ACCELETOMETER , MAGNETOMETER  , HELLOWORLD    ,    compass_showcase},
};

void button_pressed(struct device *dev, struct gpio_callback *cb, u32_t pins)
{
    if (pins & BIT(SW0_GPIO_PIN)) {
#ifdef DEBUG
        printk("A pressed\n");
#endif
        if (k_uptime_delta(&a_timestamp) < K_MSEC(100)) {
#ifdef DEBUG
            printk("Too quick A presses\n");
#endif
            return;
        }
    } else {
#ifdef DEBUG
        printk("B pressed\n");
#endif
        if (k_uptime_delta(&b_timestamp) < K_MSEC(100)) {
#ifdef DEBUG
            printk("Too quick B presses\n");
#endif
            return;
        }
    }

    if (pins & BIT(SW0_GPIO_PIN)) {
        current_state_t = current_state->s[0];
    } else {
        current_state_t = current_state->s[2];
    }

    current_state = &state_machine[current_state_t];
}

void configure_buttons()
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

void init_sensors()
{
    init_accelerometer();
    init_compass();
    init_temperature_sensor();
}

void init_state_machine() {
    current_state_t = HELLOWORLD;
    current_state = &state_machine[current_state_t];
}
