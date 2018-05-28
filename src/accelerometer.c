#include "accelerometer.h"

int translate_pos_accelerometer(int val) {
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

void accelerometer_display(int x, int y) {

    struct mb_image __dot = MB_IMAGE(
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 });

    __dot.row[translate_pos_accelerometer(y)] = (1 << translate_pos_accelerometer(x));

    struct mb_display *disp = mb_display_get();
    mb_display_image(disp, MB_DISPLAY_MODE_SINGLE,
                     K_MSEC(REFRESH_TIME_ACCELEROMETER), &__dot, 1);
    k_sleep(K_MSEC(REFRESH_TIME_ACCELEROMETER));
}

void accelerometer_showcase() {
    uint8_t data_msb[1];
    uint8_t data_lsb[1];

    uint16_t x,y,z;
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
    k_sleep(K_MSEC(REFRESH_TIME_ACCELEROMETER));
}

void init_accelerometer() {
    i2c_util_dev_init(&accelerometer, ACCELEROMETER_ADDRESS, "ACC", ACCELEROMETER_REGISTER,
                      ACCELEROMETER_TEST);
    u8_t bit_activator = 1;
    i2c_util_write_bytes(&accelerometer, 0x2A, &bit_activator, sizeof(u8_t));
}
