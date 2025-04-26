#ifndef LED_RGB_H
#define LED_RGB_H

#include <stdio.h>     
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define RED_PIN   13   // Exemplo: pino do LED vermelho
#define GREEN_PIN 11   // Exemplo: pino do LED verde

// Variáveis para controle PWM
extern uint red_slice_num;
extern uint green_slice_num;

void setup_led_rgb();
void green_light();  // brightness de 0 a 255
void red_light();    // brightness de 0 a 255

#endif // LED_RGB_H