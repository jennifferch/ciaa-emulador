/*============================================================================
 Copyright (c) 2023, Eric Pernia
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2023/09/10
 Version: 1.0
============================================================================*/

#include "sapi.h"

int main( void )
{
   boardInit();
   uartInit( UART_USB, 115200 ); // Inicializar UART_USB a 115200 baudios

   while( true ) {
      uartWriteByte( UART_USB, 'H' );  // Enviar un byte
      uartWriteString( UART_USB, "ola\r\n" ); // Enviar un string (funcion bloqueante)
	  
	  delay(1000);
   }

   return 0;
}