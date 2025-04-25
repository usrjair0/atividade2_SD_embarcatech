#include <stdio.h>
#include "pico/stdlib.h"
#include "display/display.h"
#include "joystick/joystick.h"
#include "pico/time.h"

typedef enum
{
    PORT_AND,
    PORT_OR,
    PORT_NOT,
    PORT_NAND,
    PORT_NOR,
    PORT_XOR,
    PORT_XNOR,
    NUM_PORTS
} logicGate;

const char *gate_names[NUM_PORTS] = {
    "porta AND", "porta OR", "porta NOT", "porta NAND",
    "porta NOR", "porta XOR", "porta XNOR"};

logicGate current_gate = PORT_AND;

typedef enum
{
    PORT_SELECTION,
    PORT_RUN
} programState;

programState program_state = PORT_SELECTION;

int main()
{
    stdio_init_all();
    setup_display();
    setup_joystick();

    absolute_time_t next_joystick_read = delayed_by_us(get_absolute_time(), JOYSTICK_READ_INTERVAL_us);

    uint adc_y_raw;
    uint bar_y_pos;
    uint prev_pos_y;

    uint pos_y = 12;
    uint menu_item = 2;
    const uint bar_width = 40;
    const uint adc_max = (1 << 12) - 1;
    const uint menu_lines = 3;
    const uint valor_max_posY = menu_lines * pos_y - 2;
    const uint valor_min_posY = 10;

    pos_y = menu_item * 12;
    msg_Display_mult(15, 12, 1, 12, 3, gate_names[(current_gate - 2 + NUM_PORTS) % NUM_PORTS], gate_names[(current_gate - 1 + NUM_PORTS) % NUM_PORTS], gate_names[current_gate]);
    print_rectangle(2, pos_y - 2, 120, 12);

    while (true)
    {

        if (time_reached(next_joystick_read))
        {
            next_joystick_read = delayed_by_us(next_joystick_read, JOYSTICK_READ_INTERVAL_us);
            adc_y_raw = adc_read(); // leitura adc do joystick.
            bar_y_pos = adc_y_raw * bar_width / adc_max;
            prev_pos_y = pos_y;

            // nesse caso o usuário está apontando o joystick para baixo.
            if (bar_y_pos < 4)
            {
                menu_item += 1;
                if (menu_item == 4)
                {
                    menu_item--;
                    current_gate = (current_gate + 1) % NUM_PORTS;
                    clear_display();
                    pos_y = menu_item * 12;
                    msg_Display_mult(15, 12, 1, 12, 3, gate_names[(current_gate - 2 + NUM_PORTS) % NUM_PORTS], gate_names[(current_gate - 1 + NUM_PORTS) % NUM_PORTS], gate_names[current_gate]);
                    print_rectangle(2, pos_y - 2, 120, 12);
                }
                else
                {
                    clear_display();
                    pos_y = menu_item * 12;
                    msg_Display_mult(15, 12, 1, 12, 3, gate_names[(current_gate - 2 + NUM_PORTS) % NUM_PORTS], gate_names[(current_gate - 1 + NUM_PORTS) % NUM_PORTS], gate_names[current_gate]);
                    print_rectangle(2, pos_y - 2, 120, 12);
                };
            };

            if (bar_y_pos > 32) // nesse caso o usuário está apontando o joystick para cima.
            {
                menu_item -= 1;
                if (menu_item == 0)
                {
                    menu_item++;
                    current_gate = (current_gate - 1 + NUM_PORTS) % NUM_PORTS;
                    clear_display();
                    pos_y = menu_item * 12;
                    msg_Display_mult(15, 12, 1, 12, 3, gate_names[(current_gate - 2 + NUM_PORTS) % NUM_PORTS], gate_names[(current_gate - 1 + NUM_PORTS) % NUM_PORTS], gate_names[current_gate]);
                    print_rectangle(2, pos_y - 2, 120, 12);
                }
                else
                {
                    clear_display();
                    pos_y = menu_item * 12;
                    msg_Display_mult(15, 12, 1, 12, 3, gate_names[(current_gate - 2 + NUM_PORTS) % NUM_PORTS], gate_names[(current_gate - 1 + NUM_PORTS) % NUM_PORTS], gate_names[current_gate]);
                    print_rectangle(2, pos_y - 2, 120, 12);
                };
            };
        };

        switch (current_gate)
        {
        case PORT_AND:
            printf("porta and");
            break;

        case PORT_OR:
            printf("porta OR");
            break;

        case PORT_NOT:
            printf("porta NOT");
            break;

        case PORT_NAND:
            printf("porta NAND");
            break;

        case PORT_NOR:
            printf("porta NOR");
            break;

        case PORT_XOR:

            break;

        case PORT_XNOR:

            break;

        default:

            break;
        };

        sleep_ms(100);
    };
};
