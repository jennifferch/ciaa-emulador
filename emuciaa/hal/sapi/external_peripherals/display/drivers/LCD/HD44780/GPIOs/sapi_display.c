/*==================[inlcusiones]============================================*/
#include "sapi_display.h"
#include "stdio.h"
#include <string.h>
#include "stdarg.h"

/*==================[definiciones y macros]==================================*/

//=====[Declaration of public data types]======================================
displayType_t displayType;
displayConnection_t displayConnection;
displayMode_t displayMode;

void clearCustomChar( void );
//=====[Declarations (prototypes) of public functions]=========================

void displayInit( displayType_t type, displayConnection_t connection )
{
    displayType = type;
    displayConnection = connection;
    initGraphicsDisplay("LCD");
}
 
void displayCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY ) 
{
    locate(charPositionX, charPositionY);
}

void displayStringWrite( const char * str ) 
{
    if( displayType == DISPLAY_TYPE_GLCD_ST7920 && displayMode == DISPLAY_MODE_CHAR){
       glcdPrintChar(str);
    }else{
       lcdPrintChar(str);
    }
}

void displayClear( void ) 
{
   if( displayType == DISPLAY_TYPE_GLCD_ST7920){
       glcd_clear();
   }else{
       lcd_clear();
   }
}

void clearCustomChar( void )
{
    cls();
}

// GLCD display only
void displayModeWrite( displayMode_t mode )
{
   if( displayMode != mode){
       glcd_clear();
   }
   displayMode = mode;
    
}

void displayBitmapWrite( uint8_t* bitmap )
{
    if( displayType == DISPLAY_TYPE_GLCD_ST7920 && displayMode == DISPLAY_MODE_GRAPHIC){
        glcd_print_bitmap(bitmap);
        delay(1); 
    }
}

void displayBitmapWriteMbed( struct Bitmap bm, int x, int y)
{
     print_bm(bm, x,y);
     delay(1); 
     copy_to_lcd();
     setmode(XOR);
}

// LCD display only
void displayCustomCharCreate( uint8_t charIdx, uint8_t* bitmap ) // guarda un maximo de 8 caracteres 
{

}
void displayCustomCharWrite( uint8_t charIdx ) // Imprime el caracter personalizado 
{

}
//=====[#include guards - end]=================================================
