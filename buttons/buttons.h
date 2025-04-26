#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdio.h>     
#include "pico/stdlib.h"

#define BUTTON_A 5
#define BUTTON_B 6

void setup_buttons();

bool button_A_pressed();

bool button_B_pressed();

#endif // BUTTONS_H