/*============================================================================
 Copyright (c) 2021, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2021/05/18
 Version: 1.0
============================================================================*/

#include "sapi.h"

int main( void )
{
   boardInit();

   // Inicializo LCD basado en el controlador HD44780 con conexion por GPIOs en 4 bits
   displayInit( DISPLAY_TYPE_LCD_HD44780, DISPLAY_CONNECTION_GPIO_4BITS );

   while(1) {

      displayCharPositionWrite( 1, 1 ); // Posiciona el cursor 1 en x, 1 en y
      displayStringWrite( "Hola EDU-CIAA-NXP" ); // Escribir String en pantalla
      delay(1000);

      displayCharPositionWrite( 4, 2 ); // Posiciona el cursor 4 en x, 2 en y
      displayStringWrite( "Como estas?" );
      delay(1000);

	  displayClear(); // Limpiar pantalla
      delay(500);
   }

   return 0;
}