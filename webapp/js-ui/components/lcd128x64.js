(function(exports) {

    var PIXEL_SIZE = 2;

    function Lcd128x64(pins) {
        exports.BaseComponent.call(this);
        this.pins = pins;
        this.componentsEl = document.querySelector('#components');
        this._on_update_display = this.on_update_display.bind(this);
    }

    Lcd128x64.prototype = Object.create(exports.BaseComponent.prototype);

    Lcd128x64.prototype.init = function() {
        window.JSHal.lcd.on('update_display', this._on_update_display);

        var el = this._el = document.createElement('div');  
        el.style.border = "1px solid black";
        el.style.marginTop = '20px';
        el.classList.add('component');
       
        var p = document.createElement('p');
        p.classList.add('description');

        p.innerHTML = 'GLCD 128x64 (<strong>LCD</strong>: ' +
        this.pinNameForPin(this.pins.LCD) + ')';

        p.appendChild(this.createDestroyEl());
        el.appendChild(p);

        var cnvs = this.cnvs = document.createElement('canvas');
        cnvs.height = 32 * PIXEL_SIZE;
        cnvs.width = 128 * PIXEL_SIZE;

        cnvs.style.height = 32 * PIXEL_SIZE + 'px';
        cnvs.style.width = 128 * PIXEL_SIZE + 'px';

        el.appendChild(cnvs);

        this.componentsEl.appendChild(el);
        
      //  this._on_update_display(this.pins.MOSI, this.pins.MISO, this.pins.SCK, { length: 4096 });
        this._on_update_display(22, 25, 36, { length: 4096 });

    };

    Lcd128x64.prototype.destroy = function() {
        window.JSHal.lcd.removeListener('update_display', this._on_update_display);
        window.removeComponent(this);
        this.componentsEl.removeChild(this._el);
    };

    Lcd128x64.prototype.on_update_display = function(mosi, miso, sck, buffer) {
      //  if (this.pins.MOSI !== mosi || this.pins.MISO !== miso || this.pins.SCK !== sck) return;

        var x = 0;
        var y = 0;

        var ctx = this.cnvs.getContext('2d');
        for (var ix = 0; ix < buffer.length; ix++) {
            ctx.fillStyle = buffer[ix] === 1 ? '#000' : '#767c69';
            ctx.fillRect(x, y, PIXEL_SIZE, PIXEL_SIZE);

            x += PIXEL_SIZE;
            if (x === (128 * PIXEL_SIZE)) {
                x = 0;
                y += PIXEL_SIZE;
            }

        }
    };

    exports.Lcd128x64 = Lcd128x64;

})(window.JSUI);
