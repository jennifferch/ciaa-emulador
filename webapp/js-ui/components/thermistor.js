(function(exports) {
    function Thermistor(pins) {
        exports.BaseComponent.call(this);

        this.dataPin = pins.Thermistor;

        this.componentsEl = document.querySelector('#components');
    }

    Thermistor.prototype =  Object.create(exports.BaseComponent.prototype);

    Thermistor.prototype.init = function() {
        var self = this;

        var el = this._el = document.createElement('div');
        el.classList.add('component');
        el.classList.add('thermistor');

        el.addEventListener('click', this.handleClick.bind(this));

        var range = document.createElement('input');
        range.setAttribute('min', 0);
        range.setAttribute('max', 3.3);
        range.step = 0.01;
        range.value = JSHal.gpio.read(this.dataPin) / 1024 * 5;
        range.setAttribute('type', 'range');

        range.addEventListener('change', function() {
            window.JSHal.gpio.write(self.dataPin, range.value / 5 * 1024);
        });

        var rangeP = document.createElement('p');
        rangeP.appendChild(range);

        el.appendChild(rangeP);

        var voltageP = document.createElement('p');
        var voltageMin = document.createElement('span');
        voltageMin.classList.add('voltage-min');
        voltageMin.textContent = '0V';
        var voltageMax = document.createElement('span');
        voltageMax.classList.add('voltage-max');
        voltageMax.textContent = '3.3V';

        voltageP.appendChild(voltageMin);
        voltageP.appendChild(voltageMax);

        el.appendChild(voltageP);

        this.componentsEl.appendChild(el);
    };

    Thermistor.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('destroy');
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };

    Thermistor.prototype.destroy = function() {
        window.removeComponent(this);
        param.element.remove();
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('destroy');
        destroy.classList.add('disabled');
    };

    exports.Thermistor = Thermistor;

})(window.JSUI);
