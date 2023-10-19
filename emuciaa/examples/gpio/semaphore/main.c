/*============================================================================
 Copyright (c) 2019, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2019/05/03
 Version: 1.0
============================================================================*/

#include "sapi.h"

// Elegir una placa EDU-CIAA-NXP:

#define edu_ciaa_nxp_v_1_1_0 // EDU-CIAA-NXP V1.1.0 (debajo dice ASSISI)

//#define edu_ciaa_nxp_v_1_1_1 // EDU-CIAA-NXP V1.1.1 (debajo dice ASEMBLI)

#if defined(edu_ciaa_nxp_v_1_1_0)
   #define LUZ_ROJA     LED2
   #define LUZ_AMARILLA LED1
   #define LUZ_VERDE    LEDG
#elif defined(edu_ciaa_nxp_v_1_1_1)
   #define LUZ_ROJA     LED1
   #define LUZ_AMARILLA LED2
   #define LUZ_VERDE    LED3
#endif

#define TIEMPO_EN_ROJO     3000 // 3000 ms
#define TIEMPO_EN_AMARILLO 1000 // 1000 ms
#define TIEMPO_EN_VERDE    2000 // 2000 ms

int main( void )
{
   boardInit();

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

   return 0;
}