#include "tasks_api.h"

typedef struct {
    int counter;
    int delay;
} DelayParams;

int counter = 0;

void updateTickCount() {
    counter++;
}

void EMSCRIPTEN_KEEPALIVE xStartTickCount() {
    counter = 0;
    counter++;
}

int EMSCRIPTEN_KEEPALIVE getTickCount() {
    return counter;
}

EMSCRIPTEN_KEEPALIVE
void delayCallback(void* arg) {
    DelayParams* params = (DelayParams*)arg;

    printf("params->counter: %i\n", params->counter);
    int counter = params->counter;
    int delay = params->delay;

    printf("counter: %i\n", counter);
    printf("delay: %i\n", delay);
    counter++;

    emscripten_sleep(delay);
    
    if (counter <= params->counter ) {

         printf("Entro: %i\n", counter);
         // Llamar a emscripten_sleep con el retraso especificado
         emscripten_sleep(delay);
         // Llamar a delayCallback nuevamente después del retraso
         emscripten_async_call(delayCallback, params, 0);
    }
}

EMSCRIPTEN_KEEPALIVE
void setTaskDelayUntil(int pxPreviousWakeTime, int xTimeIncrement) {

    printf("pxPreviousWakeTime: %i\n", pxPreviousWakeTime);
     printf("xTimeIncrement: %i\n", xTimeIncrement);

    DelayParams params;
    params.counter = 10;
    params.delay = 500;

    emscripten_async_call(delayCallback, &params, 0);
}