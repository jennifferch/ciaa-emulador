window.JSHal.display = (function() {
    var sensors = {};

    var obj = new EventEmitter();

    obj.init = function(mosi, miso, sck) {
        obj.emit('init', mosi, miso, sck);
    };

    obj.update_display = function(mosi, miso, sck, buffer) {
        obj.emit('update_display', mosi, miso, sck, buffer);
    };

    obj.glcd_update_char_display = function(x, y, buffer) {
        obj.emit('glcd_update_char_display', x, y, buffer);
    };

    obj.lcd_update_char_display = function(x, y, buffer) {
        obj.emit('lcd_update_char_display', x, y, buffer);
    };

    obj.update_graphic_display = function( bitmap) {
        obj.emit('update_graphic_display', bitmap);
    };

    obj.display_clear_glcd = function() {
        obj.emit('display_clear_glcd');
    };

    obj.display_clear_lcd = function() {
        obj.emit('display_clear_lcd');
    };

    obj.update_lcd = function( lcd, rs, e) {
        sensors[lcd] = {
            rs: rs,
            e: e
        };
    };

    obj.declaredPins = function() {
      //  if (!(pin in sensors)) return console.error('Configuración del pin no declarado', pin);
      //  sensors[pin].rs = rs;
      return sensors;
    }

    return obj;
})();
