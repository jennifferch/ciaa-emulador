/*============================================================================
 Copyright (c) 2018, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2018/10/04
 Version: 1.0
============================================================================*/

// The maximum number of tasks required at any one time during the execution
// of the program. MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCHEDULER_MAX_TASKS   (3)

#include "sapi.h"                     // <= sAPI header

#include "seos_pont_2014_isr.h"       // <= dispatcher and task management header
#include "seos_pont_2014_scheduler.h" // <= scheduler and system initialization header

void tarea1( void* taskPtr );
void tarea2( void* taskPtr );
void tarea3( void* taskPtr );

int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------
   boardInit();

   // FUNCION que inicializa el planificador de tareas
   schedulerInit();


   // Se agrega la tarea tarea1 al planificador
   schedulerAddTask( tarea1, // funcion de tarea a agregar
                     0,      // parametro de la tarea
                     0,      // offset de ejecucion en ticks
                     10      // periodicidad de ejecucion en ticks
                   );

   // Se agrega la tarea tarea2 al planificador
   schedulerAddTask( tarea2, 0, 1, 50 );

   // Se agrega la tarea tarea3 al planificador
   schedulerAddTask( tarea3, 0, 2, 100 );

   // FUNCION que inicializa la interrupcion que ejecuta el planificador de
   // tareas con tick cada 10 ms.
   schedulerStart( 10 );

   // ---------- REPETIR POR SIEMPRE --------------------------
   while(1) {
      // Se despachan (ejecutan) las tareas marcadas para su ejecucion.
      // Luego se pone el sistema en bajo consumo hasta que ocurra la
      // proxima interrupcion, en este caso la de Tick.
      // Al ocurrir la interrupcion de Tick se ejecutara el planificador
      // que revisa cuales son las tareas a marcar para su ejecucion.
      schedulerDispatchTasks();

      delay(1); // Es necesario agregar un delay, sino, el navegador se bloquea.
   }

   return 0;
}

void tarea1( void* taskPtr ){
   gpioToggle( LEDB );
}

void tarea2( void* taskPtr ){
   gpioToggle( LED1 );
}

void tarea3( void* taskPtr ){
   gpioToggle( LED2 );
}