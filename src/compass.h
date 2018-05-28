/****************************************************************************
 * Copyright (C) 2018 by Bruno Georgevich Ferreira                          *
 * Github : https://github.com/brunogeorgevich/                             *
 ***************************************************************************/

/**
 * @file compass.h
 * @author Bruno Georgevich Ferreira
 * @date 27 May 2018
 * @brief Este arquivo contém as funções, constantes e variáveis relacionadas a funcionalidade da Bússola
 */
#ifndef COMPASS_H
#define COMPASS_H

#include "includes.h"

#define COMPASS_ADDRESS         0x0e /**< Endereço da Bússola */
#define COMPASS_REGISTER        0x07 /**< Registrador da Bússola */
#define COMPASS_TEST            0xC4 /**< Código de Teste da Bússola */


#define REFRESH_TIME_COMPASS 1000 /**< Tempo de Reiterção da Bússola */

/**
 * @brief Variável responsável por estabelecer a comunicação I²C com a Bússola
 */
struct i2c_dev compass;
/**
 * @brief Função que irá mostrar na Matriz 5x5 um "T"
 */
void compass_display();

/**
 * @brief Função que irá executar a funcionalidade da Bússola Implementada
 */
void compass_showcase();

/**
 * @brief Método que irá iniciar as variáveis responsáveis pelo bom funcionamento da Bússola
 */
void init_compass();

#endif //COMPASS_H
