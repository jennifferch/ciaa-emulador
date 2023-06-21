#include "display_lcd_hd44780_gpios_api.h"


void display_lcd_hd44780_gpios_init( gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck ){

    EM_ASM_({
        window.JSHal.Lcd.init($0, $1, $2);
    }, _mosi, _miso, _sck);

}

void display_lcd_hd44780_gpios_cursor_set(gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck, char * buffer)
{

    EM_ASM_({
        window.JSHal.Lcd.update_display($0, $1, $2, new Uint8Array(Module.HEAPU8.buffer, $3, 4096));
    }, _mosi, _miso, _sck, buffer);
}


void display_lcd_hd44780_gpios_copy_to_lcd(gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck, char * buffer)
{
    EM_ASM_({
        window.JSHal.Lcd.update_display($0, $1, $2, new Uint8Array(Module.HEAPU8.buffer, $3, 4096));
    }, _mosi, _miso, _sck, buffer);
}

