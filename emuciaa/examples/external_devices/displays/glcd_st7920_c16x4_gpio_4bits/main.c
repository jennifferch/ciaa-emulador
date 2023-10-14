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
   displayInit( DISPLAY_TYPE_GLCD_ST7920, DISPLAY_CONNECTION_GPIO_4BITS );
   displayModeWrite( DISPLAY_MODE_CHAR );

   while( true ) {  

      displayCharPositionWrite( 0, 1 );
      displayStringWrite( "Hi EDU-CIAA-NXP" );
      delay(1000);

      displayCharPositionWrite( 1, 2 );
      displayStringWrite( "How are you?" );
      delay(1000);

	  displayClear();
      delay(500);
   }

   return 0;
}