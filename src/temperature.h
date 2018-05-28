/****************************************************************************
 * Copyright (C) 2018 by Bruno Georgevich Ferreira                          *
 * Github : https://github.com/brunogeorgevich/                             *
 ***************************************************************************/

/**
 * @file temperature.h
 * @author Bruno Georgevich Ferreira
 * @date 27 May 2018
 * @brief Este arquivo contém as funções, constantes e variáveis relacionadas a funcionalidade do Sensor de Temperatura
 */
#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "includes.h"

/**
 * @brief Variável responsável por abstrair a comunicação com o Sensor de Temperatura
 */
struct device *temperature_sensor;

/**
 * @brief Função que irá executar a funcionalidade do Sensor de Temperatura Implementada
 */
void temperature_showcase();

/**
 * @brief Função que irá iniciar as variáveis responsáveis pelo bom funcionamento do Sensor de Temperatura
 */
void init_temperature_sensor();

#endif //TEMPERATURE_H
