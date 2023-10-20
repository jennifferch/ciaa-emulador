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

   tickInit(50); // Iniciar conteo de ticks por interrupcion cada 50 ms

   bool_t tec1 = 0;
   tick_t tiempoEnTicks = 0;

   while(1) {

      tec1 = !gpioRead(TEC1);
      gpioWrite( LEDB, tec1 );

      tiempoEnTicks = tickRead(); // Leo el conteo de ticks
      if( tiempoEnTicks >= 50 ){
         gpioToggle( LED1 );
         tickWrite(0); // Reinicio el conteo de ticks
      }

	  delay(10); // Es necesario un minimo delay en el while(1) para que no se rompa el emulador
   }

   return 0;
}