/* mbed GraphicsDisplay Display Library Base Class
 * Copyright (c) 2007-2009 sford
 * Released under the MIT License: http://mbed.org/license/mit
 *
 * A library for providing a common base class for Graphics displays
 * To port a new display, derive from this class and implement
 * the constructor (setup the display), pixel (put a pixel
 * at a location), width and height functions. Everything else
 * (locate, printf, putc, cls, window, putp, fill, blit, blitbit)
 * will come for free. You can also provide a specialised implementation
 * of window and putp to speed up the results
 */

#ifndef MBED_GRAPHICSDISPLAY_H
#define MBED_GRAPHICSDISPLAY_H

#include "TextDisplay.h"

/*==================[c]====================================================*/
#ifdef __cplusplus
extern "C" {
#endif

    void initGraphicsDisplay(const char* name);

    void pixel(int x, int y, int colour);
    int width();
    int height();

    void window(int x, int y, int w, int h);
    void putp(int colour);

    void cls_t();
    void fill(int x, int y, int w, int h, int colour);
    void blit(int x, int y, int w, int h, const int *colour);
    void blitbit(int x, int y, int w, int h, const char* colour);

    void character_g(int column, int row, int value);
    int columns_t();
    int rows_g();

 

#ifdef __cplusplus
}
#endif


#endif
