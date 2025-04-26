#include "display.h"

#define I2C_PORT i2c1
const uint I2C_SDA = 14;
const uint I2C_SCL = 15; 

ssd1306_t disp;

void setup_display() {
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); 
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); 
    gpio_pull_up(I2C_SDA); 
    gpio_pull_up(I2C_SCL); 
    disp.external_vcc = false; 
    ssd1306_init(&disp, 128, 64, 0x3C, I2C_PORT);
    ssd1306_clear(&disp); 
};

void print_rectangle(int x1, int y1, int x2, int y2) {
    ssd1306_draw_empty_square(&disp, x1, y1, x2, y2); // Desenha um retângulo vazio nas coordenadas especificadas
    ssd1306_show(&disp); 
};

void clear_display() {
    ssd1306_clear(&disp); // Limpa todo o conteúdo do display
};

// Função para exibir múltiplas strings, cada uma em uma nova linha
void msg_Display_mult(int x, int y, int tam, int line_spacing, int num_strings, ...) {
    va_list args; 
    va_start(args, num_strings);

    for (int i = 0; i < num_strings; i++) {
        const char *msg = va_arg(args, const char*);
        ssd1306_draw_string(&disp, x, y + (i * line_spacing), tam, msg); 
    };

    va_end(args);
    ssd1306_show(&disp); // Atualiza o display para exibir as strings
};