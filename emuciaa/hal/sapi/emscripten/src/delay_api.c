#include "delay_api.h"
#include <unistd.h>
#include <stdio.h>

int id = 1;
int contador = 1;
int tiempo_restante;


EMSCRIPTEN_KEEPALIVE
void handle_delay() {
    contador++;

    if (contador > tiempo_restante) {
        printf("contador %d\n", contador);

        contador = 0;
        // Detenemos el retardo después de tiempo_restante
        EM_ASM_({
           JSHal.delay.delay_detach($0);
       }, id);
    }
}

void wait(float s) {
    duration_us(s * 1000000.0f);
}

void retard_ms(int ms) {
    duration_us(ms * 1000);
}

void duration_us(int us) {
    emscripten_sleep(us / 1000);
}

void duration_ns(int ns){
    emscripten_sleep(ns);
}

void wait_ms(int ms) {
    tiempo_restante = ms;
     EM_ASM_({
         console.log('::::::::::: wait_ms');
         JSHal.delay.delay_setup($0, $1);
    }, id, 1000);
}

