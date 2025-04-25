#include "joystick.h"
const int VRX = 26; const int VRY = 27; 

void setup_joystick() { 
    adc_init(); // reset_adc(); 
    adc_gpio_init(VRX); // Configura o pino VRX (eixo X) para entrada ADC
    adc_gpio_init(VRY); // Configura o pino VRY (eixo Y) para entrada ADC
};


