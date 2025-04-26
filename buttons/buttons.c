#include "buttons.h"

void setup_buttons(){
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);
};

bool button_A_pressed(){
    static absolute_time_t last_press = 0;
    static bool last_state = false;
    bool current_state = !gpio_get(BUTTON_A);
    
    if (current_state != last_state) {
        last_press = get_absolute_time();
        last_state = current_state;
    };
    
    return current_state && (absolute_time_diff_us(last_press, get_absolute_time()) > 50000);
};

bool button_B_pressed(){
    static absolute_time_t last_press = 0;
    static bool last_state = false;
    bool current_state = !gpio_get(BUTTON_B);
    
    if (current_state != last_state) {
        last_press = get_absolute_time();
        last_state = current_state;
    };
    
    return current_state && (absolute_time_diff_us(last_press, get_absolute_time()) > 50000);
};