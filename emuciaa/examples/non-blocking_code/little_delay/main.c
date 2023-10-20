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
   uint32_t contador = 0;

   while(1) {

      tec1 = !gpioRead(TEC1);
      gpioWrite( LEDB, tec1 );

      delay(10);
      contador++;
      if( contador >= 50 ){
         gpioToggle( LED1 );
         contador = 0;
      }
   }

   return 0;
}