#include "led_rgb.h"

uint red_slice_num;
uint green_slice_num;

void setup_led_rgb() {
    gpio_set_function(RED_PIN, GPIO_FUNC_PWM);
    gpio_set_function(GREEN_PIN, GPIO_FUNC_PWM);

    red_slice_num = pwm_gpio_to_slice_num(RED_PIN);
    green_slice_num = pwm_gpio_to_slice_num(GREEN_PIN);

    pwm_set_clkdiv(red_slice_num, 4.0f);
    pwm_set_wrap(red_slice_num, 255); 
    pwm_set_enabled(red_slice_num, true);

    pwm_set_clkdiv(green_slice_num, 4.0f);
    pwm_set_wrap(green_slice_num, 255);
    pwm_set_enabled(green_slice_num, true);

    pwm_set_gpio_level(GREEN_PIN, 0);
    pwm_set_gpio_level(RED_PIN, 0);
};

void green_light() {
    pwm_set_gpio_level(GREEN_PIN, 120);
    pwm_set_gpio_level(RED_PIN, 0);
};

void red_light() {
    pwm_set_gpio_level(RED_PIN, 120);
    pwm_set_gpio_level(GREEN_PIN, 0);
};

