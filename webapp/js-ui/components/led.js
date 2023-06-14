(function(exports) {
    function Led(img, pins) {
        exports.BaseComponent.call(this);

        this.img = img;
        this.dataPin = pins.LED;
        this.componentsEl = document.querySelector('#components');
        this._on_gpio_write = this.on_gpio_write.bind(this);
    }

    Led.prototype = Object.create(exports.BaseComponent.prototype);

    Led.prototype.init = function() {
        window.JSHal.gpio.on('gpio_write', this._on_gpio_write);

        var el = this._el = document.createElement('div');
        el.classList.add('component');
        el.classList.add('led');

        var img = document.createElement('img');
        img.src = '/img/' + this.img;
        img.style.width = '30px';

        img.classList.add('destroy');
        img.addEventListener('click', select)
         
        function select() {
           document.getElementById("DELETE_ID").classList.remove("disabled");
        }

       // this.createDestroyEl();
        el.appendChild(img);
        this.componentsEl.appendChild(el);
        this._on_gpio_write(this.dataPin, JSHal.gpio.read(this.dataPin), JSHal.gpio.get_type(this.dataPin));
    };

    Led.prototype.destroy = function() {
        window.JSHal.gpio.removeListener('gpio_write', this._on_gpio_write);

        window.removeComponent(this);
        this.componentsEl.removeChild(this._el);
    };

    Led.prototype.on_gpio_write = function(pin, value, type) {
        if (pin !== this.dataPin) return;

        if (type === JSHal.gpio.TYPE.DIGITAL) {
            this._el.querySelector('img').style.opacity = value === 1 ? '1' : '0.3';
        }else if (type === JSHal.gpio.TYPE.PWM) {
            this._el.querySelector('img').style.opacity = (value / 1024 * 0.7) + 0.3;
        }else {
            console.error('LED no soporta el tipo', type);
        }
    };

    exports.LedRed = Led.bind(Led, 'led_red.png');
    exports.LedBlue = Led.bind(Led, 'led_blue.png');
    exports.LedYellow = Led.bind(Led, 'led_yellow.png');
    exports.LedWhite = Led.bind(Led, 'led_white.png');

})(window.JSUI);
