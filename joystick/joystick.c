#include "joystick.h"
const int VRX = 26; const int VRY = 27; const int SW = 22;
volatile absolute_time_t last_interrupt_time = 0; //variável que vai armazenar o tempo do sistema.
volatile bool R3_button_pressed = false; //variável que vai definir o comportamento do meu button R3.

void setup_joystick() { 
    adc_init(); // reset_adc(); 
    adc_gpio_init(VRX); // Configura o pino VRX (eixo X) para entrada ADC
    adc_gpio_init(VRY); // Configura o pino VRY (eixo Y) para entrada ADC
  
    gpio_init(SW);             // Inicializa o pino do botão.
    gpio_set_dir(SW, GPIO_IN); // Configura o pino do botão como entrada.
    gpio_pull_up(SW);          // Ativa o pull-up no pino do botão para evitar flutuações.

    // Configura a interrupção no pino do botão
    gpio_set_irq_enabled_with_callback(SW, GPIO_IRQ_EDGE_FALL, true, &R3_callback);
};

// Função de callback da interrupção
void R3_callback (uint gpio, uint32_t events) {
    // Verifica se o evento foi uma borda de descida (botão pressionado).
    if (events & GPIO_IRQ_EDGE_FALL) {

        absolute_time_t current_time = get_absolute_time(); 
        
        // Calcula o tempo decorrido desde a ultima interrupção.
        int64_t time_since_last_interrupt = absolute_time_diff_us(last_interrupt_time, current_time);

        // Debouncing: ignora eventos que ocorrem dentro de um intervalo muito curto.
        if (time_since_last_interrupt > 230000) {  // 230 ms de debounce
            R3_button_pressed = !R3_button_pressed;
        }
        // Atualiza o tempo do último evento de interrupção
        last_interrupt_time = current_time;
    };
};

