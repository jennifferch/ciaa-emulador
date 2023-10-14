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

   delay_t delay;  // Variable de Retardo no bloqueante

   // Inicializar Retardo no bloqueante con tiempo en milisegundos
   // (500ms = 0,5s)
   delayInit( &delay, 500 );
   
   bool_t valor = 0;

   while(1) {

      // delayRead() retorna true cuando se cumple el tiempo del retardo
      if ( delayRead( &delay ) ){
         gpioToggle( LEDB ); // Invertir el estado del LEDB
      }

      valor = !gpioRead( TEC4 );
      gpioWrite( LED3, valor );

   }

   return 0 ;
}
