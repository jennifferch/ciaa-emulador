#ifndef GPIO_API_MOCK_H
#define GPIO_API_MOCK_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "sapi_peripheral_map.h"

#ifdef __cplusplus
extern "C" {
#endif

void gpio_api_mock_init(void);
void gpio_api_mock_destroy(void);
void gpio_read_set_result(int result);
void gpio_set_result(uint32_t result);

// Mocks de las funciones de la biblioteca gpio_api.h
uint32_t gpio_set(gpioMap_t pin);
void gpio_init(gpio_t *obj, gpioMap_t pin);
void gpio_mode(gpio_t *obj, PinMode mode);
void gpio_dir(gpio_t *obj, PinDirection direction);
void gpio_init_in(gpio_t* gpio, gpioMap_t pin);
void gpio_init_in_ex(gpio_t* gpio, gpioMap_t pin, PinMode mode);
void gpio_init_out(gpio_t* gpio, gpioMap_t pin);
void gpio_init_out_ex(gpio_t* gpio, gpioMap_t pin, int value);
void gpio_init_inout(gpio_t* gpio, gpioMap_t pin, PinDirection direction, PinMode mode, int value);
void gpio_write(gpio_t *obj, int value);
int gpio_read(gpio_t *obj);
int gpio_is_connected(const gpio_t *obj);

#ifdef __cplusplus
}
#endif

#endif