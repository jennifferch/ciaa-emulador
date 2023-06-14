
#include <stddef.h>

#include "gpio_interrupt_api.h"
#include "emscripten.h"

static gpio_irq_handler irq_handler;

EMSCRIPTEN_KEEPALIVE
void handle_interrupt_in(uint32_t id, gpio_irq_event event) {
    EM_ASM_({
        console.log('::::EMSCRIPTEN_KEEPALIVE:::');
    });
    irq_handler(id, event);
}

int gpio_interrupt_init(gpio_irq_t *obj, gpioMap_t pin, gpio_irq_handler handler, uint32_t id) {
    if (pin == NC) return -1;

    irq_handler = handler;

    obj->port = pin;
    obj->pin = pin;

    EM_ASM_({
        JSHal.gpio.irq_init($0, $1);
    }, id, obj->pin);

    return 0;
}

void gpio_interrupt_free(gpio_irq_t *obj) {
    EM_ASM_({
        JSHal.gpio.irq_free($0);
    }, obj->pin, obj->id);
}

void gpio_interrupt_set(gpio_irq_t *obj, gpio_irq_event event, uint32_t enable) {
    EM_ASM_({
        JSHal.gpio.irq_set($0, $1, $2);
    }, obj->pin, event, enable);
}

