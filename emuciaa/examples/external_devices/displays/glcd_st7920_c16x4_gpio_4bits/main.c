/*============================================================================
 Copyright (c) 2021, Eric Pernia, Pablo Gomez, Ariel Lutenberg
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2021/05/18
 Version: 1.0
============================================================================*/

#include "sapi.h"

int main( void )
{
   boardInit();

   // Inicializo GLCD basado en el controlador ST7920 con conexion por GPIOs en 4 bits
   displayInit( DISPLAY_TYPE_GLCD_ST7920, DISPLAY_CONNECTION_GPIO_4BITS );

   // En el GLCD es necesario establecer el mode, en este caso modo caracteres
   displayModeWrite( DISPLAY_MODE_CHAR );

   while(1) {

      displayCharPositionWrite( 2, 1 ); // Posiciona el cursor 2 en x, 1 en y
      displayStringWrite( "EDU-CIAA-NXP" ); // Escribir String en pantalla
      delay(1000);

      displayCharPositionWrite( 2, 2 ); // Posiciona el cursor 2 en x, 2 en y
      displayStringWrite( "Como estas?" );
      delay(1000);

	  displayClear(); // Limpiar pantalla
      delay(500);
   }

   return 0;
}