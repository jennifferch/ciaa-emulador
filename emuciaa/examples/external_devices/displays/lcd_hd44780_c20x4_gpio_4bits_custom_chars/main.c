/*============================================================================
 Copyright (c) 2021, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2021/05/18
 Version: 1.0
============================================================================*/

#include "sapi.h"

// Temperature icon
uint8_t tempIconChar[8] = {
   0b01110,
   0b01010,
   0b01010,
   0b01110,
   0b01110,
   0b10111,
   0b11111,
   0b01110
};

// Degree symbol
uint8_t degreeSymbolChar[8] = { 
   0b01110,
   0b01010,
   0b01110,
   0b00000,
   0b00000,
   0b00000,
   0b00000,
   0b00000
};

// Humidity icon
uint8_t humIconChar[8] = { 
   0b00100,
   0b00100,
   0b01110,
   0b10111,
   0b10111,
   0b10011,
   0b01110,
   0b00000
};

// Wind velocity icon
uint8_t windIconChar[8] = {
   0b00111,
   0b11100,
   0b00000,
   0b00111,
   0b11100,
   0b00000,
   0b00111,
   0b11100
};

enum{
   TEMP_ICON_CHAR     = 0,
   DEGREE_SYMBOL_CHAR = 1,
   HUM_ICON_CHAR      = 2,
   WIND_ICON_CHAR     = 3,
};

int main( void )
{
   boardInit();
   displayInit( DISPLAY_TYPE_LCD_HD44780, DISPLAY_CONNECTION_GPIO_4BITS );
   
   displayCustomCharCreate( TEMP_ICON_CHAR, tempIconChar ); // Crear caracter en indice TEMP_CHAR=0, con bitmap tempChar
   displayCustomCharCreate( DEGREE_SYMBOL_CHAR, degreeSymbolChar );
   displayCustomCharCreate( HUM_ICON_CHAR, humIconChar );
   displayCustomCharCreate( WIND_ICON_CHAR, windIconChar );

   char tempString[] = "25";
   char humString[]  = "50";
   char windString[] = "10";

   while(1) {
	  
      displayCharPositionWrite( 3, 1 );

      displayStringWrite( "Tmp" );
      displayCustomCharWrite( TEMP_ICON_CHAR );

      displayStringWrite( " Hum" );
      displayCustomCharWrite( HUM_ICON_CHAR );

      displayStringWrite( " Vie" );
      displayCustomCharWrite( WIND_ICON_CHAR );

      displayCharPositionWrite( 3, 2 );

      displayStringWrite( tempString );
      displayCustomCharWrite( DEGREE_SYMBOL_CHAR );
      displayStringWrite( "C" );

      displayCharPositionWrite( 8, 2 );
      displayStringWrite( humString );
      displayStringWrite( "%" );

      displayCharPositionWrite( 13, 2 );
      displayStringWrite( windString );
      displayStringWrite( "km/h" );

      delay(3000);

      displayClear();
      delay(1000);
   }

   return 0;
}

// ----------------------
// "                    "
// "   Tmp* Hum* Vie*   "
// "   25*C 50%  10km/h "
// "                    "
// ----------------------

// * means custom char