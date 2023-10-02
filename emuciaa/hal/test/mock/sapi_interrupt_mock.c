#include "sapi_interrupt_mock.h"
#include <stdio.h>

static bool_t read_event_state_result;

void interrupt_api_mock_init(void) {
    // Inicializar el estado del mock
    read_event_state_result = false;
}

void interrupt_api_mock_destroy(void) {
    // Limpiar el estado del mock
    read_event_state_result = false;
}

void interrupt_set_result(bool_t result) {
    // Establecer el resultado del mock
    read_event_state_result = result;
}

void interruptInit(gpioMap_t pin){
    printf("Mock: interruptInit invocado con pin = %d\n", pin);
}
static void _irq_handler(uint32_t id, gpio_irq_event event){
    printf("Mock: _irq_handler\n");
}
bool_t read_event_state(gpioMap_t pin){
    return read_event_state_result;
}

void interruptin_fall(void (*func)()){
    printf("Mock: interruptin_fall\n");
}
void interruptin_rise(void (*func)()){
    printf("Mock: interruptin_rise\n");
}


