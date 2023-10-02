#include "pwm_api.h"
#include "emscripten.h"
#include "sapi_peripheral_map.h"

void pwm_init(pwm_t* obj, gpioMap_t pin) {
    obj->pin = pin;

    EM_ASM_({
        JSHal.gpio.init_pwmout($0, $1, $2, $3);
    }, obj, obj->pin, 20, 0);
}

void pwm_write(pwm_t* obj, float value) {
    EM_ASM_({
        JSHal.gpio.write($0, $1);
    }, obj->pin, (int)(value * 1024.0f));
}

float pwm_read(pwm_t* obj) {
    int v = EM_ASM_({
        return JSHal.gpio.read($0);
    }, obj->pin);

    return ((float)v) / 1024.0f;
}

void pwm_period(pwm_t* obj, float seconds) {
    EM_ASM_({
        JSHal.gpio.period_ms($0, $1);
    }, obj->pin, (int)(seconds * 1000.0f));
}

void pwm_period_ms(pwm_t* obj, int ms) {
    EM_ASM_({
        JSHal.gpio.period_ms($0, $1);
    }, obj->pin, ms);
}

void pwm_period_us(pwm_t* obj, int us) {
    EM_ASM_({
        JSHal.gpio.period_ms($0, $1);
    }, obj->pin, us / 1000);
}

void pwm_pulsewidth(pwm_t* obj, float seconds) {
    EM_ASM_({
        JSHal.gpio.pulsewidth_ms($0, $1);
    }, obj->pin, (int)(seconds * 1000.0f));
}

void pwm_pulsewidth_ms(pwm_t* obj, int ms) {
    EM_ASM_({
        JSHal.gpio.pulsewidth_ms($0, $1);
    }, obj->pin, ms);
}

void pwm_pulsewidth_us(pwm_t* obj, int us) {
    EM_ASM_({
        JSHal.gpio.pulsewidth_ms($0, $1);
    }, obj->pin, us / 1000);
}
