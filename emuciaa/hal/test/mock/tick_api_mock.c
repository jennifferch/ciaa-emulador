#include "tick_api_mock.h"
#include <stdio.h>

void tick_enable(uint32_t tickRateMSvalue) {
   printf("Mock: tickRateMSvalue invocado\n");
}

int tick_init(sapi_tick_handler handler, int id, int ms){
   printf("Mock: tick_init invocado con ms = %d\n", ms);
}

int tick_detach(int id){
   printf("Mock: tick_detach invocado con id = %d\n", id);
}

