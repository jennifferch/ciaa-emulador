/*============================================================================
 Copyright (c) 2016, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2016/04/26
 Version: 1.0
============================================================================*/

#include "sapi.h"

// Funcion que se ejecuta cada vez que ocurre un Tick.
void myTickCallback( void *ptr )
{
   gpioMap_t led = (gpioMap_t)ptr; // Obtener el parametro
   gpioToggle( led );
}

int main( void )
{
   boardInit();

   // Inicializar el conteo de Ticks con resolucion de 50ms (se ejecuta
   // periodicamente una interrupcion cada 50ms que incrementa un contador de
   // Ticks obteniendose una base de tiempos).
   tickInit( 50 );

   // Se agrega ademas un "Tick Callback" nombrado myTickCallback. 
   // El tick callback es simplemente una funcion que se ejecutara 
   // periodicamente con cada interrupcion de Tick.
   // Tambien es nombrado tick hook porque "se engancha" del tick.
   // El segundo parametro es el parametro que recibe la funcion myTickCallback
   // al ejecutarse. En este ejemplo se utiliza para pasarle el led a destellar.
   tickCallbackSet( myTickCallback, (void*)LEDR );

   delay(1000);
   gpioWrite( LEDR, OFF );
 
   while(1) {

      // Voy cambiando el led que destella
	  tickCallbackSet( myTickCallback, (void*)LEDG );
      delay(1000);
	  gpioWrite( LEDG, OFF );

      tickCallbackSet( myTickCallback, (void*)LEDB );
      delay(1000);
	  gpioWrite( LEDB, OFF );

      tickCallbackSet( myTickCallback, (void*)LED1 );
      delay(1000);
	  gpioWrite( LED1, OFF );

      tickCallbackSet( myTickCallback, (void*)LED2 );
      delay(1000);
	  gpioWrite( LED2, OFF );

      tickCallbackSet( myTickCallback, (void*)LED3 );
      delay(1000);
	  gpioWrite( LED3, OFF );

      tickCallbackSet( myTickCallback, (void*)LEDR );
      delay(1000);
	  gpioWrite( LEDR, OFF );
   }

   return 0 ;
}