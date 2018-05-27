#include <zephyr.h>
#include <zephyr/types.h>
#include <misc/printk.h>
#include <misc/util.h>
#include <stddef.h>
#include <board.h>
#include <gpio.h>
#include <device.h>
#include <sensor.h>
#include <string.h>
#include <pwm.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>

#include <display/mb_display.h>

#include "i2c_utils.h"

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

#define ACCELEROMETER_ADDRESS   0x1D
#define ACCELEROMETER_REGISTER  0x0D
#define ACCELEROMETER_TEST      0x5A

#define COMPASS_ADDRESS         0x0e
#define COMPASS_REGISTER        0x07
#define COMPASS_TEST            0xC4

#define REFRESH_TIME 16
#define DEBUG

enum state_t{
    HELLOWORLD,     // Estado 1
    TEMPERATURE,    // Estado 2
    ACCELETOMETER,  // Estado 3
    MAGNETOMETER,   // Estado 4
    BLUETOOTH       // Estado 5
};

struct state {
    union {
        struct states
        {
            enum state_t previous;
            enum state_t current;
            enum state_t next;
        };
        enum state_t s[3];
    };

    void (*run)(void);
};

static struct i2c_dev accelerometer, compass;
static struct device *temperature_sensor;
static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
    BT_DATA_BYTES(BT_DATA_UUID16_ALL, 0xaa, 0xfe),
    BT_DATA_BYTES(BT_DATA_SVC_DATA16,
                  0xaa, 0xfe, /* Eddystone UUID */
                  0x10, /* Eddystone-URL frame type */
                  0x00, /* Calibrated Tx power at 0m */
                  0x00, /* URL Scheme Prefix http://www. */
                  'z', 'e', 'p', 'h', 'y', 'r',
                  'p', 'r', 'o', 'j', 'e', 'c', 't',
                  0x08) /* .org */
};
static const struct bt_data sd[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};


static void bt_ready(int err)
{
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return;
    }

    printk("Bluetooth initialized\n");

    /* Start advertising */
    err = bt_le_adv_start(BT_LE_ADV_NCONN, ad, ARRAY_SIZE(ad),
                          sd, ARRAY_SIZE(sd));
    if (err) {
        printk("Advertising failed to start (err %d)\n", err);
        return;
    }

    printk("Beacon started\n");
}

static int translate_pos_accelerometer(int val) {
    if(val >= 0 && val <= 51) {
        return 4;
    }
    if(val >= 52 && val <= 103) {
        return 3;
    }
    if(val >= 104 && val <= 155) {
        return 2;
    }
    if(val >= 156 && val <= 207) {
        return 1;
    }
    if(val >= 208 && val <= 255) {
        return 0;
    }
    else {
#ifdef DEBUG
        printk("MAJOR THAN 255 OR MINOR THAN 0 -> %d\n", val);
#endif
        return -1;
    }
}

static void accelerometer_display(int x, int y) {

    struct mb_image __dot = MB_IMAGE(
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 });

    __dot.row[translate_pos_accelerometer(y)] = (1 << translate_pos_accelerometer(x));

    struct mb_display *disp = mb_display_get();
    mb_display_image(disp, MB_DISPLAY_MODE_SINGLE,
                     K_MSEC(REFRESH_TIME), &__dot, 1);
    k_sleep(K_MSEC(REFRESH_TIME));
}

static void compass_display() {

    struct mb_display *disp = mb_display_get();

    char *str = "T";

    mb_display_print(disp, MB_DISPLAY_MODE_SINGLE, K_SECONDS(1), str);
    k_sleep(K_SECONDS(1)*strlen(str));
}

static void bluetooth_showcase() {
    int err;

    printk("Starting Beacon Demo\n");

    /* Initialize the Bluetooth Subsystem */
    err = bt_enable(bt_ready);
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
    }
}

static void temperature_showcase() {

    printk("temp device is %p, name is %s\n",
           temperature_sensor, temperature_sensor->config->name);
    struct mb_display *disp = mb_display_get();

    int r;
    struct sensor_value temp_value;

    r = sensor_sample_fetch(temperature_sensor);
    if (r) {
        printk("sensor_sample_fetch failed return: %d\n", r);
        return;
    }

    r = sensor_channel_get(temperature_sensor, SENSOR_CHAN_TEMP,
                           &temp_value);
    if (r) {
        printk("sensor_channel_get failed return: %d\n", r);
        return;
    }


    u32_t temperature_value = (u32_t)sensor_value_to_double(&temp_value);

    mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP,
                     K_MSEC(500), "%dC\n", temperature_value);
    printk("Temperature is %d °C\n", temperature_value);

    k_sleep(1800);
}

static void accelerometer_showcase() {
    uint8_t data_msb[1];
    uint8_t data_lsb[1];

    uint16_t x,y,z;
    //X_LSB = 0x2 | Y_LSB = 0x4 | Z_LSB = 0x6
    i2c_util_read_bytes(&accelerometer, 0x1, data_msb, sizeof(data_msb));
    i2c_util_read_bytes(&accelerometer, 0x2, data_lsb, sizeof(data_lsb));

    data_lsb[0] = (data_msb[0] << 2) | (data_lsb[0] >> 6);
    x = data_lsb[0];

#ifdef DEBUG
    printk("ACC X: %d\n", x);
#endif

    i2c_util_read_bytes(&accelerometer, 0x3, data_msb, sizeof(data_msb));
    i2c_util_read_bytes(&accelerometer, 0x4, data_lsb, sizeof(data_lsb));

    data_lsb[0] = (data_msb[0] << 2) | (data_lsb[0] >> 6);
    y = data_lsb[0];

#ifdef DEBUG
    printk("ACC Y: %d\n", y);
#endif

    i2c_util_read_bytes(&accelerometer, 0x5, data_msb, sizeof(data_msb));
    i2c_util_read_bytes(&accelerometer, 0x6, data_lsb, sizeof(data_lsb));

    data_lsb[0] = (data_msb[0] << 2) | (data_lsb[0] >> 6);
    z = data_lsb[0];

#ifdef DEBUG
    printk("ACC Z: %d\n", z);
    printk("------------------------------------\n", z);
#endif

    accelerometer_display(x,y);
    k_sleep(REFRESH_TIME);
}

static void compass_showcase() {
    int8_t data_msb[1];
    int8_t data_lsb[1];

    int16_t x,y,z;
    //X_LSB = 0x2 | Y_LSB = 0x4 | Z_LSB = 0x6
    i2c_util_read_bytes(&compass, 0x1, data_msb, sizeof(data_msb));
    i2c_util_read_bytes(&compass, 0x2, data_lsb, sizeof(data_lsb));

    x = data_msb[0] << 8 | data_lsb[0];

#ifdef DEBUG
    printk("COMPASS X: %d\n", x);
#endif

    i2c_util_read_bytes(&compass, 0x3, data_msb, sizeof(data_msb));
    i2c_util_read_bytes(&compass, 0x4, data_lsb, sizeof(data_lsb));

    y = data_msb[0] << 8 | data_lsb[0];

#ifdef DEBUG
    printk("COMPASS Y: %d\n", y);
#endif

    i2c_util_read_bytes(&compass, 0x5, data_msb, sizeof(data_msb));
    i2c_util_read_bytes(&compass, 0x6, data_lsb, sizeof(data_lsb));

    z = data_msb[0] << 8 | data_lsb[0];

#ifdef DEBUG
    printk("COMPASS Z: %d\n", z);
    printk("------------------------------------\n", z);
#endif

    compass_display();
}

static void hello_world() {
    struct mb_display *disp = mb_display_get();

    char *str = "ECOM042.2017.2";

    mb_display_print(disp, MB_DISPLAY_MODE_SINGLE, K_SECONDS(1), str);
    k_sleep(K_SECONDS(1)*strlen(str));
}


static struct state states[5] = {
{BLUETOOTH, HELLOWORLD, TEMPERATURE,        hello_world},
{HELLOWORLD, TEMPERATURE, ACCELETOMETER,    temperature_showcase},
{TEMPERATURE, ACCELETOMETER, MAGNETOMETER,  accelerometer_showcase},
{ACCELETOMETER, MAGNETOMETER, BLUETOOTH,    compass_showcase},
{MAGNETOMETER, BLUETOOTH, HELLOWORLD,       bluetooth_showcase},
};

static enum state_t current_state_t;
static struct state *current_state;


static void button_pressed(struct device *dev, struct gpio_callback *cb,
                           u32_t pins)
{
    if (pins & BIT(SW0_GPIO_PIN)) {
#ifdef DEBUG
        printk("A pressed\n");
#endif
        if(current_state_t == BLUETOOTH) {
            current_state_t = HELLOWORLD;
        } else {
            current_state_t += 1;
        }
    } else {
#ifdef DEBUG
        printk("B pressed\n");
#endif
        if(current_state_t == HELLOWORLD) {
            current_state_t = BLUETOOTH;
        } else {
            current_state_t -= 1;
        }
    }

    current_state = &states[current_state_t];
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

    current_state_t = HELLOWORLD;
    current_state = &states[current_state_t];

    configure_buttons();

    i2c_util_dev_init(&accelerometer, ACCELEROMETER_ADDRESS, "ACC", ACCELEROMETER_REGISTER,
                      ACCELEROMETER_TEST);
    i2c_util_dev_init(&compass, COMPASS_ADDRESS, "COMPASS", COMPASS_REGISTER, COMPASS_TEST);

    u8_t bit_activator = 1;
    i2c_util_write_bytes(&accelerometer, 0x2A, &bit_activator, sizeof(u8_t));
    i2c_util_write_bytes(&compass, 0x10, &bit_activator, sizeof(u8_t));


    printk("Thermometer Example! %s\n", CONFIG_ARCH);

    temperature_sensor = device_get_binding("TEMP_0");
    if (!temperature_sensor) {
        printf("error: no temp device\n");
        return;
    }

    while (1) {
        current_state->run();
    }

    return 0;
}
