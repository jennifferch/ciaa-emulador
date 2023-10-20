#include "display_api.h"


void lcd_init( gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck ){

    EM_ASM_({
        window.JSHal.display.init($0, $1, $2);
    }, _mosi, _miso, _sck);

}

void lcd_cursor_set(gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck, unsigned char * buffer)
{

    EM_ASM_({
        window.JSHal.display.update_display($0, $1, $2, new Uint8Array(Module.HEAPU8.buffer, $3, 4096));
    }, _mosi, _miso, _sck, buffer);
}


void lcd_copy_to_lcd(gpioMap_t _mosi, gpioMap_t _miso, gpioMap_t _sck, unsigned char * buffer)
{
    EM_ASM_({
        window.JSHal.display.update_display($0, $1, $2, new Uint8Array(Module.HEAPU8.buffer, $3, 4096));
    }, _mosi, _miso, _sck, buffer);
}

void position_to_glcd(int x, int y)
{
    EM_ASM_({
        window.JSHal.display.glcd_update_char_position($0, $1);
    }, x, y);
}

void position_to_lcd(int x, int y)
{
    EM_ASM_({
        window.JSHal.display.lcd_update_char_position($0, $1);
    }, x, y);
}

void char_to_glcd( unsigned char * buffer)
{
    EM_ASM_({
        window.JSHal.display.glcd_update_char_display(new Uint8Array(Module.HEAPU8.buffer, $0, 64));
    }, buffer);
}

void char_to_lcd( unsigned char * buffer)
{
    EM_ASM_({
        window.JSHal.display.lcd_update_char_display(new Uint8Array(Module.HEAPU8.buffer, $0, 80));
    },buffer);
}

void bitmap_to_glcd( uint8_t* bitmap)
{
    EM_ASM_({
        window.JSHal.display.update_graphic_display(new Uint8Array(Module.HEAPU8.buffer, $0, 8192));
    },bitmap);
}

void display_clear_glcd()
{
    EM_ASM_({
        window.JSHal.display.display_clear_glcd();
    });
}

void display_clear_lcd()
{
    EM_ASM_({
        window.JSHal.display.display_clear_lcd();
    });
}
