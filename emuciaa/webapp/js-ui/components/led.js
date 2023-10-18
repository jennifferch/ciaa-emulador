(function(exports) {
    function Led(img, pins) {
        exports.BaseComponent.call(this);

        this.img = img;
        this.dataPin = pins.DATA;
        this.componentsEl = document.querySelector('#components');
        this._on_gpio_write = this.on_gpio_write.bind(this);
    }

    Led.prototype = Object.create(exports.BaseComponent.prototype);

    Led.prototype.init = function() {
        window.JSHal.gpio.on('gpio_write', this._on_gpio_write);
        var divElement = this._el = this.element = document.createElement('div');
        divElement.classList.add('component');
        divElement.classList.add('led');

        var wrapper = document.createElement('div');
        wrapper.innerHTML =
             '<object id="led-svg" data="/img/'+this.img+'"' + 'type="image/svg+xml"></object>';
     
        divElement.appendChild(wrapper);

        divElement.addEventListener('click', this.handleClick.bind(this));

        divElement.querySelector('#led-svg').addEventListener('load', function() {
            const svgObject = divElement.querySelector('#led-svg');
            this.svgDoc = svgObject.contentDocument;
    
            var pin_LED = this.pinNameForPin(this.dataPin);
            var txtLED = this.svgDoc.getElementById('text_led_gpio');
            txtLED.textContent = pin_LED;

            this._on_gpio_write(this.dataPin, JSHal.gpio.read(this.dataPin), JSHal.gpio.get_type(this.dataPin));

            const self = this;
            this.svgDoc.addEventListener('click', function(event) {
                handleClick();
            });

            function handleClick () {
                var destroy = document.getElementById("DELETE_ID");
                while (destroy.classList.length > 0) {
                    destroy.classList.remove(destroy.classList.item(0));
                }
                destroy.classList.add('destroy');
                destroy.classList.add('enabled');

                var rectElement = self.svgDoc.getElementById("rectElement");
                rectElement.setAttribute('class', 'fil1Select');
                var polygonElement = self.svgDoc.getElementById("rectPolygonElement");
                var currentClass = polygonElement.getAttribute('class');
                if (!currentClass.includes('str0Select')) {
                  var updatedClass = currentClass.replace('str0', 'str0Select');
                  polygonElement.setAttribute('class', updatedClass);
                }
                
                destroy.addEventListener('click', function() {
                    window.removeComponent(this);
                    try {
                        while ( self._el.firstChild) {
                            self._el.removeChild(self._el.firstChild);
                          }
                    } catch (ex) {
                        console.log(ex);
                    } 
                    var destroy = document.getElementById("DELETE_ID");
                    while (destroy.classList.length > 0) {
                        destroy.classList.remove(destroy.classList.item(0));
                    }
                    destroy.classList.add('destroy');
                    destroy.classList.add('disabled');
                });
            }
        }.bind(this));

        this.componentsEl.appendChild(divElement);
    };

    Led.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
          destroy.classList.remove(destroy.classList.item(0));
        }
        destroy.classList.add('destroy');
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };

    Led.prototype.destroy = function(param) {
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

    Led.prototype.on_gpio_write = function(pin, value, type) {
        if (pin !== this.dataPin) return;

        var svg = this._el.querySelector('#led-svg');

        if (svg && svg.contentDocument && svg.contentDocument.rootElement) {
            var txtOpacity = this.svgDoc.getElementById('rect_led_status');
            var txtStatus = this.svgDoc.getElementById('text_led_status');

            if (type === JSHal.gpio.TYPE.DIGITAL) {
                value === 1 ? txtOpacity.setAttribute('fill-opacity', '0%') : txtOpacity.setAttribute('fill-opacity', '50%');
                value === 1 ? txtStatus.textContent = "Estado: ON": txtStatus.textContent = "Estado: OFF";
            }else if (type === JSHal.gpio.TYPE.PWM) {
                    //       this.element.querySelector('img').style.opacity = (value / 1024 * 0.7) + 0.3;
            }else {
                    console.error('LED no soporta el tipo', type);
            }
        }else {
           console.log("svg null");
        }                 
    };

    exports.LedRed = Led.bind(Led, 'led_red.svg');
    exports.LedBlue = Led.bind(Led, 'led_blue.svg');
    exports.LedYellow = Led.bind(Led, 'led_yellow.svg');
    exports.LedWhite = Led.bind(Led, 'led_white.svg');

})(window.JSUI);
