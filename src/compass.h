#ifndef COMPASS_H
#define COMPASS_H

#include "includes.h"

#define COMPASS_ADDRESS         0x0e
#define COMPASS_REGISTER        0x07
#define COMPASS_TEST            0xC4

#define REFRESH_TIME_COMPASS 1000

struct i2c_dev compass;
void compass_display();
void compass_showcase();
void init_compass();

#endif //COMPASS_H
