/* Copyright 2017, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/* Date: 2017-12-05 */

/*==================[inlcusiones]============================================*/

#include "display_lcd_hd44780_gpios.h"
#include "display_lcd_hd44780_gpios_api.h"

#include "stdio.h"
#include "Small_7.h"
#include "emscripten.h"
#include <string.h>
#include "stdarg.h"
#include "GraphicsDisplay.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

typedef struct {
   uint16_t lineWidth;
   uint16_t amountOfLines;
   uint16_t charWidth;
   uint16_t charHeight;
   uint8_t x;
   uint8_t y;
} lcd_t;

/*==================[definiciones de datos externos]=========================*/

static lcd_t lcd;

/*==================[declaraciones de funciones internas]====================*/

static uint8_t lcdDataValue = 0;
static uint8_t lcdEnStatus = OFF;
static uint8_t lcdRsStatus = OFF;
static uint8_t lcdBacklightStatus = 0;

static void lcdI2cWritePins( uint8_t _data );
static void lcdPinSet( uint8_t pin, bool_t status );

static void lcdEnablePulse( void );
static void lcdSendNibble( uint8_t nibble );

/*==================[declaraciones de funciones externas]====================*/

/*==================[definiciones de funciones internas]=====================*/


#define PCF8574T_I2C_A0           1 // 1 connected to VDD, 0 to VSS
#define PCF8574T_I2C_A1           1 // 1 connected to VDD, 0 to VSS
#define PCF8574T_I2C_A2           1 // 1 connected to VDD, 0 to VSS

#define PCF8574T_I2C_BASE         0x20 // 0x40(fixed)
#define PCF8574T_I2C_ADDRESS      ( PCF8574T_I2C_BASE | ((PCF8574T_I2C_A2)<<2) | ((PCF8574T_I2C_A1)<<1) | PCF8574T_I2C_A0 )

static uint8_t pcf8574TGpioPortDirections = 0x00;
static uint8_t pcf8574TGpioPortValue = 0x00;
static uint8_t pcf8574TI2cAddress = PCF8574T_I2C_ADDRESS;



static void pcf8574TInit( uint8_t i2c, uint8_t i2cAddress );
static void pcf8574TGpioPortInit( uint8_t directions );
static void pcf8574TGpioPortWrite( uint8_t portValue );
static uint8_t pcf8574TGpioPortRead( void );
static void pcf8574TGpioInit( pcf8574T_gpio_t pin,
                              pcf8574T_gpioDirection_t direction );
static bool_t pcf8574TGpioRead( pcf8574T_gpio_t pin );
static void pcf8574TGpioWrite( pcf8574T_gpio_t pin, bool_t value );


#define BPP    1       // Bits per pixel


char* font;
int draw_mode;

int orientation;
int char_x;
int char_y;
char buffer[32 * 128];
int contrast;
int auto_up;

gpioMap_t _lcdrs;
gpioMap_t _lcden;
gpioMap_t _lcd;

static void pcf8574TInit( uint8_t i2c, uint8_t i2cAddress )
{

   pcf8574TI2cAddress = i2cAddress;
//   i2cInit( I2C0, 100000 );

   pcf8574TGpioPortInit( 0x00 ); // Init all GPIOs as outputs
   pcf8574TGpioPortWrite( 0x00 ); // Init all as zeros
   /*
   while(true){
      pcf8574TGpioPortWrite( 0x00 );
      delay(2000);
      pcf8574TGpioPortWrite( 0xFF );
      delay(2000);
   }
   */
}

static void pcf8574TGpioPortInit( uint8_t directions )
{
   pcf8574TGpioPortDirections = directions;
 //  i2cWrite( I2C0, pcf8574TI2cAddress, &directions, 1, TRUE );
}

static void pcf8574TGpioPortWrite( uint8_t portValue )
{
   pcf8574TGpioPortValue = portValue;
   // Or with pcf8574TGpioPortDirections to keep pins initialized as inputs
   uint8_t transmitDataBuffer = portValue | pcf8574TGpioPortDirections;
 //  i2cWrite( I2C0, pcf8574TI2cAddress, &transmitDataBuffer, 1, TRUE );
}

static uint8_t pcf8574TGpioPortRead( void )
{
   //uint8_t dataToReadBuffer[1] = { 0 };
   uint8_t receiveDataBuffer = 0;
  // i2cRead( I2C0, pcf8574TI2cAddress,
   //        &receiveDataBuffer, 1, TRUE );
}

static void pcf8574TGpioInit( pcf8574T_gpio_t pin,
                              pcf8574T_gpioDirection_t direction )
{
   uint8_t directions = pcf8574TGpioPortDirections;
   if( direction ) {
      directions |= (1<<pin);
   } else {
      directions &= ~(1<<pin);
   }
   pcf8574TGpioPortInit( directions );
}

static bool_t pcf8574TGpioRead( pcf8574T_gpio_t pin )
{
   return pcf8574TGpioPortRead() & (1<<pin);
}

static void pcf8574TGpioWrite( pcf8574T_gpio_t pin, bool_t value )
{
   uint8_t portValue = pcf8574TGpioPortValue;
   if( value ) {
      portValue |= (1<<pin);
   } else {
      portValue &= ~(1<<pin);
   }
   pcf8574TGpioPortWrite( portValue );
}



static void lcdPinSet( uint8_t pin, bool_t status )
{
#ifdef LCD_HD44780_I2C_PCF8574T
   pcf8574TGpioWrite( pin, status );
#else
   gpioWrite( pin, status );
#endif
}

static void lcdEnablePulse( void )
{
  // lcdPinSet( LCD_HD44780_EN, ON );       // EN = 1 for H-to-L pulse
  // lcdDelay_us( LCD_EN_PULSE_WAIT_US );   // Wait to make EN wider //lcdDelay_us(1);
  // lcdPinSet( LCD_HD44780_EN, OFF );      // EN = 0 for H-to-L pulse
   //lcdDelay_us(50); // commands need > 37us to settle
}

static void lcdSendNibble( uint8_t nibble )
{
  /* lcdPinSet( LCD_HD44780_D7, ( nibble & 0x80 ) );
   lcdPinSet( LCD_HD44780_D6, ( nibble & 0x40 ) );
   lcdPinSet( LCD_HD44780_D5, ( nibble & 0x20 ) );
   lcdPinSet( LCD_HD44780_D4, ( nibble & 0x10 ) );*/
}

/*==================[definiciones de funciones externas]=====================*/

void lcdCommand( uint8_t cmd )
{
   lcdSendNibble( cmd & 0xF0 );          // Send high nibble to D7-D4

//   lcdPinSet( LCD_HD44780_RS, OFF );   // RS = 0 for command
 //  lcdPinSet( LCD_HD44780_RW, OFF );   // RW = 0 for write

   lcdEnablePulse();
 //  lcdDelay_us( LCD_LOW_WAIT_US );       // Wait

   lcdSendNibble( cmd << 4 );            // Send low nibble to D7-D4
   lcdEnablePulse();
}

void lcdData( uint8_t data )
{
   lcdSendNibble( data & 0xF0 );         // Send high nibble to D7-D4

 //  lcdPinSet( LCD_HD44780_RS, ON );    // RS = 1 for data
 //  lcdPinSet( LCD_HD44780_RW, OFF );   // RW = 0 for write

   lcdEnablePulse();

   lcdSendNibble( data << 4 );           // Send low nibble to D7-D4
   lcdEnablePulse();
}

void lcdInit( uint16_t lineWidth, uint16_t amountOfLines,
              uint16_t charWidth, uint16_t charHeight )
{
   lcd.lineWidth = lineWidth;
   lcd.amountOfLines = amountOfLines;
   lcd.charWidth = charWidth;
   lcd.charHeight = charHeight;
   lcd.x = 0;
   lcd.y = 0;

#ifdef LCD_HD44780_I2C_PCF8574T
   // Init I2C
   pcf8574TInit( I2C0, PCF8574T_I2C_ADDRESS );
   lcdPinSet( LCD_HD44780_BACKLIGHT, ON );
//   delay(100);
#else
   // Configure LCD Pins as Outputs
 /* lcdInitPinAsOutput( LCD_HD44780_RST );
   lcdInitPinAsOutput( LCD_HD44780_RS );
   lcdInitPinAsOutput( LCD_HD44780_RW );
   lcdInitPinAsOutput( LCD_HD44780_EN );
   lcdInitPinAsOutput( LCD_HD44780_D4 );
   lcdInitPinAsOutput( LCD_HD44780_D5 );
   lcdInitPinAsOutput( LCD_HD44780_D6 );
   lcdInitPinAsOutput( LCD_HD44780_D7 );*/ 
#endif

   // Configure LCD for 4-bit mode
  /* lcdPinSet( LCD_HD44780_RW, OFF );     // RW = 0
   lcdPinSet( LCD_HD44780_RS, OFF );     // RS = 0
   lcdPinSet( LCD_HD44780_EN, OFF );     // EN = 0

        //lcdCommand( 0x20 );                   // Command 0x20 for 4-bit mode
        lcdCommand( 0x30 );                   // Command 0x20 for 4-bit mode
        lcdCommandDelay();                    // Wait

        //lcdCommand( 0x20 );                   // Command 0x20 for 4-bit mode
        //lcdCommand( 0x00 );                   // Command 0x20 for 4-bit mode
        //lcdCommandDelay();                    // Wait
        lcdCommand( 0x30 );                   // Command 0x20 for 4-bit mode
        lcdDelay_us(40);
        
        //lcdCommand( 0x00 );                   // Command 0x20 for 4-bit mode
        //lcdCommand( 0xF0 );                   // Command 0x20 for 4-bit mode
        lcdCommand( 0x08 );                   // Command 0x20 for 4-bit mode
        lcdCommandDelay();                    // Wait
 
        //lcdCommand( 0x00 );                   // Command 0x20 for 4-bit mode
        //lcdCommand( 0x10 );                   // Command 0x20 for 4-bit mode
        lcdCommand( 0x01 );                   // Command 0x20 for 4-bit mode
        lcdDelay_ms(12);
 
        //lcdCommand( 0x00 );                   // Command 0x20 for 4-bit mode
        //lcdCommand( 0x70 );                   // Command 0x20 for 4-bit mode
        //lcdCommandDelay();                    // Wait
        
        lcdCommand( 0x06 );                   // Command 0x20 for 4-bit mode
        lcdDelay_ms( 1 );                     // Wait
        
        lcdCommand( 0x0C );                   // Command 0x20 for 4-bit mode
        lcdDelay_ms( 3 );                     // Wait
        
        lcdCommand( 0x02 );                   // Command 0x20 for 4-bit mode
        lcdDelay_ms( 3 );                     // Wait


   lcdCommand( 0x33 );                   // Command 0x33 for 4-bit mode
   lcdCommandDelay();                    // Wait

   lcdCommand( 0x32 );                   // Command 0x32 for 4-bit mode
   lcdCommandDelay();                    // Wait

   lcdCommand( 0x28 );                   // Command 0x28 for 4-bit mode
   lcdCommandDelay();                    // Wait

   // Initialize LCD
   lcdCommand( 0x0E );                   // Command 0x0E for display on, cursor on
   lcdCommandDelay();                    // Wait

   lcdClear();                           // Command for clear LCD

   lcdCommand( 0x06 );                   // Command 0x06 for Shift cursor right
   lcdCommandDelay();                    // Wait

   lcdDelay_ms( 1 );                     // Wait

   lcdCursorSet( LCD_CURSOR_OFF );
   //lcdGoToXY( 0, 0 );
   lcdClearAndHome();
   
*/

   _lcdrs = LCDRS;
   _lcden = LCDEN;
   _lcd = LCD1;

   initGraphicsDisplay("LCD");

   display_lcd_hd44780_gpios_init(_lcd, _lcdrs, _lcden);

   orientation = 1;
   draw_mode = NORMAL;
   char_x = 0;
   lcd_reset();
}

void lcdGoToXY( uint8_t x, uint8_t y )
{
   if( x >= lcd.lineWidth || y >= lcd.amountOfLines ) {
      return;
   }
   uint8_t firstCharAdress[] = { 0x80, 0xC0, 0x94, 0xD4 };   // See table 12-5
   //lcdCommand( firstCharAdress[ y - 1 ] + x - 1 ); // Start in {x,y} = {1,1}
   lcdCommand( firstCharAdress[y] + x );             // Start in {x,y} = {0,0}
 //  lcdDelay_us( LCD_HIGH_WAIT_US );      // Wait
   lcd.x = x;
   lcd.y = y;
}

void lcdClear( void )
{
   //lcdCommand( 0x01 );                   // Command 0x01 for clear LCD
 //  lcdDelay_ms(LCD_CLR_DISP_WAIT_MS);    // Wait
    memset(buffer,0x00,4096);  // clear display buffer
    lcdCursorSet(LCD_CURSOR_ON);
}

void lcdCursorSet( lcdCursorModes_t mode )
{
   // lcdCommand( 0b00001100 | mode );
 //  lcdDelay_ms(LCD_CLR_DISP_WAIT_MS); // Wait
    display_lcd_hd44780_gpios_cursor_set(_lcd, _lcdrs, _lcden, buffer);
}

void lcdSendStringRaw( char* str )
{
   uint8_t i = 0;
   while( str[i] != 0 ) {
      lcdData( str[i] );
      i++;
   }
}

void lcdCreateChar( uint8_t charnum, const char* chardata )
{
   uint8_t i;
   charnum &= 0x07;
   lcdCommand( E_SET_CGRAM_ADDR | (charnum << 3) );
   for (i = 0; i < 8; i++) {
      lcdData( chardata[i] );
   }
   delay(1);
   lcdGoToXY( lcd.x, lcd.y );
}

void lcdCreateCustomChar( lcdCustomChar_t* customChar )
{
//   lcdCreateChar( customChar->address, customChar->bitmap );
}

void lcdSendCustomChar( lcdCustomChar_t* customChar )
{
   lcdSendCustomCharByIndex( customChar->address );
}


void lcdClearAndHome( void )
{
   lcdClear();
   lcdGoToXY( 0, 0 ); // Poner cursor en 0, 0
   //delay(100);
}

void lcdClearLine( uint8_t line )
{
   lcdClearLineFromTo( line, 0, lcd.lineWidth - 1 );
}

void lcdClearLineFrom( uint8_t line, uint8_t xFrom )
{
   lcdClearLineFromTo( line, xFrom, lcd.lineWidth - 1 );
}

void lcdClearLineFromTo( uint8_t line, uint8_t xFrom, uint8_t xTo )
{
   uint8_t i = 0;

   if( xFrom >= lcd.lineWidth || line >= lcd.amountOfLines ) {
      return;
   }
   if( xFrom > xTo ) {
      return;
   }
   if( xTo >= lcd.lineWidth ) {
      xTo = lcd.lineWidth - 1;
   }

   lcdGoToXY( xFrom, line );
   for( i=xFrom; i<=xTo; i++ ) {
      lcdSendChar( ' ' );
   }
   //lcd.x--;
   lcdGoToXY( xFrom, line );
}

void lcdSendChar( char character )
{
   uint8_t i = 0;

   if( character == '\r' ) {        // Ignore '\r'
   } else if( character == '\n' ) { // Mando enter
      lcdSendEnter();
   } else {
      // Si se extiende en ancho mando enter
      if( lcd.x >= lcd.lineWidth ) {
         lcdSendEnter();
      }
      // Mando el caracter
      lcdData( character );
      lcd.x++;
   }
}

void lcdSendCustomCharByIndex( uint8_t charIndex )
{
   // Si se extiende en ancho mando enter
   if( lcd.x >= lcd.lineWidth ) {
      lcdSendEnter();
   }
   // Mando el caracter
   lcdData( charIndex );
   lcd.x++;
}

void lcdSendEnter( void )
{
   // Si llego abajo no hace nada
   if( lcd.y >= lcd.amountOfLines ) {
      return;
   } else {
      lcd.x = 0;
      lcd.y++;
      lcdGoToXY( lcd.x, lcd.y );
   }
}

void lcdSendStringClearLine( char* str )
{
   lcdSendString( str );
   lcdClearLineFrom( lcd.y, lcd.x );
}

void lcdSendString( char* str )
{
   uint32_t i = 0;
   while( str[i] != 0 ) {
      lcdSendChar( str[i] );
      i++;
   }
}

void lcdSendStringFormXY( char* str, uint8_t x, uint8_t y )
{
   lcdGoToXY( x, y );
   lcdSendString( str );
}

void lcdSendStringFormXYClearLine( char* str, uint8_t x, uint8_t y )
{
   lcdSendStringFormXY( str, x, y );
   lcdClearLineFrom( lcd.y, lcd.x );
}

void lcdSendInt( int64_t value )
{
   lcdSendString( intToStringGlobal(value) );
}

void lcdSendIntClearLine( int64_t value )
{
   lcdSendInt( value );
   lcdClearLineFrom( lcd.y, lcd.x );
}

void lcdSendIntFormXY( int64_t value, uint8_t x, uint8_t y )
{
   lcdGoToXY( x, y );
   lcdSendInt( value );
}

void lcdSendIntFormXYClearLine( int64_t value, uint8_t x, uint8_t y )
{
   lcdSendIntFormXY( value, x, y );
   lcdClearLineFrom( lcd.y, lcd.x );
}


void lcdSendFloat( float value, uint32_t decDigits )
{
   lcdSendString( floatToStringGlobal(value, decDigits) );
}

void lcdSendFloatClearLine( float value, uint32_t decDigits )
{
   lcdSendString( floatToStringGlobal(value, decDigits) );
   lcdClearLineFrom( lcd.y, lcd.x );
}

void lcdSendFloatFormXY( float value, uint32_t decDigits, uint8_t x, uint8_t y )
{
   lcdGoToXY( x, y );
   lcdSendFloat( value, decDigits );
}

void lcdSendFloatFormXYClearLine( float value, uint32_t decDigits, uint8_t x, uint8_t y )
{
   lcdSendFloatFormXY( value, decDigits, x, y );
   lcdClearLineFrom( lcd.y, lcd.x );
}


int width()
{
    if (orientation == 0 || orientation == 2) return 32;
    else return 128;
}

int height()
{
    if (orientation == 0 || orientation == 2) return 128;
    else return 32;
}


void invert(unsigned int o)
{
  /*  EM_ASM({
        console.log('invert\n');
    });*/
}


void set_contrast(unsigned int o)
{
   /* EM_ASM({
        console.log('set_contrast\n');
    });*/
}

int get_contrast(void)
{
    return(contrast);
}


void wr_cmd(unsigned char cmd)
{
    /* no-op */
}

// write data to lcd controller

void wr_dat(unsigned char dat)
{
    /* no-op */
}

// reset and init the lcd controller

void lcd_reset()
{
    memset(buffer,0x00,4096);  // clear display buffer

    // dont do this by default. Make the user call
    //claim(stdout);           // redirekt printf to lcd
    locate(0,0);
    set_font((unsigned char*)Small_7);  // standart font

    lcdCursorSet(LCD_CURSOR_ON);
}

// set one pixel in buffer

void pixel(int x, int y, int color)
{
    // first check parameter
    if(x > 128 || y > 32 || x < 0 || y < 0) return;

    if(draw_mode == NORMAL) {
        if(color == 0)
            buffer[x + (y * 128)] = 0;
        else
            buffer[x + (y * 128)] = 1;
    } else { // XOR mode
        if(color == 1)
            buffer[x + (y * 128)] ^= 1;
    }
}

// update lcd

void copy_to_lcd(void)
{
   display_lcd_hd44780_gpios_copy_to_lcd(_lcd, _lcdrs, _lcden, buffer);
}

void _flush(void)
{
    copy_to_lcd();
}

void line(int x0, int y0, int x1, int y1, int color)
{
    int   dx = 0, dy = 0;
    int   dx_sym = 0, dy_sym = 0;
    int   dx_x2 = 0, dy_x2 = 0;
    int   di = 0;

    dx = x1-x0;
    dy = y1-y0;

    //  if (dx == 0) {        /* vertical line */
    //      if (y1 > y0) vline(x0,y0,y1,color);
    //      else vline(x0,y1,y0,color);
    //      return;
    //  }

    if (dx > 0) {
        dx_sym = 1;
    } else {
        dx_sym = -1;
    }
    //  if (dy == 0) {        /* horizontal line */
    //      if (x1 > x0) hline(x0,x1,y0,color);
    //      else  hline(x1,x0,y0,color);
    //      return;
    //  }

    if (dy > 0) {
        dy_sym = 1;
    } else {
        dy_sym = -1;
    }

    dx = dx_sym*dx;
    dy = dy_sym*dy;

    dx_x2 = dx*2;
    dy_x2 = dy*2;

    if (dx >= dy) {
        di = dy_x2 - dx;
        while (x0 != x1) {

            pixel(x0, y0, color);
            x0 += dx_sym;
            if (di<0) {
                di += dy_x2;
            } else {
                di += dy_x2 - dx_x2;
                y0 += dy_sym;
            }
        }
        pixel(x0, y0, color);
    } else {
        di = dx_x2 - dy;
        while (y0 != y1) {
            pixel(x0, y0, color);
            y0 += dy_sym;
            if (di < 0) {
                di += dx_x2;
            } else {
                di += dx_x2 - dy_x2;
                x0 += dx_sym;
            }
        }
        pixel(x0, y0, color);
    }
    if(auto_up) lcdCursorSet(LCD_CURSOR_ON);
}

void rect(int x0, int y0, int x1, int y1, int color)
{

    if (x1 > x0) line(x0,y0,x1,y0,color);
    else  line(x1,y0,x0,y0,color);

    if (y1 > y0) line(x0,y0,x0,y1,color);
    else line(x0,y1,x0,y0,color);

    if (x1 > x0) line(x0,y1,x1,y1,color);
    else  line(x1,y1,x0,y1,color);

    if (y1 > y0) line(x1,y0,x1,y1,color);
    else line(x1,y1,x1,y0,color);

    if(auto_up) lcdCursorSet(LCD_CURSOR_ON);
}

void fillrect(int x0, int y0, int x1, int y1, int color)
{
    int l,c,i;
    if(x0 > x1) {
        i = x0;
        x0 = x1;
        x1 = i;
    }

    if(y0 > y1) {
        i = y0;
        y0 = y1;
        y1 = i;
    }

    for(l = x0; l<= x1; l ++) {
        for(c = y0; c<= y1; c++) {
            pixel(l,c,color);
        }
    }
    if(auto_up) lcdCursorSet(LCD_CURSOR_ON);
}



void circle(int x0, int y0, int r, int color)
{

    int draw_x0, draw_y0;
    int draw_x1, draw_y1;
    int draw_x2, draw_y2;
    int draw_x3, draw_y3;
    int draw_x4, draw_y4;
    int draw_x5, draw_y5;
    int draw_x6, draw_y6;
    int draw_x7, draw_y7;
    int xx, yy;
    int di;
    //WindowMax();
    if (r == 0) {       /* no radius */
        return;
    }

    draw_x0 = draw_x1 = x0;
    draw_y0 = draw_y1 = y0 + r;
    if (draw_y0 < height()) {
        pixel(draw_x0, draw_y0, color);     /* 90 degree */
    }

    draw_x2 = draw_x3 = x0;
    draw_y2 = draw_y3 = y0 - r;
    if (draw_y2 >= 0) {
        pixel(draw_x2, draw_y2, color);    /* 270 degree */
    }

    draw_x4 = draw_x6 = x0 + r;
    draw_y4 = draw_y6 = y0;
    if (draw_x4 < width()) {
        pixel(draw_x4, draw_y4, color);     /* 0 degree */
    }

    draw_x5 = draw_x7 = x0 - r;
    draw_y5 = draw_y7 = y0;
    if (draw_x5>=0) {
        pixel(draw_x5, draw_y5, color);     /* 180 degree */
    }

    if (r == 1) {
        return;
    }

    di = 3 - 2*r;
    xx = 0;
    yy = r;
    while (xx < yy) {

        if (di < 0) {
            di += 4*xx + 6;
        } else {
            di += 4*(xx - yy) + 10;
            yy--;
            draw_y0--;
            draw_y1--;
            draw_y2++;
            draw_y3++;
            draw_x4--;
            draw_x5++;
            draw_x6--;
            draw_x7++;
        }
        xx++;
        draw_x0++;
        draw_x1--;
        draw_x2++;
        draw_x3--;
        draw_y4++;
        draw_y5++;
        draw_y6--;
        draw_y7--;

        if ( (draw_x0 <= width()) && (draw_y0>=0) ) {
            pixel(draw_x0, draw_y0, color);
        }

        if ( (draw_x1 >= 0) && (draw_y1 >= 0) ) {
            pixel(draw_x1, draw_y1, color);
        }

        if ( (draw_x2 <= width()) && (draw_y2 <= height()) ) {
            pixel(draw_x2, draw_y2, color);
        }

        if ( (draw_x3 >=0 ) && (draw_y3 <= height()) ) {
            pixel(draw_x3, draw_y3, color);
        }

        if ( (draw_x4 <= width()) && (draw_y4 >= 0) ) {
            pixel(draw_x4, draw_y4, color);
        }

        if ( (draw_x5 >= 0) && (draw_y5 >= 0) ) {
            pixel(draw_x5, draw_y5, color);
        }
        if ( (draw_x6 <=width()) && (draw_y6 <= height()) ) {
            pixel(draw_x6, draw_y6, color);
        }
        if ( (draw_x7 >= 0) && (draw_y7 <= height()) ) {
            pixel(draw_x7, draw_y7, color);
        }
    }
    if(auto_up) lcdCursorSet(LCD_CURSOR_ON);
}

void fillcircle(int x, int y, int r, int color)
{
    int i,up;
    up = auto_up;
    auto_up = 0;   // off
    for (i = 0; i <= r; i++)
        circle(x,y,i,color);
    auto_up = up;
    if(auto_up) lcdCursorSet(LCD_CURSOR_ON);
}

void setmode(int mode)
{
    draw_mode = mode;
}

void locate(int x, int y)
{
    char_x = x;
    char_y = y;
}



int columns_d()
{
    return width() / font[1];
}



int rows_d()
{
    return height() / font[2];
}



int _putc_d(int value)
{
    if (value == '\n') {    // new line
        char_x = 0;
        char_y = char_y + font[2];
        if (char_y >= height() - font[2]) {
            char_y = 0;
        }
    } else {
        character_d(char_x, char_y, value);
        if(auto_up) copy_to_lcd();
    }
    return value;
}

void character_d(int x, int y, int c)
{
    unsigned int hor,vert,offset,bpl,j,i,b;
    unsigned char* zeichen;
    unsigned char z,w;

    if ((c < 31) || (c > 127)) return;   // test char range

    // read font parameter from start of array
    offset = font[0];                    // bytes / char
    hor = font[1];                       // get hor size of font
    vert = font[2];                      // get vert size of font
    bpl = font[3];                       // bytes per line

    if (char_x + hor > width()) {
        char_x = 0;
        char_y = char_y + vert;
        if (char_y >= height() - font[2]) {
            char_y = 0;
        }
    }

    zeichen = &font[((c -32) * offset) + 4]; // start of char bitmap
    w = zeichen[0];                          // width of actual char
    // construct the char into the buffer
    for (j=0; j<vert; j++) {  //  vert line
        for (i=0; i<hor; i++) {   //  horz line
            z =  zeichen[bpl * i + ((j & 0xF8) >> 3)+1];
            b = 1 << (j & 0x07);
            if (( z & b ) == 0x00) {
                pixel(x+i,y+j,0);
            } else {
                pixel(x+i,y+j,1);
            }

        }
    }

    char_x += w;
}


void set_font(unsigned char* f)
{
    font = f;
}

void set_auto_up(unsigned int up)
{
    if(up ) auto_up = 1;
    else auto_up = 0;
}

int get_auto_up(void)
{
    return (auto_up);
}

void lcdCreateCharT(Bitmap bm, int x, int y)
{
    int h,v,b;
    char d;

    for(v=0; v < bm.ySize; v++) {   // lines
        for(h=0; h < bm.xSize; h++) { // pixel
            if(h + x > 127) break;
            if(v + y > 31) break;
            d = bm.data[bm.Byte_in_Line * v + ((h & 0xF8) >> 3)];
            b = 0x80 >> (h & 0x07);
            if((d & b) == 0) {
                pixel(x+h,y+v,0);
            } else {
                pixel(x+h,y+v,1);
            }
        }
    }

}


int printfLCD(const char *format, ...){
        va_list arg;
        va_start(arg, format);
 //   #if defined(TARGET_SIMULATOR)
        char buffer[4096] = { 0 };
        int r = vsprintf(buffer, format, arg);
        for (int ix = 0; ix < r; ix++) {
            _putc_d(buffer[ix]);
        }
        _flush();
  /*  #else
        fflush(_file);
        int r = vfprintf(_file, format, arg);
    #endif */
        va_end(arg);
        return r;
}


/*==================[fin del archivo]========================================*/
