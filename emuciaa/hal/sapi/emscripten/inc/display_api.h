/* Copyright 2015, Eric Pernia.
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

#ifndef LCD_API_H
#define LCD_API_H

#include "emscripten.h"

#include "base/sapi_datatypes.h"
#include "sapi_peripheral_map.h"

/*==================[c]====================================================*/
#ifdef __cplusplus
extern "C" {
#endif

    void lcd_init( gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck );

    void lcd_cursor_set(gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck, unsigned char * buffer);

    void lcd_copy_to_lcd(gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck, unsigned char * buffer);

    void char_to_glcd(unsigned char * buffer);

    void char_to_lcd(unsigned char * buffer);

    void bitmap_to_glcd( uint8_t* bitmap);

    void display_clear_glcd();

    void display_clear_lcd();

    void position_to_glcd(int x, int y);

    void position_to_lcd(int x, int y);
/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif


#endif
