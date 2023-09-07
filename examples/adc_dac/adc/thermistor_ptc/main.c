#include "sapi.h"

int main()
{
    boardInit();
    adcInit( ADC_ENABLE );

    uint16_t sample = 0;
    float voltage = 0.0;

    while (1) {
        sample = adcRead( CH1 ); // ADC Read retorna un entero en el rango [0,1023] (conversor de 10 bits)

		voltage = (float)sample * 3.3 / 1023.0;

        printf("Lectura ADC en crudo: %d, lectura en voltaje: %f\r\n", sample, voltage );

        delay(500);
    }
}