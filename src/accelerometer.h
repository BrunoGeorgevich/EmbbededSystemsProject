#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "includes.h"

#define ACCELEROMETER_ADDRESS   0x1D
#define ACCELEROMETER_REGISTER  0x0D
#define ACCELEROMETER_TEST      0x5A

#define REFRESH_TIME_ACCELEROMETER 16

struct i2c_dev accelerometer;
int translate_pos_accelerometer(int val);
void accelerometer_display(int x, int y);
void accelerometer_showcase();
void init_accelerometer();

#endif //ACCELEROMETER_H
