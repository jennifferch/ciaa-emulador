/*============================================================================
 Copyright (c) 2023, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2023/09/11
 Version: 1.0
 NTC Thermistor calculations from:
   https://curiousscientist.tech/blog/ntc-thermometer-stm32-arduino
============================================================================*/

#include "sapi.h"

int main( void )
{
    boardInit();
    adcInit( ADC_ENABLE );

    uint16_t sample = 0;

    const float adc_resolution = 1023.0; // 1023 par los 10 bits de resolucion del ADC de la EDU-CIAA-NXP
    const float Vsupply = 3.3;           // Voltaje de alimentacion (3.3V) 
    const float R_10k = 9840;            // Resistencia de 10k medida en Ohms para hacer las cuentas mejor
    const float B_param = 3700;          // Coeficiente B del termistor
    const float T0 = 298.15;             // 25°C en escala Kelvin
    
    float Temp_K; // Temperatura medida por el termistor (Kelvin)
    float Temp_C; // Temperatura medida por el termistor (Celsius)
    float Vout;   // Voltaje de salida del divisor resisitivo
    float R_NTC;  // Resistencia del NTC en Ohms

    while(1) {

		sample = adcRead( CH1 ); // ADC Read retorna un entero en el rango [0,1023] (resolucion 10 bits)

		Vout = sample * (Vsupply/1023);

		R_NTC = (Vout * R_10k) / (Vsupply - Vout); // Calcular la resistencia del termistor

		Temp_K = (T0*B_param) / (T0*log(R_NTC/R_10k) + B_param); // Calcular temperatura en Kelvin

		Temp_C = Temp_K - 273.15; // Convertir a Celsius
		
		printf("ADC: %d Vout: %.2f R_NTC: %.2f Temp_K: %.2f Temp_C: %.2f\r\n", sample, Vout, R_NTC, Temp_K, Temp_C );
		
		delay(500);
    }
}