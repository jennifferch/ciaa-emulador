#include "lcd_api.h"


void lcd_init( gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck ){

    EM_ASM_({
        window.JSHal.lcd.init($0, $1, $2);
    }, _mosi, _miso, _sck);

}

void lcd_cursor_set(gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck, char * buffer)
{

    EM_ASM_({
        window.JSHal.lcd.update_display($0, $1, $2, new Uint8Array(Module.HEAPU8.buffer, $3, 4096));
    }, _mosi, _miso, _sck, buffer);
}


void lcd_copy_to_lcd(gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck, char * buffer)
{
    EM_ASM_({
        window.JSHal.lcd.update_display($0, $1, $2, new Uint8Array(Module.HEAPU8.buffer, $3, 4096));
    }, _mosi, _miso, _sck, buffer);
}

