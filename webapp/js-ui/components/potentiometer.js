(function(exports) {
    function Potentiometer(pins) {
        exports.BaseComponent.call(this);

        this.dataPin = pins.Potentiometer;

        this.componentsEl = document.querySelector('#components');
    }

    Potentiometer.prototype =  Object.create(exports.BaseComponent.prototype);

    Potentiometer.prototype.init = function() {
        var self = this;

        var el = this._el = document.createElement('div');

        var wrapper = document.createElement('div');
        wrapper.classList.add('pote');
        wrapper.innerHTML =
            '<div class="pote-img"><img src="/img/potenciometro.jpeg" alt="Descripción de la imagen"></div>';
        el.appendChild(wrapper);


        el.classList.add('component');
        el.classList.add('thermistor');

        el.addEventListener('click', this.handleClick.bind(this));

        var range = document.createElement('input');
        range.setAttribute('min', 0);
        range.setAttribute('max', 3.3);
        range.step = 0.01;
        range.value = JSHal.gpio.read(1) / 1024 * 5;
        range.setAttribute('type', 'range');

        range.addEventListener('change', function() {
            window.JSHal.gpio.write(1, range.value / 5 * 1024);
        });

        var rangeP = document.createElement('p');
        rangeP.appendChild(range);

        el.appendChild(rangeP);

        var voltageP = document.createElement('p');
        var voltageMin = document.createElement('span');
        voltageMin.classList.add('voltage-min');
        voltageMin.textContent = 'Left';
        var voltageMax = document.createElement('span');
        voltageMax.classList.add('voltage-max');
        voltageMax.textContent = 'Right';

        voltageP.appendChild(voltageMin);
        voltageP.appendChild(voltageMax);

        el.appendChild(voltageP);

        this.componentsEl.appendChild(el);
    };

    Potentiometer.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('destroy');
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };

    Potentiometer.prototype.destroy = function(param) {
        window.removeComponent(this);
        this.componentsEl.removeChild(this._el);
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('destroy');
        destroy.classList.add('disabled');
    };

    exports.Potentiometer = Potentiometer;

})(window.JSUI);
