#include "temperature.h"


void temperature_showcase() {

#ifdef DEBUG
    printk("temp device is %p, name is %s\n",
           temperature_sensor, temperature_sensor->config->name);
#endif
    struct mb_display *disp = mb_display_get();

    int r;
    struct sensor_value temp_value;

    r = sensor_sample_fetch(temperature_sensor);
    if (r) {
#ifdef DEBUG
        printk("sensor_sample_fetch failed return: %d\n", r);
#endif
        return;
    }

    r = sensor_channel_get(temperature_sensor, SENSOR_CHAN_TEMP,
                           &temp_value);
    if (r) {
#ifdef DEBUG
        printk("sensor_channel_get failed return: %d\n", r);
#endif
        return;
    }


    u32_t temperature_value = (u32_t)sensor_value_to_double(&temp_value);

    mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP,
                     K_MSEC(500), "%dC\n", temperature_value);
#ifdef DEBUG
    printk("Temperature is %d °C\n", temperature_value);
#endif

    k_sleep(1800);
}

void init_temperature_sensor() {
#ifdef DEBUG
    printk("Thermometer Example! %s\n", CONFIG_ARCH);
#endif

    temperature_sensor = device_get_binding("TEMP_0");
    if (!temperature_sensor) {
#ifdef DEBUG
        printf("error: no temp device\n");
#endif
        return;
    }
}
