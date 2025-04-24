#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdio.h>     
#include "pico/stdlib.h"
#include "hardware/adc.h"

// Intervalos de leitura do joystick (em milissegundos)
#define JOYSTICK_READ_INTERVAL 200  // 100 ms para economia de recursos

//funções
void setup_joystick();
void R3_callback (uint gpio, uint32_t events);

//variáveis globais
volatile extern bool R3_button_pressed;

#endif // JOYSTICK_H