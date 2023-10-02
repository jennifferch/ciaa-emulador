#include "sapi.h"        // <= Biblioteca sAPI

// Caracter personalizado carita feliz :)
const char smile[8] = {
   0b00000000,
   0b00001010,
   0b00001010,
   0b00001010,
   0b00000000,
   0b00010001,
   0b00001110,
   0b00000000,
};

// Caracter personalizado letra e
const char e_char[8] = {
   0b01110,
   0b10000,
   0b10000,
   0b01100,
   0b01000,
   0b10000,
   0b10001,
   0b01110
};

// Caracter personalizado letra r
const char r_char[8] = {
   0b00000,
   0b00000,
   0b00000,
   0b01110,
   0b01000,
   0b01000,
   0b01000,
   0b01000
};

// Caracter personalizado letra i
const char i_char[8] = {
   0b00000,
   0b00100,
   0b00000,
   0b00100,
   0b00100,
   0b00100,
   0b00100,
   0b00110
};

// Caracter personalizado letra c
const char c_char[8] = {
   0b00000,
   0b00000,
   0b00000,
   0b00110,
   0b01000,
   0b01000,
   0b01001,
   0b00110
};

//Temperatura - Termometro
const char tempChar[8] = {
   0b01110,
   0b01010,
   0b01010,
   0b01110,
   0b01110,
   0b10111,
   0b11111,
   0b01110
};

// Humedad - Gota
const char humChar[8] = { 
   0b00100,
   0b00100,
   0b01110,
   0b10111,
   0b10111,
   0b10011,
   0b01110,
   0b00000
};

// Viento
const char vieChar[8] = {
   0b00111,
   0b11100,
   0b00000,
   0b00111,
   0b11100,
   0b00000,
   0b00111,
   0b11100
};

// Simbolo grados
const char graChar[8] = { 
   0b01110,
   0b01010,
   0b01110,
   0b00000,
   0b00000,
   0b00000,
   0b00000,
   0b00000
};

enum{
   TEMP_CHAR = 0,
   HUM_CHAR  = 1,
   VIE_CHAR  = 2,
   E_CHAR    = 3,
   R_CHAR    = 4,
   I_CHAR    = 5,
   C_CHAR    = 6,
   GRA_CHAR  = 7,
};

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){

   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that)

   // Inicializar LCD de 16x2 (caracteres x lineas) con cada caracter de 5x8 pixeles
   lcdInit( 16, 2, 5, 8 );

   // Cargar el caracter a CGRAM
   // El primer parametro es el codigo del caracter (0 a 7).
   // El segundo es el puntero donde se guarda el bitmap (el array declarado
   // anteriormente)
   lcdCreateChar( 0, tempChar );
   lcdCreateChar( 7, humChar );
   lcdCreateChar( 14, vieChar );
                     
   lcdCreateChar( 21, e_char );
   lcdCreateChar( 24, r_char );
   lcdCreateChar( 27, i_char );
   lcdCreateChar( 30, c_char );

   lcdCreateChar( 35, graChar );

   char tempString[] = "25";
   char humString[] = "50";
   char vieString[] = "10";
   
   lcdCursorSet( LCD_CURSOR_OFF ); // Apaga el cursor
   lcdClear();                     // Borrar la pantalla

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {
      lcdGoToXY( 0, 10 ); // Poner cursor en 0, 0
      lcdSendStringRaw( "Tmp" );
      lcdData(TEMP_CHAR);
      lcdSendStringRaw( " Hum" );
      lcdData(HUM_CHAR);
      lcdSendStringRaw( " Vie" );
      lcdData(VIE_CHAR);


      lcdGoToXY( 0, 20 );
      lcdSendStringRaw( tempString );
      lcdData(GRA_CHAR);
      lcdSendStringRaw( "C" );
      
      lcdGoToXY( 20, 20 );
      lcdSendStringRaw( humString );
      lcdSendStringRaw( "%" );
      
      lcdGoToXY( 40, 20 );
      lcdSendStringRaw( vieString );
      lcdSendStringRaw( "km/h" );

      delay(3000);

      lcdClear(); // Borrar la pantalla
      lcdGoToXY( 0, 0 );
      lcdData(E_CHAR);
      lcdData(R_CHAR);
      lcdData(I_CHAR);
      lcdData(C_CHAR);

      delay(1000);

      lcdClear(); // Borrar la pantalla
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamente sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
} 