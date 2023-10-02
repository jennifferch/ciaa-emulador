window.JSHal.lcd = (function() {
    var sensors = {};

    var obj = new EventEmitter();

    obj.init = function(mosi, miso, sck) {
        obj.emit('init', mosi, miso, sck);
    };

    obj.update_display = function(mosi, miso, sck, buffer) {
        obj.emit('update_display', mosi, miso, sck, buffer);
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
