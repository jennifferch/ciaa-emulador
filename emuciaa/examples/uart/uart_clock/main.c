/*============================================================================
 * License: BSD-3-Clause
 * Copyright 2018, Eric Pernia <ericpernia@gmail.com>
 * All rights reserved.
 * Date: 2018/10/04
 *===========================================================================*/

// The maximum number of tasks required at any one time during the execution
// of the program. MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCHEDULER_MAX_TASKS   (2)

/*==================[inlcusiones]============================================*/

//#include "cooperative_os_scheduler_03_seos_Pont2014.h"   // <= own header (optional)
#include "sapi.h"        // <= sAPI header

#include "seos_pont_2014_isr.h"       // <= dispatcher and task management header
#include "seos_pont_2014_scheduler.h" // <= scheduler and system initialization header

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

//---------------------- #include "buffer.h" ----------------------------
#define TX_BUFFER_LENGTH     20

#define ERROR_UART_FULL_BUFF  15
#define ERROR_UART_TX_TIMEOUT 16

void Write_String_To_Buffer( uint8_t *strPtr );
uint8_t Read_Char_From_Buffer( void );

static void Write_Char_To_Buffer( uint8_t data );


static uint8_t TX_Indice_escritura = 0;
static uint8_t TX_Indice_lectura = 0;
static uint8_t TX_Buffer[TX_BUFFER_LENGTH];

uint8_t Buffer_Error_code;
//---------------------- #include "task_uart.h" -----------------------------
void taskUartInit( uint32_t baudrate );
void taskUart( void* taskParam );

//---------------------- "#include "task_clock.h" -----------------------------
void taskClockInit( uint8_t h, uint8_t m, uint8_t s );
void taskClock( void* taskParam );
static uint8_t Reloj_string[18] = "RELOJ: HH:MM:SS\r\n";

static uint8_t hs;
static uint8_t min;
static uint8_t seg;

static const uint8_t CharMap[10] = {'0','1','2','3','4','5','6','7','8','9'};
//------------------------------------------------------------------------------------

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();
   
   taskClockInit( 19, 0, 0 ); // Inicializar tarea de Reloj
   taskUartInit( 115200 );    // Inicializar tarea de UART

   // FUNCION que inicializa el planificador de tareas
   schedulerInit();

   // Se agrega la tarea taskClock al planificador
   schedulerAddTask( taskClock, // funcion de tarea a agregar
                     0,         // parametro de la tarea
                     0,         // offset de ejecucion en ticks
                     1000       // periodicidad de ejecucion en ticks
                   );

   // Se agrega la tarea taskUart al planificador cada 5 ticks, offset 1 tick
   schedulerAddTask( taskUart, 0, 1, 5 );

   // FUNCION que inicializa la interrupcion que ejecuta el planificador de
   // tareas con tick cada 1ms.
   schedulerStart( 1 );

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {
      // Se despachan (ejecutan) las tareas marcadas para su ejecucion.
      // Luego se pone el sistema en bajo consumo hasta que ocurra la
      // proxima interrupcion, en este caso la de Tick.
      // Al ocurrir la interrupcion de Tick se ejecutara el planificador
      // que revisa cuales son las tareas a marcar para su ejecucion.
      schedulerDispatchTasks();
      // Es necesario agregar un delay, sino, el navegador se bloquea.
      delay(1);
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}


static void Write_Char_To_Buffer( uint8_t data )
{
   // Write to the buffer *only* if there is space
   if (TX_Indice_escritura < TX_BUFFER_LENGTH){
      TX_Buffer[TX_Indice_escritura] = data;
      TX_Indice_escritura++;
   }
   else{
      // Write buffer is full
      Buffer_Error_code = ERROR_UART_FULL_BUFF;
   }
}

/*==================[external functions definition]==========================*/

void Write_String_To_Buffer( uint8_t *strPtr )
{
   uint8_t i = 0;
   while ( strPtr[i] != '\0'){
      Write_Char_To_Buffer( strPtr[i] );
      i++;
   }
}

uint8_t Read_Char_From_Buffer(void)
{
   uint8_t ret_val = 0;

   // Hay byte en el buffer Tx para transmitir?
   if (TX_Indice_lectura < TX_Indice_escritura){
      ret_val = TX_Buffer[TX_Indice_lectura];
      TX_Indice_lectura++;
   }
   else{
      // No hay datos disponibles para enviar
      TX_Indice_lectura = 0;
      TX_Indice_escritura = 0;
      ret_val = 0;
   }

   return ret_val;
}

void taskUartInit( uint32_t baudrate )
{
   uartConfig( UART_USB, baudrate );
}


void taskUart( void* taskParam )
{
   uint8_t txByte = 0;

   txByte = Read_Char_From_Buffer();

   // Si el txByte es distinto de 0 envio lo que me llego
   if( txByte != 0 ){
      // Envio un byte si el canal esta libre
      uartWriteByte( UART_USB, txByte );
   }
}

void taskClockInit( uint8_t h, uint8_t m, uint8_t s )
{
   hs  = h;
   min = m;
   seg = s;
}

void taskClock( void* taskParam )
{
   // Actualizo reloj
   if ( ++seg == 60 ){
      seg = 0;
      if ( ++min == 60 ){
         min = 0;
           if ( ++hs == 24 ){
           hs = 0;
         }
      }
   }

   // Armo mensaje a visualizar
   Reloj_string[7]  = CharMap[hs/10];
   Reloj_string[8]  = CharMap[hs%10];
   Reloj_string[10] = CharMap[min/10];
   Reloj_string[11] = CharMap[min%10];
   Reloj_string[13] = CharMap[seg/10];
   Reloj_string[14] = CharMap[seg%10];

   // Lo envi�o al Buffer
   Write_String_To_Buffer(Reloj_string);
}
/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/
