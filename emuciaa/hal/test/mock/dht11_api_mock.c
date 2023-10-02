#include "dht11_api_mock.h"
#include <stdio.h>

static bool dht11_read_result;

void dht11_api_mock_init(void) {
    // Inicializar el estado del mock
    dht11_read_result = false;
}

void dht11_api_mock_destroy(void) {
    // Limpiar el estado del mock
    dht11_read_result = false;
}

void dht11_read_set_result(bool result) {
    // Establecer el resultado del mock
    dht11_read_result = result;
}

void dht11_init( int32_t gpio ){
    printf("Mock: dht11_init invocado con gpio = %d\n", gpio);
}

bool_t dht11_read(float *phum, float *ptemp ){
    return dht11_read_result;
}


/*==================[c++]====================================================*/

