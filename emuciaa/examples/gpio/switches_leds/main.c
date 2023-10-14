/*============================================================================
 Copyright (c) 2016, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2016-04-26
 Version: 1.0
============================================================================*/

#include "sapi.h"

int main(void){

   boardInit();

   gpioInit( GPIO0, GPIO_OUTPUT ); // Configurar pin GPIO0 como Salida

   bool_t valor;  // Variable para almacenar el valor de tecla leido

   while(1) {

      // Leer TEC1, invertir el resultado logico y guardar en valor
      valor = !gpioRead( TEC1 ); 
      gpioWrite( LEDB, valor ); // Escribir el pin de salida LEDB con valor

      valor = !gpioRead( TEC2 );
      gpioWrite( LED1, valor );

      valor = !gpioRead( TEC3 );
      gpioWrite( LED2, valor );

      valor = !gpioRead( TEC4 );
      gpioWrite( LED3, valor );
      gpioWrite( GPIO0, valor );

   }

   return 0 ;
}