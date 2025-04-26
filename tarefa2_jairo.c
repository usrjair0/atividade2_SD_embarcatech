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

void update_display() {
    clear_display();
    msg_Display_mult(15, 12, 1, 12, 3, 
        gate_names[(current_gate - 1 + NUM_PORTS) % NUM_PORTS],
        gate_names[current_gate],
        gate_names[(current_gate + 1) % NUM_PORTS]);
    print_rectangle(2, 22, 120, 12);
};

int main()
{
    stdio_init_all();
    setup_display();
    setup_joystick();

    absolute_time_t next_joystick_read = delayed_by_us(get_absolute_time(), JOYSTICK_READ_INTERVAL_us);

    uint adc_y_raw;
    uint bar_y_pos;
    uint prev_pos_y;
    const uint bar_width = 40;
    const uint adc_max = (1 << 12) - 1;

    update_display();

    while (true)
    {

        if (time_reached(next_joystick_read))
        {
            next_joystick_read = delayed_by_us(next_joystick_read, JOYSTICK_READ_INTERVAL_us);
            adc_y_raw = adc_read(); // leitura adc do joystick.
            bar_y_pos = adc_y_raw * bar_width / adc_max;

            // nesse caso o usuário está apontando o joystick para baixo.
            if (bar_y_pos < 4)
            { 
                current_gate = (current_gate + 1) % NUM_PORTS;
                update_display();
            };

            if (bar_y_pos > 32) // nesse caso o usuário está apontando o joystick para cima.
            {    
                current_gate = (current_gate - 1 + NUM_PORTS) % NUM_PORTS;
                update_display();
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
            printf("porta XOR");
            break;

        case PORT_XNOR:
            printf("porta XNOR");
            break;

        default:

            break;
        };

        sleep_ms(100);
    };
};
