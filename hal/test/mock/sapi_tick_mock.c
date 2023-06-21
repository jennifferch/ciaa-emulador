#include "sapi_tick_mock.h"
#include <stdio.h>

static bool_t tickInit_result;
static bool_t tickCallbackSet_result;
static uint64_t tickRead_result;

void tickInit_mock_init(void) {
    // Inicializar el estado del mock
    tickInit_result = false;
}

void tickInit_mock_destroy(void) {
    // Limpiar el estado del mock
    tickInit_result = false;
}

void tickInit_set_result(bool result) {
    // Establecer el resultado del mock
    tickInit_result = result;
}

void tickCallbackSet_mock_init(void) {
    // Inicializar el estado del mock
    tickCallbackSet_result = false;
}

void tickCallbackSet_mock_destroy(void) {
    // Limpiar el estado del mock
    tickCallbackSet_result = false;
}

void tickCallbackSet_set_result(bool result) {
    // Establecer el resultado del mock
    tickCallbackSet_result = result;
}

void tickRead_mock_init(void) {
    // Inicializar el estado del mock
    tickRead_result = 0;
}

void tickRead_mock_destroy(void) {
    // Limpiar el estado del mock
    tickRead_result = 0;
}

void tickRead_set_result(uint64_t result) {
    // Establecer el resultado del mock
    tickRead_result = result;
}

bool_t tickInit( tick_t tickRateMSvalue ){
    return tickInit_result;
}

tick_t tickRead( void ){
    return tickRead_result;
}

void tickWrite( tick_t ticks ){
    printf("Mock: tickWrite invocado con tick_t = %lu\n", ticks);
}

bool_t tickCallbackSet( callBackFuncPtr_t tickCallback, void* tickCallbackParams ){
    return tickCallbackSet_result;
}

void tickPowerSet( bool_t power ){
    printf("Mock: tickPowerSet invocado con power = %d\n", power);
}
