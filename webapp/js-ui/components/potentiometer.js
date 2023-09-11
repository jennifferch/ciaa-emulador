(function(exports) {

    function Potentiometer(pins) {   
        this.dataPin = pins;
        exports.BaseComponent.call(this);
        this.componentsEl = document.querySelector('#components');
        JSHal.adc.update_adc(this.dataPin.ADC);
    }

    Potentiometer.prototype =  Object.create(exports.BaseComponent.prototype);

    Potentiometer.prototype.init = function() {
        var self = this;
        var el = this._el = document.createElement('div');

        el.id = 'potentiometer';
        el.classList.add('component');
        var p = document.createElement('p');
        p.classList.add('description');

        p.innerHTML = 'Potenciómetro (<strong>ADC</strong>: ' +
        this.pinNameForPin(self.dataPin.ADC) + ')';

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

        var pValue = document.createElement('p');
        pValue.textContent = "VR: 0.0 V";
        pValue.style.display = "inline";
        pValue.style.marginLeft = '70px';
        el.appendChild(pValue);

        var range = document.createElement('input');
        range.setAttribute('min', 0);
        range.setAttribute('max', 3.3);
        range.step = 0.01;
        range.value = JSHal.gpio.read(this.dataPin.ADC)/ 1023 * 3.3;
        range.setAttribute('type', 'range');
        range.style.marginLeft = '40px';
        

        range.addEventListener('change', function() {
            range.classList.add('custom-range'); 
            window.JSHal.gpio.write(self.dataPin.ADC, range.value/ 3.3 * 1023);
            var voltage = (Math.floor(range.value/ 3.3 * 1023)* 3.3 / 1023.0).toFixed(6);
            tooltip.textContent = voltage;

            var VR = parseFloat(voltage);
            if (!isNaN(VR)) {
                pValue.textContent = 'VR: '+ VR.toFixed(2) + ' V';
              }
            tooltip.style.display = 'block';

            var R12, R23;
            R12 = (VR / 3.3) * 10000; 
            R23 = 10000 - R12; 
            if (R12 < 0) {
              R12 = 0;
              R23 = 10000;
            } else if (R23 < 0) {
              R23 = 0;
              R12 = 10000;
            }
            pResistance12.textContent = 'R12: ' + (R12 / 1000).toFixed(1) + ' KΩ';
            pResistance23.textContent = 'R23: ' + (R23 / 1000).toFixed(1) + ' KΩ';
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
        voltageMin.textContent = 'Girar Anti-horario';
        voltageMin.style.fontSize = '10px';
        var voltageMax = document.createElement('span');
        voltageMax.classList.add('voltage-max');
        voltageMax.textContent = 'Girar Horario';
        voltageMax.style.fontSize = '10px';
        voltageMax.style.marginLeft = '40px';

        voltageP.appendChild(voltageMin);
        voltageP.appendChild(voltageMax);

        el.appendChild(voltageP);

        var pResistance12 = document.createElement('p');
        pResistance12.textContent = "R12: 0 KΩ";
        pResistance12.style.marginTop = '40px';
        pResistance12.style.marginLeft = '65px';
        el.appendChild(pResistance12);

        var pResistance23 = document.createElement('p');
        pResistance23.textContent = "R23: 10 KΩ";
        pResistance23.style.marginLeft = '65px';
        el.appendChild(pResistance23);
        
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
