(function(exports) {
    function ThermistorPTC(pins) {
        exports.BaseComponent.call(this);
        this.dataPin = pins;

        this.componentsEl = document.querySelector('#components');
    }

    ThermistorPTC.prototype =  Object.create(exports.BaseComponent.prototype);

    ThermistorPTC.prototype.init = function() {
        var self = this;

        var el = this._el = document.createElement('div');
        el.classList.add('component');

        var p = document.createElement('p');
        p.classList.add('description');

        p.textContent = 'Thermistor PTC ( ADC: ' +
        this.pinNameForPin(self.dataPin.ADC) + ')';

        el.appendChild(p);

        el.addEventListener('click', this.handleClick.bind(this));

        var tooltip = document.createElement('div');
        tooltip.id = 'customTooltip';
        tooltip.className = 'tooltip';

        var wrapper = document.createElement('div');
        wrapper.classList.add('thermistor-ptc');
        wrapper.innerHTML =
            '<div class="thermistor-ptc-img"><img src="/img/ptcCurvaThermistor.jpeg" alt="Thermistor PTC" width="210" height="200"></div>' +
            '<div class="thermometer thermistor-ptc-comp"><div class="dht11-before"></div><span class="dht11-content">3.22&deg;C</span><div class="dht11-after"></div></div>';
        el.appendChild(wrapper);

        var divptcrange = document.createElement('div');
        divptcrange.classList.add('thermistor-ptc-range');

        var resistanceRange = document.createElement('input');
        resistanceRange.setAttribute('min', 0);
        resistanceRange.setAttribute('max', 10000);
        resistanceRange.step = 100;
        resistanceRange.value = JSHal.gpio.read(this.dataPin.ADC);
        resistanceRange.setAttribute('type', 'range');

        resistanceRange.addEventListener('change', function() {
            var selectedResistance = parseFloat(resistanceRange.value);
            self.graphTemperature(resistanceRange.value);

            window.JSHal.gpio.write(self.dataPin.ADC, resistanceRange.value);
           
            tooltip.textContent = resistanceRange.value;
            tooltip.style.display = 'block';        
        });

        resistanceRange.addEventListener('mouseleave', function() {
            tooltip.style.display = 'none'; 
        });

        resistanceRange.addEventListener('mouseup', function() {
            tooltip.style.display = 'none'; 
        });

        var rangeP = document.createElement('p');
        rangeP.appendChild(resistanceRange);
        rangeP.appendChild(tooltip);
        divptcrange.appendChild(rangeP);

        var voltageP = document.createElement('p');
        var voltageMin = document.createElement('span');
        voltageMin.classList.add('voltage-min');
        voltageMin.textContent = '0 Ω';
        var voltageMax = document.createElement('span');
        voltageMax.classList.add('voltage-max');
        voltageMax.textContent = '10000 Ω';

        voltageP.appendChild(voltageMin);
        voltageP.appendChild(voltageMax);

        divptcrange.appendChild(voltageP);
        el.appendChild(divptcrange);

        this.componentsEl.appendChild(el);
    };

    ThermistorPTC.prototype.calculateTemperature = function(resistance) {
        // Constants for the PTC
        var referenceResistance = 1000; // Resistance at a reference temperature (e.g., 25°C)
        var referenceTemperature = 25; // Reference temperature in °C
        var betaValue = 2000; // Adjust this value based on your PTC's specifications

        // Calculate the temperature using the Steinhart-Hart equation for PTCs
        var kelvin = 273.15;
        var temperatureKelvin = (1 / ((Math.log(resistance / referenceResistance) / betaValue) + (1 / (referenceTemperature + kelvin)))) - kelvin;
       
        return temperatureKelvin;
    };

    ThermistorPTC.prototype.graphTemperature = function(resistance) {
        var temperature = this.calculateTemperature(resistance);
        var heightTemp = (temperature - 25) / (110 - 25) * 146; // Convert temperature to a height within the 0-146 pixel range
        var topTemp = 146 - heightTemp;
        var afterTemp = document.querySelector('.thermometer .dht11-after');
        afterTemp.style.top = topTemp + 'px';
        afterTemp.style.height = heightTemp + 'px';
    
        document.querySelector('.thermometer .dht11-content').textContent = temperature.toFixed(2) + '°C';
    };

    ThermistorPTC.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('destroy');
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };

    ThermistorPTC.prototype.destroy = function(param) {
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

    exports.ThermistorPTC = ThermistorPTC;

})(window.JSUI);
