/* mbed TextDisplay Library Base Class
 * Copyright (c) 2007-2009 sford
 * Released under the MIT License: http://mbed.org/license/mit
 *
 * A common base class for Text displays
 * To port a new display, derive from this class and implement
 * the constructor (setup the display), character (put a character
 * at a location), rows and columns (number of rows/cols) functions.
 * Everything else (locate, printf, putc, cls) will come for free
 *
 * The model is the display will wrap at the right and bottom, so you can
 * keep writing and will always get valid characters. The location is
 * maintained internally to the class to make this easy
 */

#ifndef MBED_TEXTDISPLAY_H
#define MBED_TEXTDISPLAY_H

#include "emscripten.h"


/*==================[c]====================================================*/
#ifdef __cplusplus
extern "C" {
#endif


void initTextDisplay(const char *name);

void character(int column, int row, int c);

int rows();
    
int columns();

int claim (FILE *stream);

void cls_clear();
void locate_t(int column, int row);
void foreground(int colour);
void background(int colour);

int _putc(int c);
int _getc();
void _flush();

int getColumn();
int getBackground();
int getForeground();


#ifdef __cplusplus
}
#endif


#endif
