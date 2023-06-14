/* mbed library for the mbed Lab Board  128*32 pixel LCD
 * use C12832 controller
 * Copyright (c) 2012 Peter Drescher - DC2PD
 * Released under the MIT License: http://mbed.org/license/mit
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef DISPLAY_LCD_HD44780_GPIOS_API_H
#define DISPLAY_LCD_HD44780_GPIOS_API_H

#include "emscripten.h"

#include "base/sapi_datatypes.h"
#include "sapi_peripheral_map.h"

/*==================[c]====================================================*/
#ifdef __cplusplus
extern "C" {
#endif

    void display_lcd_hd44780_gpios_init( gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck );

    void display_lcd_hd44780_gpios_cursor_set(gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck, char * buffer);

    void display_lcd_hd44780_gpios_copy_to_lcd(gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck, char * buffer);
/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif


#endif
