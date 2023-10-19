/*============================================================================
 Copyright (c) 2016, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2016-07-03
 Version: 1.0
============================================================================*/

#include "sapi.h"

static char uartBuff[10]; // Buffer

// C++ version 0.4 char* style "itoa":
// Written by Lukas Chmela
// Released under GPLv3.
char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}

// Enviar fecha y hora en formato "DD/MM/YYYY, HH:MM:SS"
void showDateAndTime( rtc_t * rtc ){

   // Conversion de entero a ascii con base decimal de mday
   itoa( (int) (rtc->mday), (char*)uartBuff, 10 ); // 10 significa decimal

   // Envio el dia
   if( (rtc->mday)<10 ) {
      uartWriteByte( UART_USB, '0' );
   }
   uartWriteString( UART_USB, uartBuff );

   // Envio '/'
   uartWriteByte( UART_USB, '/' );

   // Conversion de entero a ascii con base decimal de month
   itoa( (int) (rtc->month), (char*)uartBuff, 10 );
 
   // Envio el mes
   if( (rtc->month)<10 ) {
      uartWriteByte( UART_USB, '0' );
   }
   uartWriteString( UART_USB, uartBuff );

   // Envio '/'
   uartWriteByte( UART_USB, '/' );

   // Conversion de entero a ascii con base decimal de year
   itoa( (int) (rtc->year), (char*)uartBuff, 10 );

   // Envio el year
   if( (rtc->year)<10 ) {
      uartWriteByte( UART_USB, '0' );
   }
   uartWriteString( UART_USB, uartBuff );

   // Envio ", "
   uartWriteString( UART_USB, ", ");

   // Conversion de entero a ascii con base decimal de hour
   itoa( (int) (rtc->hour), (char*)uartBuff, 10 );

   // Envio la hora
   if( (rtc->hour)<10 ) {
      uartWriteByte( UART_USB, '0' );
   }
   uartWriteString( UART_USB, uartBuff );

   // Envio ':'
   uartWriteByte( UART_USB, ':' );

   // Conversion de entero a ascii con base decimal de min
   itoa( (int) (rtc->min), (char*)uartBuff, 10 );

   // Envio los minutos
   if( (rtc->min)<10 ) {
      uartWriteByte( UART_USB, '0' );
   }
   uartWriteString( UART_USB, uartBuff );

   // Envio ':'
   uartWriteByte( UART_USB, ':' );

   // Conversion de entero a ascii con base decimal de sec
   itoa( (int) (rtc->sec), (char*)uartBuff, 10 );

   // Envio los segundos
   if( (rtc->sec)<10 ) {
      uartWriteByte( UART_USB, '0' );
   }
   uartWriteString( UART_USB, uartBuff );

   // Envio un "Enter"
   uartWriteString( UART_USB, "\r\n");
}

int main(void){

   boardInit();
   uartInit( UART_USB, 115200 ); // Inicializar UART_USB a 115200 baudios

   rtc_t rtc; // Estructura RTC

   // Completar estructura RTC
   rtc.year = 2016;
   rtc.month = 7;
   rtc.mday = 3;
   rtc.wday = 1;
   rtc.hour = 19;
   rtc.min = 00;
   rtc.sec= 0;

   bool_t val = 0;
   uint8_t i = 0;

   uartWriteString( UART_USB, "Inicializar RTC\r\n" );
   rtcInit(); // Inicializar RTC
 
   uartWriteString( UART_USB, "Establecer fecha y hora\r\n" );
   rtcWrite( &rtc ); // Establecer fecha y hora

   delay(2000); // El RTC tarda en setear la hora, por eso el delay

   while(1) {

      val = rtcRead( &rtc ); // Leer fecha y hora
      
	  // Mostrar fecha y hora en formato "DD/MM/YYYY, HH:MM:SS"
      showDateAndTime( &rtc );

      delay(1000);

   }

   return 0 ;
}