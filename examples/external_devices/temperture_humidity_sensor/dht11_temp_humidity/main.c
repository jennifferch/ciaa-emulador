#include "sapi.h"

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void) {

    boardConfig(); // Inicializar y configurar la plataforma
    // Inicializo el sensor DHT11
    dht11Init(GPIO1);
   
    // Variables para almacenar humedad y temperatura
    float humidity = 0, temperature = 0;
    while (TRUE) {
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
}