#include "joystick.h"
const int VRX = 26; const int VRY = 27; 

void setup_joystick() { 
    adc_init(); 
    adc_gpio_init(VRX);
    adc_gpio_init(VRY);
};


