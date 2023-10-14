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

   delay_t delay;
   delayInit( &delay, 500 );

   int8_t i = 3;
   uint8_t sequence = 0;

   while(1) {

      if( !gpioRead(TEC1) ) {       // Secuencia hacia izquierda <--
         sequence = 0;
      }
      if( !gpioRead(TEC2) ) {
         delayWrite( &delay, 150 ); // Velocidad rapida
      }
      if( !gpioRead(TEC3) ) {
         delayWrite( &delay, 750 ); // Velocidad lenta
      }
      if( !gpioRead(TEC4) ) {       // Secuencia hacia derecha -->
         sequence = 1;
      }

      if( delayRead(&delay) ){
         if ( !sequence ){
            i--;
         } else{
            i++;
         }
      }

      if( i == 0 ) {
         gpioWrite( LEDB, ON );
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, OFF );
      }
      if( i == 1 ) {
         gpioWrite( LEDB, OFF );
         gpioWrite( LED1, ON );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, OFF );
      }
      if( i == 2 ) {
         gpioWrite( LEDB, OFF );
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, ON );
         gpioWrite( LED3, OFF );
      }
      if( i == 3 ) {
         gpioWrite( LEDB, OFF );
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, ON );
      }

      if( i < 0 ) {
         i = 3;
      }
      if( i > 3 ) {
         i = 0;
      }

   }

   return 0 ;
}

/*==================[end of file]============================================*/