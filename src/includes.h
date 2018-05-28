/****************************************************************************
 * Copyright (C) 2018 by Bruno Georgevich Ferreira                          *
 * Github : https://github.com/brunogeorgevich/                             *
 ***************************************************************************/

/**
 * @file includes.h
 * @author Bruno Georgevich Ferreira
 * @date 27 May 2018
 * @brief Este arquivo contém todas as bibliotecas necessárias para os arquivos .h
 */
#ifndef INCLUDES_H
#define INCLUDES_H

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

#endif //INCLUDES_H
