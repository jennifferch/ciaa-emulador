/*============================================================================
 Copyright (c) 2019, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date:  2019/04/30
 Version: 1.0
============================================================================*/

#include "sapi.h"

int main( void )
{
   boardInit();

   rtc_t rtc; // Crear estructura RTC

   // Completar estructura RTC
   rtc.year = 2019;
   rtc.month = 4;
   rtc.mday = 30;
   rtc.wday = 3;
   rtc.hour = 12;
   rtc.min = 15;
   rtc.sec= 50;
  
   rtcInit(); // Inicializar RTC 
   rtcWrite( &rtc );

   while(1) {

      // Leer fecha y hora
      rtcRead( &rtc ); // en la variable de estructura rtc te queda la 
                       // fecha/hora actual

      // Envio por Salida estandar de forma humanamente legible
      // %02d == %d y ademas completa con 2 0 a izquierda
      printf( "%02d/%02d/%04d, %02d:%02d:%02d\r\n", 
              rtc.mday, rtc.month, rtc.year, 
              rtc.hour, rtc.min, rtc.sec );
      // Nota: printf() usa sAPI UART_USB (USART2 de EDU-CIAA-NXP) 
	  //       con 115200, 8N1 

      delay(1000);
   }

   return 0 ;
}