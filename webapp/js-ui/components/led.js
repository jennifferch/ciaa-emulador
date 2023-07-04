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

        var divElement = this.element = document.createElement('div');
        divElement.classList.add('component');
        divElement.classList.add('led');

        var img = document.createElement('img');
        img.src = '/img/' + this.img;
        img.style.width = '30px';

        img.classList.add('destroy');
        img.addEventListener('click', select)
         
        function select() {
           document.getElementById("DELETE_ID").classList.remove("disabled");
        }

        divElement.appendChild(img);
        divElement.addEventListener('click', this.handleClick.bind(this));
        this.componentsEl.appendChild(divElement);
        this._on_gpio_write(this.dataPin, JSHal.gpio.read(this.dataPin), JSHal.gpio.get_type(this.dataPin));
    };

    Led.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
          destroy.classList.remove(destroy.classList.item(0));
        }
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };

    Led.prototype.destroy = function(param) {
        window.removeComponent(this);
        param.element.remove();
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('disabled');
    };

    Led.prototype.on_gpio_write = function(pin, value, type) {
        if (pin !== this.dataPin) return;

        if (type === JSHal.gpio.TYPE.DIGITAL) {
            this.element.querySelector('img').style.opacity = value === 1 ? '1' : '0.3';
        }else if (type === JSHal.gpio.TYPE.PWM) {
            this.element.querySelector('img').style.opacity = (value / 1024 * 0.7) + 0.3;
        }else {
            console.error('LED no soporta el tipo', type);
        }
    };

    exports.LedRed = Led.bind(Led, 'led_red.png');
    exports.LedBlue = Led.bind(Led, 'led_blue.png');
    exports.LedYellow = Led.bind(Led, 'led_yellow.png');
    exports.LedWhite = Led.bind(Led, 'led_white.png');

})(window.JSUI);
