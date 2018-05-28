#include "compass.h"


void compass_display() {

    struct mb_display *disp = mb_display_get();

    char *str = "T";

    mb_display_print(disp, MB_DISPLAY_MODE_SINGLE, K_MSEC(REFRESH_TIME_COMPASS), str);
    k_sleep(K_MSEC(REFRESH_TIME_COMPASS)*strlen(str));
}

void compass_showcase() {
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

void init_compass() {
    i2c_util_dev_init(&compass, COMPASS_ADDRESS, "COMPASS", COMPASS_REGISTER, COMPASS_TEST);

    u8_t bit_activator = 1;
    i2c_util_write_bytes(&compass, 0x10, &bit_activator, sizeof(u8_t));
}
