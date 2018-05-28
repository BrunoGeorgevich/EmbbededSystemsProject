#ifndef CONFIGURE_H
#define CONFIGURE_H

#include "includes.h"

#include "helloworld.h"
#include "temperature.h"
#include "accelerometer.h"
#include "compass.h"

#include "state.h"

#define PROGRAM_RUNS_CORRECTLY 1
#define NO_ERRORS 0
#define DEBUG

s64_t a_timestamp;
s64_t b_timestamp;

extern struct state state_machine[4];

enum state_t current_state_t;
struct state *current_state;

void button_pressed(struct device *dev, struct gpio_callback *cb,
                    u32_t pins);
void configure_buttons(void);
void init_sensors(void);
void init_state_machine(void);

#endif //CONFIGURE_H
