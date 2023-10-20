/*============================================================================
 Copyright (c) 2018, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2018/10/04
 Version: 1.0
============================================================================*/

// The maximum number of tasks required at any one time during the execution
// of the program. MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCHEDULER_MAX_TASKS   (10)

#include "sapi.h"      // <= sAPI
#include "seos_pont.h" // <= Simple Embedded Operating Sistem (cooperative)

// Funcion que inicializa la tarea
void task1_Init( void );
// Funcion que se ejecuta periodicamente
void task1_Update( void* taskParam );

// Funcion que inicializa la tarea
void task2_Init( void );
// Funcion que se ejecuta periodicamente
void task2_Update( void* taskParam );

// Funcion que inicializa la tarea
void task3_Init( void );
// Funcion que se ejecuta periodicamente
void task3_Update( void* taskParam );

int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardInit();

   task1_Init();
   task2_Init();
   task3_Init();

   // FUNCION que inicializa el planificador de tareas
   schedulerInit();

   // Se agrega la tarea tarea1 al planificador
   schedulerAddTask( task1_Update, // funcion de tarea a agregar
                     0,            // parametro de la tarea
                     0,            // offset de ejecucion en ticks
                     10           // periodicidad de ejecucion en ticks
                   );
   
   schedulerAddTask( task2_Update, 0, 1, 20 );
   schedulerAddTask( task3_Update, 0, 2, 30 );

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

// Funcion que inicializa la tarea
void task1_Init( void ){
   gpioInit( LEDB, GPIO_OUTPUT );
}

// Funcion que se ejecuta periodicamente
void task1_Update( void* taskParam ){   
   gpioToggle( LEDB );
}

// Funcion que inicializa la tarea
void task2_Init( void ){
   gpioInit( LED1, GPIO_OUTPUT );
}

// Funcion que se ejecuta periodicamente
void task2_Update( void* taskParam ){   
   gpioToggle( LED1 );
}

// Funcion que inicializa la tarea
void task3_Init( void ){
   gpioInit( LED2, GPIO_OUTPUT );
}

// Funcion que se ejecuta periodicamente
void task3_Update( void* taskParam ){   
   gpioToggle( LED2 );
}