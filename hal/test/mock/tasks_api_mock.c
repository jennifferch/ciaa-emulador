#include "tasks_api_mock.h"
#include <stdio.h>

static int getTick_result;

void getTickCount_mock_init(void) {
    // Inicializar el estado del mock
    getTick_result = 0;
}

void getTickCount_mock_destroy(void) {
    // Limpiar el estado del mock
    getTick_result = 0;
}

void getTickCount_set_result(uint64_t result) {
    // Establecer el resultado del mock
    getTick_result = result;
}

void xStartTickCount(){
    printf("Mock: xStartTickCount invocado\n");
}

int getTickCount(){
    printf("Mock: xStartTickCount invocado\n");
    return getTick_result;
}
 
void setTaskDelayUntil(int pxPreviousWakeTime, int xTimeIncrement){
    printf("Mock: setTaskDelayUntil invocado con xTimeIncrement = %d\n", xTimeIncrement);
}