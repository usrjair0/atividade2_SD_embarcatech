#ifndef DISPLAY_H
#define DISPLAY_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"

// Inicializa o display
void setup_display();

// Desenha um retângulo no display
void print_rectangle(int x1, int y1, int x2, int y2);

// função para limpar o display
void clear_display();

void msg_Display_mult(int x, int y, int tam, int line_spacing, int num_strings, ...);

#endif // DISPLAY_H