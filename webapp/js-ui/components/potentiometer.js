(function(exports) {

    function Potentiometer(pins) {   
        this.dataPin = pins;
        exports.BaseComponent.call(this);
        this.componentsEl = document.querySelector('#components');
    }

    Potentiometer.prototype =  Object.create(exports.BaseComponent.prototype);

    Potentiometer.prototype.init = function() {
        var self = this;
        var el = this._el = document.createElement('div');

        el.id = 'potentiometer';
        el.classList.add('component');
        var p = document.createElement('p');
        p.classList.add('description');

        p.textContent = 'Potenciómetro';
        el.appendChild(p);

        var wrapper = document.createElement('div');
        wrapper.classList.add('pote');
        wrapper.innerHTML =
            '<div class="pote-img"><img src="/img/potenciometro.png" alt="Potenciómetro"  width="200" height="200"></div>';
        el.appendChild(wrapper);

        el.classList.add('pote-range');

        el.addEventListener('click', this.handleClick.bind(this));

        var tooltip = document.createElement('div');
        tooltip.id = 'customTooltip';
        tooltip.className = 'tooltip';

        var range = document.createElement('input');
        range.setAttribute('min', 0);
        range.setAttribute('max', 3.3);
        range.step = 0.01;
        range.value = JSHal.gpio.read(this.dataPin.SIGNAL)/ 1023 * 3.3;
        range.setAttribute('type', 'range');

        range.addEventListener('change', function() {
            window.JSHal.gpio.write(self.dataPin.SIGNAL, range.value/ 3.3 * 1023);
            tooltip.textContent = (Math.floor(range.value/ 3.3 * 1023)* 3.3 / 1023.0).toFixed(6);
            tooltip.style.display = 'block';
        });
     
        range.addEventListener('mouseleave', function() {
            tooltip.style.display = 'none'; 
        });

        range.addEventListener('mouseup', function() {
            tooltip.style.display = 'none'; 
        });

        var rangeP = document.createElement('p');
        rangeP.appendChild(range);
        rangeP.appendChild(tooltip);
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

    exports.Potentiometer = Potentiometer;

})(window.JSUI);
