/*============================================================================
 Copyright (c) 2018, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2018/08/03
 Version: 1.0
============================================================================*/

#include "sapi.h"

// Se deben establecer los valores del centro y umbrales segun su AnalogStick:

// En x:  Oeste                                               Este
// En y:  Sur                                                 Norte
//         |--------------------|--center--|--------------------|
//         0                   506  511   516                  1023

#define X_CENTER   511 // Ajustar centro segun como quede en reposo en x
#define Y_CENTER   511 // Ajustar centro segun como quede en reposo en y

#define THRESHOLD_X        5 // Ajustar luego de mover y soltar el AnalogStick
#define X_THRESHOLD_HIGH   X_CENTER + THRESHOLD_X
#define X_THRESHOLD_LOW    X_CENTER - THRESHOLD_X

#define THRESHOLD_Y        5 // Ajustar luego de mover y soltar el AnalogStick
#define Y_THRESHOLD_HIGH   Y_CENTER + THRESHOLD_Y
#define Y_THRESHOLD_LOW    Y_CENTER - THRESHOLD_Y

int main( void ) {

	boardInit();
	adcInit( ADC_ENABLE);

	uint16_t x_position = 0;
	uint16_t y_position = 0;

	while(1) {

		x_position = adcRead( CH1 );
		y_position = adcRead( CH2 );

		printf( "{x: %d; y: %d} ", x_position, y_position );

		if( x_position > X_THRESHOLD_HIGH ){
			printf("Moviendo al Este en x, ");
		} else if( x_position < X_THRESHOLD_LOW ){
			printf("Moviendo al Oste en x, ");
		} else{
			printf("Eje x en el centro, ");
		}

		if( y_position > Y_THRESHOLD_HIGH ){
			printf("moviendo al Norte en y.\r\n");
		} else if( y_position < Y_THRESHOLD_LOW ){
			printf("moviendo al Sur en y.\r\n");
		} else{
			printf("eje y en el centro.\r\n");
		}

		delay(100);
	}
	return 0 ;
}