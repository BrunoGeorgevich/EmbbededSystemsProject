/****************************************************************************
 * Copyright (C) 2018 by Bruno Georgevich Ferreira                          *
 * Github : https://github.com/brunogeorgevich/                             *
 ***************************************************************************/

/**
 * @file state.h
 * @author Bruno Georgevich Ferreira
 * @date 27 May 2018
 * @brief Este arquivo contém as constantes e variáveis relacionadas a Máquina de Estados
 */
#ifndef STATE_H
#define STATE_H

/**
 * @brief Enum responsável por definir os estados da Máquina de Estados
 */
enum state_t{
    HELLOWORLD,     /**< Estado 1 */
    TEMPERATURE,    /**< Estado 2 */
    ACCELETOMETER,  /**< Estado 3 */
    MAGNETOMETER   /**< Estado 4 */
};

/**
 * @brief Struct que modela o formato de um estado da Máquina de Estados
 */
struct state {
    union {
        struct internal_states{ /**< Referencia os estado anterior, atual e posterior */
            enum state_t previous; /**< Referencia o estado anterior */
            enum state_t current;  /**< Referencia o estado atual */
            enum state_t next;     /**< Referencia o estado posterior */
        };
        enum state_t s[3]; /**< Permite o acesso às referencias dos estados por um Array */
    };

    void (*run)(void); /**< Referencia o método a ser executado pelo estado atual */
};

#endif //STATE_H
