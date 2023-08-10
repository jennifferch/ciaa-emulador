#include "dht11_api.h"

void dht11_init(int32_t gpio){
    gpioMap_t gpio1 = GPIO1; 
    gpioMap_t gnd = GND;

    EM_ASM_({
        JSHal.dht11.init($0, $1, $2);
    }, 1, gpio1, gnd);
}

bool_t dht11_read( float *phum, float *ptemp ){
    int temp = EM_ASM_INT({
        return JSHal.dht11.read_temperature($0);
    }, 1);

    int humidity = EM_ASM_INT({
        return JSHal.dht11.read_humidity($0);
    }, 1);

    *phum 	= ((float)humidity) / 100.0f;
    *ptemp 	= ((float)temp) / 100.0f;
    return TRUE;
}