#include "delay_api.h"
#include <unistd.h>

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
