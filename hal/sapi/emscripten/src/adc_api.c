#include "emscripten.h"
#include "adc_api.h"

void adc_init(adc_t *obj, adcMap_t pin) {
    obj->pin = pin;

    EM_ASM_({
        JSHal.gpio.init_analogin($0, $1);
    }, obj, obj->pin);
}

uint16_t adc_read_u16(adc_t *obj) {
    return EM_ASM_INT({
        return JSHal.gpio.read($0);
    }, obj->pin);
}

uint16_t adc_read(adc_t *obj) {
    int v = EM_ASM_INT({
        return JSHal.gpio.read($0);
    }, obj->pin);

    return v;
}

