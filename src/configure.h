/****************************************************************************
 * Copyright (C) 2018 by Bruno Georgevich Ferreira                          *
 * Github : https://github.com/brunogeorgevich/                             *
 ***************************************************************************/

/**
 * @file configure.h
 * @author Bruno Georgevich Ferreira
 * @date 27 May 2018
 * @brief Este arquivo contém as funções, constantes e variáveis responsáveis por configurar e abstrair os Sensores da MicroBit
 */
#ifndef CONFIGURE_H
#define CONFIGURE_H

#include "includes.h"

#include "helloworld.h"
#include "temperature.h"
#include "accelerometer.h"
#include "compass.h"

#include "state.h"

#define PROGRAM_RUNS_CORRECTLY 1 /**< Constante responsável por agregar legibilidade ao loop de iterações da execução do estado atual */
#define NO_ERRORS 0 /**< Constante responsável por agregar legibilidade ao retorno 0 da função Main */
#define DEBUG /**< Constante responsável por habilitar os printk's do código */

/**
 * @brief Variável responsável por armazenar o momento que o qual o último clique foi realizado no Botão A
 */
s64_t a_timestamp;

/**
 * @brief Variável responsável por armazenar o momento que o qual o último clique foi realizado no Botão B
 */
s64_t b_timestamp;

/**
 * @brief Variável responsável por armazenar o estados predefinidos da Máquina de Estados
 */
extern struct state state_machine[4];

/**
 * @brief Variável responsável por referenciar o tipo do estado atual
 */
enum state_t current_state_t;

/**
 * @brief Variável responsável por referenciar o estado atual
 */
struct state *current_state;

/**
 * @brief Função que irá identificar o botão apertado e executar a ação delegada ao mesmo
 */
void button_pressed(struct device *dev, struct gpio_callback *cb,
                    u32_t pins);

/**
 * @brief Função responsável por configurar os botões e seus devidos pinos e callbacks
 */
void configure_buttons(void);

/**
 * @brief Função responsável por inicializar todos os sensores utilizados no projeto
 */
void init_sensors(void);

/**
 * @brief Função responsável por inicializar a Máquina de Estados
 */
void init_state_machine(void);

#endif //CONFIGURE_H
