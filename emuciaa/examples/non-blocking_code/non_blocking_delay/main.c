/*============================================================================
 Copyright (c) 2020, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2020/03/05
 Version: 1.0
============================================================================*/

#include "sapi.h"

int main( void )
{
   boardInit();
   bool_t tec1 = 0;
	
   delay_t led1Delay; // Creo una variable de delay no bloqueante
   delayInit( &led1Delay, 500 ); // Inicializo el delay en 500 ms

   while(1) {

      tec1 = !gpioRead(TEC1);
      gpioWrite( LEDB, tec1 );

      if( delayRead(&led1Delay) ){
         gpioToggle( LED1 );
      }

	  delay(10); // Es necesario un minimo delay en el while(1) para que no se rompa el emulador
   }

   return 0;
}