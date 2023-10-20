/*============================================================================
 Copyright (c) 2017, Eric Pernia <ericpernia@gmail.com>
 All rights reserved.
 License: bsd-3-clause (see https://opensource.org/license/bsd-3-clause/)
 Date: 2017/05/18
 Version: 1.0
============================================================================*/

// Includes de FreeRTOS
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

// sAPI header
#include "sapi.h"

// Prototipo de funcion de la tarea
void myTask( void* taskParmPtr );

int main( void )
{
   boardInit();

   // Led para dar fe de vida
   gpioWrite( LED3, ON );

   // Crear tarea en freeRTOS
   xTaskCreate(
      myTask,                     // Funcion de la tarea a ejecutar
      (const char *)"myTask",     // Nombre de la tarea como String amigable para el usuario
      configMINIMAL_STACK_SIZE*2, // Cantidad de stack de la tarea
      0,                          // Parametros de tarea
      tskIDLE_PRIORITY+1,         // Prioridad de la tarea
      0                           // Puntero a la tarea creada en el sistema
   );

   // Iniciar scheduler
   vTaskStartScheduler();

   while(1) {
      // Si cae en este while 1 significa que no pudo iniciar el scheduler
      // Es necesario agregar un delay, sino, el navegador se bloquea.
      delay(1);
   }

   return 0;
}

// Implementacion de funcion de la tarea
void myTask( void* taskParmPtr )
{
   printf( "Blinky con freeRTOS y sAPI usando memoria dinamica.\r\n" );

   gpioWrite( LED1, ON );

   // Envia la tarea al estado bloqueado durante 1 s (delay)
   vTaskDelay( 1000 / portTICK_RATE_MS );
   gpioWrite( LED1, OFF ); 

   // Tarea periodica cada 500 ms
   portTickType xPeriodicity =  500 / portTICK_RATE_MS;
   portTickType xLastWakeTime = xTaskGetTickCount();
   
   while(1) {
      gpioToggle( LEDB );
      printf( "Blink LEDB!\r\n" );

      // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
      vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
   }
}