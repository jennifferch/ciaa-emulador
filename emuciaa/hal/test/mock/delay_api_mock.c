#include "delay_api_mock.h"
#include <stdio.h>

void wait(float s);
void delay_ms(int ms);
void delay_us(int us);

void wait(float s){
    printf("Mock: wait invocado con float = %f\n", s);
}

void retard_ms(int ms){
    printf("Mock: delay_ms invocado con int = %d\n", ms);
}

void duration_us(int us){
    printf("Mock: delay_us invocado con int = %d\n", us);
}

void duration_ns(int ns){
    printf("Mock: delay_ns invocado con int = %d\n", ns);
}

/*==================[c++]====================================================*/

