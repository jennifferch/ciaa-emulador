/*============================================================================
 Copyright (c) 2016, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2016/08/16
 Version: 1.0
============================================================================*/

#include "sapi.h"

// FUNCION que contiene el planificador de tareas.
void seosScheduleTasks( void *ptr );

// FUNCION que contiene el despachador de tareas.
void seosDispatchTask( void );

// FUNCION que inicializa la interrupcion que ejecuta
// el planificador de tareas.
void seosInterruptInit( tick_t tickRateMs );


// FUNCION que inicializa las tareas.
void tasksInit(void);

// FUNCION que realiza la tarea 1.
void task1(void);

// FUNCION que realiza la tarea 2.
void task2(void);

// FUNCION que realiza la tarea 3.
void task3(void);


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializacion de las tareas. */
   tasksInit();

   /* Inicializacion de la interrpción periódica
      del sistema operativo cada 1ms. */
   seosInterruptInit(1);

   /* ----- REPETIR POR SIEMPRE (SUPER LOOP) ----- */

   while(1) {

      /* Se despachan (ejecutan) las tareas marcadas para su ejecucion. */
      seosDispatchTask();

      /* Se pone el sistema en bajo consumo hasta que ocurra la proxima
         interrupcion, en este caso la de Tick. */
      sleepUntilNextInterrupt();

      /* Al ocurrir la interrupcion de Tick se ejecutara el planificador
         que revisa cuales son las tareas a marcar para su ejecucion. */

	  delay(1); // Es necesario un minimo delay en el while(1) para que no se rompa el emulador
   }

   return 0 ;
}


/* ------------ INICIALIZACION DE TAREAS ------------ */

/* FUNCION que inicializa las tareas. */
void tasksInit(void){
   /* Inicializar la placa */
   boardConfig();
}

/* --------------------- TAREAS --------------------- */

/* FUNCION que realiza la tarea 1.
   Esta tarea lee una tecla cada 40ms y escribe su valor
   en LEDG */
void task1(void){
   gpioWrite( LEDG, !gpioRead(TEC1) );
}

/* FUNCION que realiza la tarea 2.
   Esta tarea hace destellar el LED1 (blink) cada
   250ms. */
void task2(void){
   gpioToggle( LED1 );
}

/* FUNCION que realiza la tarea 3.
   Esta tarea hace destellar el LED2 (blink) cada
   500ms. */
void task3(void){
   gpioToggle( LED2 );
}


// PERIODICIDAD DE LAS TAREAS
#define TASK1_PERIODICITY  10
#define TASK2_PERIODICITY  50
#define TASK3_PERIODICITY 100

static tick_t task1Counter = 0;
static tick_t task2Counter = 0;
static tick_t task3Counter = 0;

static tick_t task1RunFlag = 0;
static tick_t task2RunFlag = 0;
static tick_t task3RunFlag = 0;

/* ----------- PLANIFICADOR y DESPACHADOR ----------- */

/* FUNCION que contiene el planificador de tareas. */
void seosScheduleTasks(void *ptr){
   
   /* Tarea planificada cada TASK1_PERIODICITY ms */
   if( task1Counter++ == TASK1_PERIODICITY ){
      /* Planifica la tarea (activa el flag para
         que la ejecute el despachador) */
      task1RunFlag = 1;

      /* Resetea el contador de la tarea */
      task1Counter = 0;
   }

   /* Tarea planificada cada TASK2_PERIODICITY ms */
   if( task2Counter++ == TASK2_PERIODICITY ){
      /* Planifica la tarea (activa el flag para
         que la ejecute el despachador) */
      task2RunFlag = 1;

      /* Resetea el contador de la tarea */
      task2Counter = 0;
   }

   /* Tarea planificada cada TASK3_PERIODICITY ms */
   if( task3Counter++ == TASK3_PERIODICITY ){
      /* Planifica la tarea (activa el flag para
         que la ejecute el despachador) */
      task3RunFlag = 1;

      /* Resetea el contador de la tarea */
      task3Counter = 0;
   }
}

/* FUNCION que contiene el despachador de tareas. */
void seosDispatchTask(void){

   /* Tarea planificada cada TASK1_PERIODICITY ms */
   if( task1RunFlag ){
      /* Si el flag esta en 1 despacha de la tarea 
         (la ejecuta) */
      task1();

      /* Resetea el flag de ejecucion de la tarea */
      task1RunFlag = 0;
   }

   /* Tarea planificada cada TASK2_PERIODICITY ms */
   if( task2RunFlag ){
      /* Si el flag esta en 1 despacha de la tarea 
         (la ejecuta) */
      task2();

      /* Resetea el flag de ejecucion de la tarea */
      task2RunFlag = 0;
   }

   /* Tarea planificada cada TASK3_PERIODICITY ms */
   if( task3RunFlag ){
      /* Si el flag esta en 1 despacha de la tarea 
         (la ejecuta) */
      task3();

      /* Resetea el flag de ejecucion de la tarea */
      task3RunFlag = 0;
   }
}

/* FUNCION que inicializa la interrupcion que ejecuta
   el planificador de tareas. */
void seosInterruptInit( tick_t tickRateMs ){
   /* Inicializar el conteo de Ticks con resolucion de tickRateMs ms (se 
      ejecuta periodicamente una interrupcion cada tickRateMs ms que 
      incrementa un contador de Ticks obteniendose una base de tiempos).
      Se agrega ademas como "tick hook" a la funcion encargada de planificar 
      las tareas seosScheduleTasks(). 
      El tick hook es simplemente una funcion que se ejecutara periodicamente 
      con cada interrupcion de Tick, este nombre se refiere a una funcion 
      "enganchada" a una interrupcion */
   tickInit( 10 );
   tickCallbackSet( seosScheduleTasks, NULL );
}