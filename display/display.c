#include "display.h" // Inclui o arquivo de cabeçalho para o display

#define I2C_PORT i2c1 // Define a porta I2C a ser utilizada (i2c1)
const uint I2C_SDA = 14; // Define o pino GPIO para SDA (dados) do I2C
const uint I2C_SCL = 15; // Define o pino GPIO para SCL (clock) do I2C

ssd1306_t disp; // Variável global que representa o display OLED

// Função para inicializar o display
void setup_display() {
    i2c_init(I2C_PORT, 400 * 1000); // Inicializa a comunicação I2C com frequência de 400 kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Configura o pino SDA como função I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Configura o pino SCL como função I2C
    gpio_pull_up(I2C_SDA); // Habilita o resistor pull-up no pino SDA
    gpio_pull_up(I2C_SCL); // Habilita o resistor pull-up no pino SCL
    disp.external_vcc = false; // Define que o display não usa fonte de alimentação externa
    ssd1306_init(&disp, 128, 64, 0x3C, I2C_PORT); // Inicializa o display OLED com 128x64 pixels e endereço I2C 0x3C
    ssd1306_clear(&disp); // Limpa a tela do display
};

// Função para desenhar um retângulo vazio no display
void print_rectangle(int x1, int y1, int x2, int y2) {
    ssd1306_draw_empty_square(&disp, x1, y1, x2, y2); // Desenha um retângulo vazio nas coordenadas especificadas
    ssd1306_show(&disp); // Atualiza o display para exibir o retângulo
};

// Função para limpar a tela do display
void clear_display() {
    ssd1306_clear(&disp); // Limpa todo o conteúdo do display
};

// Função para exibir múltiplas strings, cada uma em uma nova linha
void msg_Display_mult(int x, int y, int tam, int line_spacing, int num_strings, ...) {
    va_list args; // Declara uma lista de argumentos variáveis
    va_start(args, num_strings); // Inicializa a lista de argumentos

    // Loop para exibir cada string
    for (int i = 0; i < num_strings; i++) {
        const char *msg = va_arg(args, const char*); // Obtém a próxima string da lista de argumentos
        ssd1306_draw_string(&disp, x, y + (i * line_spacing), tam, msg); // Exibe a string na posição (x, y + i * line_spacing)
    }

    va_end(args); // Finaliza a lista de argumentos
    ssd1306_show(&disp); // Atualiza o display para exibir as strings
};