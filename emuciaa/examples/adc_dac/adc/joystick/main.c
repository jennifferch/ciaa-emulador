#include "sapi.h"

int main()
{
    boardInit();
    adcInit( ADC_ENABLE );

    uint16_t sampleCH1 = 0;
    uint16_t sampleCH2 = 0;
    float voltageCH1 = 0.0;
    float voltageCH2 = 0.0;

    while (1) {
        sampleCH1 = adcRead( CH1 ); // ADC Read retorna un entero en el rango [0,1023] (conversor de 10 bits)
        
        sampleCH2 = adcRead( CH2 ); // ADC Read retorna un entero en el rango [0,1023] (conversor de 10 bits)

		voltageCH1 = (float)sampleCH1 * 3.3 / 1023.0;
		voltageCH2 = (float)sampleCH2 * 3.3 / 1023.0;

        printf("Lectura ADC CH1 en crudo: %d, lectura en voltaje CH1: %f\r\n", sampleCH1, voltageCH1 );
        printf("Lectura ADC CH2 en crudo: %d, lectura en voltaje CH2: %f\r\n", sampleCH2, voltageCH2 );

        delay(500);
    }
}