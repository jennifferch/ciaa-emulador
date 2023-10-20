/*============================================================================
 Copyright (c) 2016, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2016/08/15
 Version: 1.0
============================================================================*/

#include "sapi.h"

// PERIODICIDAD DE LAS TAREAS
#define TASK1_PERIODICITY   1
#define TASK2_PERIODICITY  10
#define TASK3_PERIODICITY  20

// Contador de ticks de cada tarea
static tick_t task1Counter = 0;
static tick_t task2Counter = 0;
static tick_t task3Counter = 0;

/* ------- TAREAS, PLANIFICADOR y DESPACHADOR ------- */

// FUNCION que realiza la tarea 1.
// Esta tarea lee una tecla cada 40ms y escribe su valor
// en LEDB 
static void task1(void){
   gpioWrite( LED1, !gpioRead(TEC2) );
}

// FUNCION que realiza la tarea 2.
// Esta tarea hace destellar el LED2 (blink) cada
// 250ms.
static void task2(void){
   gpioToggle( LED2 );
}

// FUNCION que realiza la tarea 3.
// Esta tarea hace destellar el LED3 (blink) cada
// 500ms.
static void task3(void){
   gpioToggle( LED3 );
}

// FUNCION que contiene el planificador y despachador de tareas.
static void scheduleAndDispatchTasks(void)
{
   // Tarea planificada cada TASK1_PERIODICITY*10 ms
   if( task1Counter++ == TASK1_PERIODICITY ){
      // Despacho de la tarea (la ejecuta)
      task1();
      // Resetea el contador de la tarea
      task1Counter = 0;
   }

   // Tarea planificada cada TASK2_PERIODICITY*10 ms
   if( task2Counter++ == TASK2_PERIODICITY ){
      // Despacho de la tarea (la ejecuta)
      task2();
      // Resetea el contador de la tarea
      task2Counter = 0;
   }

   // Tarea planificada cada TASK3_PERIODICITY*10 ms
   if( task3Counter++ == TASK3_PERIODICITY ){
      // Despacho de la tarea (la ejecuta)
      task3();
      // Resetea el contador de la tarea
      task3Counter = 0;
   }
}

// FUNCION que se ejecuta cada vez que ocurre un Tick.
static void myTickHook( void *ptr ){
   scheduleAndDispatchTasks();
}

int main( void )
{
   /* ------------- INICIALIZACIONES ------------- */

   boardInit();

   // Inicializar el conteo de Ticks con resolucion de 10 ms (se ejecuta
   // periodicamente una interrupcion cada 10 ms que incrementa un contador
   // de Ticks obteniendose una base de tiempos).
   tickInit( 10 );
   tickCallbackSet( myTickHook, NULL );

   /* ----- REPETIR POR SIEMPRE (SUPER LOOP) ----- */

   while(1) {

      // No se hace nada en el Super loop, simplemente se pone el sistema en
      // bajo consumo hasta que ocurra la proxima interrupcion, en este caso
      // la de Tick. Comente esta duncion y note el aumento de temperatura
      // del microcontrolador
      sleepUntilNextInterrupt();

      // Es necesario agregar un delay, sino, el navegador se bloquea.
      delay(1);
   }

   return 0 ;
}

/* SEOS del inges Simple Embedded Operating System.
 * Ejemplo de Planificador de tareas cooperativo disparado por tiempo
 * (Time-Triggered), con el planificador (scheduler) y despachador de tareas
 * (dispatcher) todo junto que se ejecuta en una Interrupcion periodica de
 * tiempo.
 * Solamente la primer tarea es Real-Time. La suma de la duracion de todas las
 * tareas debe ser menor a 1 Tick (1ms en el ejemplo), si alguna se excede un
 * poco de tiempo el sistema va a fallar, ya que se perdera temporizacion.
 * Las tareas deben ser NO bloqueantes.
 */