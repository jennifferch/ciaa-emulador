//=====[#include guards - begin]===============================================

#ifndef _SAPI_DISPLAY_H_
#define _SAPI_DISPLAY_H_

/*==================[inclusions]=============================================*/
      // <= Biblioteca sAPI
#include "GraphicsDisplay.h"
/*==================[c++]====================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

typedef enum {
     DISPLAY_TYPE_LCD_HD44780,
     DISPLAY_TYPE_GLCD_ST7920,
} displayType_t;

typedef enum {
     DISPLAY_CONNECTION_GPIO_4BITS,
//     DISPLAY_CONNECTION_GPIO_8BITS,
//     DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER,
//     DISPLAY_CONNECTION_SPI
} displayConnection_t;

typedef enum {
     DISPLAY_MODE_CHAR,
     DISPLAY_MODE_GRAPHIC
} displayMode_t;

typedef struct {
   displayConnection_t connection;
   displayType_t type;
   displayMode_t mode;
} display_t;

extern struct Bitmap;

//=====[Declarations (prototypes) of public functions]=========================

void displayInit( displayType_t type, displayConnection_t connection );
 
void displayCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY ); // Posicion donde voy a comenzar a escribir texto ( ex lcdGoToXY() )

void displayStringWrite( const char * str ); // Texto a escribir desde posicion seteada actual ( ex lcdSendStringRaw() )

void displayClear( void ); // Borrar todo el texto o graficos del display

// GLCD display only
void displayModeWrite( displayMode_t mode );

void displayBitmapWrite( uint8_t* bitmap );

void displayBitmapWriteMbed( struct Bitmap bm, int x, int y); // Ver en Mbed

// LCD display only
// Cargar el caracter a CGRAM
// El primer parametro es el codigo del caracter (0 a 7).
// El segundo es el puntero donde se guarda el bitmap (el array declarado
// anteriormente)
void displayCustomCharCreate( uint8_t charIdx, uint8_t* bitmap ); // guarda un maximo de 8 caracteres 

void displayCustomCharWrite( uint8_t charIdx ); // Imprime el caracter personalizado 

//=====[#include guards - end]=================================================


/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif // _SAPI_DISPLAY_H_
