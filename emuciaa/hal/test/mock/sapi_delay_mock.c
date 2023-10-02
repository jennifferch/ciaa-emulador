#include "sapi_delay_mock.h"
#include <stdio.h>

static bool_t delay_read_result;

void delay_api_mock_init(void) {
    // Inicializar el estado del mock
    delay_read_result = false;
}

void delay_api_mock_destroy(void) {
    // Limpiar el estado del mock
    delay_read_result = false;
}

void delay_read_set_result(bool result) {
    // Establecer el resultado del mock
    delay_read_result = result;
}

void delayInaccurateMs( tick_t delay_ms ){
    printf("Mock: delayInaccurateMs invocado con delay_ms = %lu\n", delay_ms);
}

void delayInaccurateUs( tick_t delay_us ){
    printf("Mock: delayInaccurateUs invocado con delay_us = %lu\n", delay_us);
}

void delayInaccurateNs( tick_t delay_ns ){
    printf("Mock: delayInaccurateNs invocado con delay_ns = %lu\n", delay_ns);
}

void delay( tick_t duration_ms ){
    printf("Mock: delay invocado con duration_ms = %lu\n", duration_ms);
}

void delayInit( delay_t * delay, tick_t duration ){
    printf("Mock: delayInit invocado con duration = %lu\n", duration);
}

bool_t delayRead( delay_t * delay ){
    return delay_read_result;
}

void delayWrite( delay_t * delay, tick_t duration ){
    printf("Mock: delayWrite invocado con duration = %lu\n", duration);
}
