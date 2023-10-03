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
        el.classList.add('component');

        var wrapper = document.createElement('div');
        wrapper.classList.add('lcd');
        wrapper.innerHTML =
            '<object id="glcd-svg" data="/img/glcd_st7920_g128x64_c16x4.svg" type="image/svg+xml"></object>';
        el.appendChild(wrapper);

        el.addEventListener('click', this.handleClick.bind(this));

        this.componentsEl.appendChild(el);
        
        this._on_update_display(22, 25, 36, { length: 4096 });

    };

    Lcd128x64.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
        }
        destroy.classList.add('destroy');
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };

    Lcd128x64.prototype.destroy = function(param) {
        window.removeComponent(this);
        try {
            this.componentsEl.removeChild(param._el);
        } catch (ex) {
            console.log(ex);
        } 
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
        }
        destroy.classList.add('destroy');
        destroy.classList.add('disabled');
    };

    Lcd128x64.prototype.on_update_display = function(mosi, miso, sck, buffer) {
      //  if (this.pins.MOSI !== mosi || this.pins.MISO !== miso || this.pins.SCK !== sck) return;

      const svgObject = this._el.querySelector('#glcd-svg');
      this.svgDoc = svgObject.contentDocument;

      for (var iy = 0; iy <= 63; iy++) {
          for (var ix = 0; ix <= 127; ix++) {
            var rectId = `glcd_pixel_x${ix}_y${iy}`;
            var rect = this.svgDoc.getElementById(rectId);
        
            if (rect) {
              rect.setAttribute('class', buffer[iy * 128 + ix] === 1 ? 'glcd_pixel_on' : 'glcd_pixel_off');
            }
          }
        }
    };

    exports.Lcd128x64 = Lcd128x64;

})(window.JSUI);
