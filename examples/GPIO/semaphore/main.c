#include "sapi.h"

// EDU-CIAA-NXP V1.1 primer tirada (abajo dice ASSISI)
#define edu_ciaa_nxp_v_1_1_0

// EDU-CIAA-NXP V1.1 segunda tirada (abajo dice ASEMBLI)
//#define edu_ciaa_nxp_v_1_1_1

#if defined(edu_ciaa_nxp_v_1_1_0)
   #define LUZ_ROJA     LED2
   #define LUZ_AMARILLA LED1
   #define LUZ_VERDE    LEDG
#elif defined(edu_ciaa_nxp_v_1_1_1)
   #define LUZ_ROJA     LED1
   #define LUZ_AMARILLA LED2
   #define LUZ_VERDE    LED3
#endif

#define TIEMPO_EN_ROJO     3000 // ms
#define TIEMPO_EN_AMARILLO 1000 // ms
#define TIEMPO_EN_VERDE    2000 // ms


int main() {
   // ----- Setup -----------------------------------
   boardInit();

   // ----- Repeat for ever -------------------------
   while( true ) {

      gpioWrite( LUZ_ROJA, ON );
      delay( TIEMPO_EN_ROJO );
      gpioWrite( LUZ_ROJA, OFF );
      
      gpioWrite( LUZ_AMARILLA, ON );
      delay( TIEMPO_EN_AMARILLO );
      gpioWrite( LUZ_AMARILLA, OFF );
      
      gpioWrite( LUZ_VERDE, ON );
      delay( TIEMPO_EN_VERDE );
      gpioWrite( LUZ_VERDE, OFF );
      
      gpioWrite( LUZ_AMARILLA, ON );
      delay( TIEMPO_EN_AMARILLO );
      gpioWrite( LUZ_AMARILLA, OFF ); 
   }
}
