/*============================================================================
 Copyright (c) 2016, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2016/04/26
 Version: 1.0
============================================================================*/

#include "sapi.h"

int main()
{
    boardInit();
    adcInit( ADC_ENABLE ); // Inicializar ADC

    uint16_t sample = 0;
    float voltage = 0.0;

    while(1) {
        sample = adcRead( CH1 ); // ADC Read retorna un entero en el rango [0,1023] (conversor de 10 bits)

		voltage = (float)sample * 3.3 / 1023.0;

        printf("Lectura ADC en crudo: %d, lectura en voltaje: %.2f V\r\n", sample, voltage );

        delay(500);
    }
}