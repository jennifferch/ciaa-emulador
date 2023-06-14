#include "sapi.h"

int main(void) {

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Variable de Retardo no bloqueante */
   delay_t delay;

   /* Inicializar Retardo no bloqueante con tiempo en milisegundos
      (500ms = 0,5s) */
   delayConfig( &delay, 500 );

   uint8_t led = OFF;
   uint8_t valor = 0;

    /* ------------- REPETIR POR SIEMPRE ------------- */
    while (1) {
      /* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
      if ( delayRead( &delay ) ){
         if( !led )
            led = ON;
         else
            led = OFF;
         gpioWrite( LEDB, led );
      }

      valor = !gpioRead( TEC4 );
      gpioWrite( LED3, valor );
    }
}
