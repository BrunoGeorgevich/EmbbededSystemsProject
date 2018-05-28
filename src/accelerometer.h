/****************************************************************************
 * Copyright (C) 2018 by Bruno Georgevich Ferreira                          *
 * Github : https://github.com/brunogeorgevich/                             *
 ***************************************************************************/

/**
 * @file accelerometer.h
 * @author Bruno Georgevich Ferreira
 * @date 27 May 2018
 * @brief Este arquivo contém as funções, constantes e variáveis relacionadas a funcionalidade do Acelerômetro
 */
#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "includes.h"

#define ACCELEROMETER_ADDRESS   0x1D /**< Endereço do Acelerômetro */
#define ACCELEROMETER_REGISTER  0x0D /**< Registrador do Acelerômetro */
#define ACCELEROMETER_TEST      0x5A /**< Código de Teste do Acelerômetro */

#define REFRESH_TIME_ACCELEROMETER 16 /**< Tempo de Reiterção do Acelerômetro*/

/**
 * @brief Variável responsável por estabelecer a comunicação I²C com o Acelerômetro
 */
struct i2c_dev accelerometer;
/**
 * @brief Função que traduz os valores coletados pelo Acelerômetro para uma posição em uma Matriz 5x5
 * @param int val - Valor que será mapeado de 0 a 4
 */
int translate_pos_accelerometer(int32_t val);
/**
 * @brief Função que irá representar a variação do Acelerômetro em uma Matriz 5x5
 * @param int x - Coordenada X coletada do Acelerômetro
 * @param int x - Coordenada Y coletada do Acelerômetro
 */
void accelerometer_display(int32_t x, int32_t y);
/**
 * @brief Função que irá executar a funcionalidade do Acelerômetro Implementada
 */
void accelerometer_showcase();
/**
 * @brief Função que irá iniciar as variáveis responsáveis pelo bom funcionamento do Acelerômetro
 */
void init_accelerometer();

#endif //ACCELEROMETER_H
