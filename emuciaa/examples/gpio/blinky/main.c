/*============================================================================
 Copyright (c) 2016, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2016/04/26
 Version: 1.0
============================================================================*/

#include "sapi.h"  // Biblioteca sAPI

int main( void )
{
   boardInit();  // Inicializar la placa

   while(1) {

      gpioWrite( LEDB, ON );   // Encender LED Azul de la placa

      delay(500);              // Esperar 500 ms

      gpioWrite( LEDB, OFF );  // Apagar LED Azul de la placa

      delay(500);              // Esperar 500 ms
   }

   return 0;
}