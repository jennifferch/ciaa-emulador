/*============================================================================
 Copyright (c) 2018, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2018/05/18
 Version: 1.0
============================================================================*/

#include "sapi.h"

#define LED_ROJO     LED2
#define LED_AMARILLO LED1
#define LED_VERDE    LEDG

void ledsInit( void );
void ledOn( int32_t pin );
void ledOff( int32_t pin );

// FSM DECLARATIONS

// FSM state names
typedef enum{
   ROJO,
   ROJO_AMARILLO,
   AMARILLO,
   VERDE,
} fsmSemaphoreState_t;

// FSM functions
void fsmSemaphoreError( void );
void fsmSemaphoreInit( void );
void fsmSemaphoreUpdate( void );

// Variable that hold the current state
fsmSemaphoreState_t fsmSemaphoreState;

int main( void )
{
   // ----- Setup -----------------------------------
   fsmSemaphoreInit();

   // ----- Repeat for ever -------------------------
   while(1){
      fsmSemaphoreUpdate();
	  delay(1000);
   }
   return 0;
}

// FSM Error Handler Function
void fsmSemaphoreError( void )
{
   // Error handler, example, restart FSM:
   fsmSemaphoreState = ROJO;
}

// FSM Initialize Function
void fsmSemaphoreInit( void )
{
   boardInit();
   ledsInit();
   fsmSemaphoreState = ROJO;   // Set initial state
}

// FSM Update Sate Function
void fsmSemaphoreUpdate( void )
{
   static uint32_t contador = 0;
   
   switch( fsmSemaphoreState ){

      case ROJO:         
         // UPDATE OUTPUTS
         ledOn( LED_ROJO );
         ledOff( LED_AMARILLO );
         ledOff( LED_VERDE ); 
         
         // CHECK TRANSITION CONDITIONS
         contador++;
         if( contador >= 3 ){
            fsmSemaphoreState = ROJO_AMARILLO;
            contador = 0;
         }
      break;
      
      case ROJO_AMARILLO:            
         // UPDATE OUTPUTS
         ledOn( LED_ROJO );
         ledOn( LED_AMARILLO );
         ledOff( LED_VERDE ); 
         
         // CHECK TRANSITION CONDITIONS
         contador++;
         if( contador >= 1 ){
            fsmSemaphoreState = VERDE;
            contador = 0;
         }
      break;
      
      case VERDE:         
         // UPDATE OUTPUTS
         ledOff( LED_ROJO );
         ledOff( LED_AMARILLO );
         ledOn( LED_VERDE ); 
         
         // CHECK TRANSITION CONDITIONS
         contador++;
         if( contador >= 2 ){
            fsmSemaphoreState = AMARILLO;
            contador = 0;
         }
      break;
      
      case AMARILLO:
         // UPDATE OUTPUTS
         ledOff( LED_ROJO );
         ledOn( LED_AMARILLO );
         ledOff( LED_VERDE ); 
         
         // CHECK TRANSITION CONDITIONS
         contador++;
         if( contador >= 1 ){
            fsmSemaphoreState = ROJO;
            contador = 0;
         }
      break;

      default:
         fsmSemaphoreError();
      break;
   }
}

// LEDs

void ledsInit( void )
{
   gpioInit( LED_ROJO, GPIO_OUTPUT );
   gpioInit( LED_AMARILLO, GPIO_OUTPUT );
   gpioInit( LED_VERDE, GPIO_OUTPUT );
}

void ledOn( int32_t pin )
{
   gpioWrite( pin, ON );
}

void ledOff( int32_t pin )
{
   gpioWrite( pin, OFF );
}