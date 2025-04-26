#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdio.h>     
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define JOYSTICK_READ_INTERVAL_us 240000 //intervalo em us

void setup_joystick();

#endif // JOYSTICK_H