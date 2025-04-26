#include <stdio.h>
#include "pico/stdlib.h"
#include "display/display.h"
#include "joystick/joystick.h"
#include "buttons/buttons.h"
#include "led_rgb/led_rgb.h"
#include "pico/time.h"

// Enumeração das portas lógicas disponíveis
typedef enum
{
    PORT_AND,
    PORT_OR,
    PORT_NOT,
    PORT_NAND,
    PORT_NOR,
    PORT_XOR,
    PORT_XNOR,
    NUM_PORTS // Total de portas (usado para navegação circular)
} logicGate;

const char *gate_names[NUM_PORTS] = { // Nomes das portas para exibição no display
    "porta AND", "porta OR", "porta NOT", "porta NAND",
    "porta NOR", "porta XOR", "porta XNOR"};

logicGate current_gate = PORT_AND; // Porta lógica atualmente selecionada

// Atualiza o display com as informações da porta atual
void update_display()
{
    clear_display();
    msg_Display_mult(15, 12, 1, 12, 3,
                     gate_names[(current_gate - 1 + NUM_PORTS) % NUM_PORTS],
                     gate_names[current_gate],
                     gate_names[(current_gate + 1) % NUM_PORTS]);
    // Destaca visualmente a porta selecionada
    print_rectangle(2, 22, 120, 12);
};

int main()
{
    // Inicializações básicas
    stdio_init_all();
    setup_display();
    setup_joystick();
    setup_buttons();
    setup_led_rgb();

    // Configuração do temporizador para leitura do joystick
    absolute_time_t next_joystick_read = delayed_by_us(get_absolute_time(), JOYSTICK_READ_INTERVAL_us);

    // Variáveis para leitura do joystick
    uint adc_y_raw;
    uint bar_y_pos;
    uint prev_pos_y;
    const uint bar_width = 40;          // Largura da barra de referência
    const uint adc_max = (1 << 12) - 1; // Valor máximo do ADC (12 bits)

    update_display();

    while (true)
    {
        // Verifica se é hora de ler o joystick novamente
        if (time_reached(next_joystick_read))
        {
            // Reinicia o temporizador
            next_joystick_read = delayed_by_us(next_joystick_read, JOYSTICK_READ_INTERVAL_us);
            adc_y_raw = adc_read();                      // Lê a posição vertical do joystick
            bar_y_pos = adc_y_raw * bar_width / adc_max; // Normaliza o valor para a escala de referência

            if (bar_y_pos < 4) // Navegação para baixo (próxima porta lógica)
            {
                current_gate = (current_gate + 1) % NUM_PORTS; // Navegação circular
                update_display();
            };

            if (bar_y_pos > 32) // Navegação para cima (porta lógica anterior)
            {
                current_gate = (current_gate - 1 + NUM_PORTS) % NUM_PORTS; // Navegação circular
                update_display();
            };
        };

        // Implementação das portas lógicas
        switch (current_gate) 
        {
        case PORT_AND: // AND: Verde apenas se ambos os botões estiverem soltos
            if (!button_A_pressed() && !button_B_pressed())
            {
                green_light();
            }
            else
            {
                red_light();
            };
            break;

        case PORT_OR: // OR: verde desde que ambos não estejam pressionados
            if (!button_A_pressed() || !button_B_pressed())
            {
                green_light();
            }
            else
            {
                red_light();
            };
            break;

        case PORT_NOT: // NOT: Verde apenas quando botão A é pressionado
            if (button_A_pressed())
            {
                green_light();
            }
            else
            {
                red_light();
            };
            break;

        case PORT_NAND: // NAND: Verde desde que ao menos 1 ou ambos os botões estejam pressionados
            if (button_A_pressed() || button_B_pressed())
            {
                green_light();
            }
            else
            {
                red_light();
            };
            break;

        case PORT_NOR: // NOR: verde apenas se ambor forem pressionados
            if (button_A_pressed() && button_B_pressed())
            {
                green_light();
            }
            else
            {
                red_light();
            };
            break;

        case PORT_XOR: // XOR: verde desde que apenas 1 dos botões esteja pressionado
            if (button_A_pressed() != button_B_pressed())
            {
                green_light();
            }
            else
            {
                red_light();
            };
            break;

        case PORT_XNOR: //XNOR: verde desde que ambos os botões estejam pressionados ou ambos estejam soltos
            if (button_A_pressed() == button_B_pressed())
            {
                green_light();
            }
            else
            {
                red_light();
            };
            break;

        default:

            break;
        };

        sleep_ms(100);
    };
};
