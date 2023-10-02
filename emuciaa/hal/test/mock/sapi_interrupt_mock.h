#ifndef SAPI_INTERRUPT_MOCK_H
#define SAPI_INTERRUPT_MOCK_H

#include <stdint.h>
#include <string.h>  
#include <stdbool.h>
#include "sapi_peripheral_map.h"

#ifdef __cplusplus
extern "C" {
#endif

void interrupt_api_mock_init(void);
void interrupt_api_mock_destroy(void);
void interrupt_set_result(bool_t result);

// Mocks de las funciones de la biblioteca sapi_interrupt.h
void interruptInit(gpioMap_t pin);
static void _irq_handler(uint32_t id, gpio_irq_event event);
bool_t read_event_state(gpioMap_t pin);
void interruptin_fall(void (*func)());
void interruptin_rise(void (*func)());

#ifdef __cplusplus
}
#endif

#endif

