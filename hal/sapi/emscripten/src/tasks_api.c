/*
 * FreeRTOS Kernel V10.0.1
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#include "tasks_api.h"

typedef struct {
    int counter;
    int delay;
} DelayParams;

int counter = 0;

void updateTickCount() {
   // printf("Counter: %d\n", counter);
    counter++;
}

void EMSCRIPTEN_KEEPALIVE xStartTickCount() {
    counter = 0;
    counter++;
   // emscripten_set_main_loop(updateTickCount, 1000, 1);
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
    
  //  params->initialCounter = counter;
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
   // params.counter = ((xTimeIncrement * 1000 )/ 1000);
   // params.delay = ((pxPreviousWakeTime * 1000 )/ 1000);

    params.counter = 10;
    params.delay = 500;

    emscripten_async_call(delayCallback, &params, 0);
}