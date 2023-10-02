#ifndef _DHT11_API_MOCK_H
#define _DHT11_API_MOCK_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdbool.h>

#include "sapi_peripheral_map.h"

#ifdef __cplusplus
extern "C" {
#endif

void dht11_api_mock_init(void);
void dht11_api_mock_destroy(void);
void dht11_read_set_result(bool result);

/* Mock de la función dht11_init */
void dht11_init(int32_t gpio);

/* Mock de la función dht11_read */
bool_t dht11_read(float *phum, float *ptemp);

#ifdef __cplusplus
}
#endif
#endif 
