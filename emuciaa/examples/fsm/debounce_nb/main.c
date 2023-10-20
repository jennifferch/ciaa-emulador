/*============================================================================
 Copyright (c) 2018, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2018/05/18
 Version: 1.0
============================================================================*/

#include "sapi.h"

typedef enum{
   STATE_BUTTON_UP,
   STATE_BUTTON_DOWN,
   STATE_BUTTON_FALLING,
   STATE_BUTTON_RISING
} fsmButtonState_t;

void fsmButtonError( void );
void fsmButtonInit( void );
void fsmButtonUpdate( gpioMap_t tecla );

void buttonPressed( void );
void buttonReleased( void );

fsmButtonState_t fsmButtonState;

int main(void)
{        
   // Inicializo la placa
   boardInit();
   
   // Inicializo temporizacion y MEF Boton
   delay_t actualizarMefBoton;   
   delayInit( &actualizarMefBoton, 40 );   
   fsmButtonInit();
   
   while(1) {

      // Actualizo MEF Boton cada tiempo actualizarMefBoton
      if( delayRead(&actualizarMefBoton) ){
         fsmButtonUpdate(TEC1);
      }

	  delay(1); // Es necesario un minimo delay en el while(1) para que no se rompa el emulador
   }
   return 0;
}


void buttonPressed( void )
{
   static uint8_t cont = 0;
   gpioWrite(LEDR, OFF);
   gpioWrite(LEDG, OFF);
   gpioWrite(LEDB, ON);
   if(cont>5){
      gpioWrite(LEDR, OFF);
      gpioWrite(LEDG, ON);
      gpioWrite(LEDB, OFF);
   }
   cont++;
}

void buttonReleased( void )
{
   static uint8_t cont = 0;
   gpioWrite(LEDR, ON);
   gpioWrite(LEDG, OFF);
   gpioWrite(LEDB, OFF);
   if(cont>10){
      gpioWrite(LEDR, OFF);
      gpioWrite(LEDG, OFF);
      gpioWrite(LEDB, OFF);
   }
   cont++;
}

void fsmButtonError( void )
{
   fsmButtonState = BUTTON_UP;
}

void fsmButtonInit( void )
{
   fsmButtonState = BUTTON_UP;  // Set initial state
}

// FSM Update Sate Function
void fsmButtonUpdate( gpioMap_t tecla )
{
   static bool_t flagFalling = FALSE;
   static bool_t flagRising = FALSE;
   
   static uint8_t contFalling = 0;
   static uint8_t contRising = 0;

   switch( fsmButtonState ){

      case STATE_BUTTON_UP:
         // CHECK TRANSITION CONDITIONS
         if( !gpioRead(tecla) ){
            fsmButtonState = STATE_BUTTON_FALLING;
         }
      break;

      case STATE_BUTTON_DOWN:
         // CHECK TRANSITION CONDITIONS
         if( gpioRead(tecla) ){
            fsmButtonState = STATE_BUTTON_RISING;
         }
      break;

      case STATE_BUTTON_FALLING:
         // ENTRY
         if( flagFalling == FALSE ){
            flagFalling = TRUE;
            gpioWrite(LED1, ON);
            break;
         }
         // CHECK TRANSITION CONDITIONS
         if( !gpioRead(tecla) ){
            fsmButtonState = STATE_BUTTON_DOWN;
            buttonPressed();
         } else{
            fsmButtonState = STATE_BUTTON_UP;
         }
         // EXIT
         if( fsmButtonState != STATE_BUTTON_FALLING ){
            flagFalling = FALSE;
            gpioWrite(LED1, OFF);
         }
      break;

      case STATE_BUTTON_RISING:
         // ENTRY
         if( flagRising == FALSE ){
            flagRising = TRUE;
            gpioWrite(LED2, ON);
            break;
         }
         // CHECK TRANSITION CONDITIONS
         if( gpioRead(tecla) ){
            fsmButtonState = STATE_BUTTON_UP;
            buttonReleased();
         } else{
            fsmButtonState = STATE_BUTTON_DOWN;
         }
         // EXIT
         if( fsmButtonState != STATE_BUTTON_RISING ){
            flagRising = FALSE;
            gpioWrite(LED2, OFF);
         }
      break;

      default:
         fsmButtonError();
      break;
   }
}