/*============================================================================
 Copyright (c) 2017, Sebastian Pablo Bedin.
 Copyright (c) 2018, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2017/11/13
 Version: 1.0
============================================================================*/

#include "sapi.h"

int main( void )
{
   boardInit();

   dht11Init( GPIO1 ); // Inicializo el sensor DHT11

   // Variables para almacenar humedad y temperatura
   float humidity = 0, temperature = 0;

   while(1) {

      // Lectura del sensor DHT11, devuelve true si pudo leer correctamente
      if( dht11Read(&humidity, &temperature) ) {
         // Si leyo bien prendo el LEDG y enciendo el LEDR
         gpioWrite( LEDG, ON );
         gpioWrite( LEDR, OFF );
         // Informo los valores de los sensores
         printf( "Temperatura: %.2f grados C.\r\n", temperature );
         printf( "Humedad: %.2f  %.\r\n\r\n", humidity );
      } else {
         // Si leyo mal apago el LEDG y enciendo el LEDR
         gpioWrite( LEDG, OFF );
         gpioWrite( LEDR, ON );
         // Informo el error de lectura
         printf( "Error al leer DHT11.\r\n\r\n");
      }

      delay(1000); // Espero 1 segundo.
   }

   return 0;
}

/*
DHT11 connections:
                                                DHT11
                                           +--------------+
             EDU-CIAA-NXP +3.3V <--> 1 ----| +++  +++  +++|
   EDU-CIAA-NXP GPIO1 (pull-up) <--> 2 ----| +++  +++  +++|
                 (SIN CONEXION) <--> 3 ----| +++  +++  +++|
               EDU-CIAA-NXP GND <--> 4 ----| +++  +++  +++|
                                           +--------------+

                                           DHT11 on a board
                                          +----------------+
                                          |    +-----------+--+
             EDU-CIAA-NXP GPIO1 <--> S ----o --| +++  +++  +++|
             EDU-CIAA-NXP +3.3V <--> + ----o --| +++  +++  +++|
              EDU-CIAA-NXP GND  <--> - ----o --| +++  +++  +++|
                                          |  --| +++  +++  +++|
                                          |    +-----------+--+
                                          +----------------+
*/