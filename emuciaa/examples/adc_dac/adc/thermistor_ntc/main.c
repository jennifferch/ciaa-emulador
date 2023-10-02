#include "sapi.h"

int main()
{
    boardInit();
    adcInit( ADC_ENABLE );

    uint16_t sample = 0;

    const float adc_resolution = 1023.0; // 1023 for 10 bit resolution ADC of EDU-CIAA
    const float Vsupply = 3.3;           // Power supply voltage (3.3V) 
    const float R_10k = 9840;            // 10k resistor measured resistance in Ohms (other element in the voltage divider)
    const float B_param = 3700;          // B-coefficient of the thermistor
    const float T0 = 298.15;             // 25°C in Kelvin
    
    float Temp_K; // Temperature measured by the thermistor (Kelvin)
    float Temp_C; // Temperature measured by the thermistor (Celsius)
    float Vout;   // Voltage divider output
    float R_NTC;  // NTC thermistor resistance in Ohms

    while (1) {
		sample = adcRead( CH1 ); // ADC Read retuns an integer in range [0,1023] (10 bits resolution)

		Vout = sample * (Vsupply/1023);

		R_NTC = (Vout * R_10k) / (Vsupply - Vout); // Calculating the resistance of the thermistor

		Temp_K = (T0*B_param) / (T0*log(R_NTC/R_10k) + B_param); // Temperature in Kelvin

		Temp_C = Temp_K - 273.15; // Converting into Celsius
		
		printf("ADC: %d Vout: %.2f R_NTC: %.2f Temp_K: %.2f Temp_C: %.2f\r\n", sample, Vout, R_NTC, Temp_K, Temp_C );
		
		delay(500);
    }
}