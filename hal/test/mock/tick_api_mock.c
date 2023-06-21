#include "tick_api_mock.h"
#include <stdio.h>

void tick_enable(uint32_t tickRateMSvalue) {
   printf("Mock: tickRateMSvalue invocado\n");
}