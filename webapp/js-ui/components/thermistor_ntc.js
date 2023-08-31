(function(exports) {
    function ThermistorNTC(pins) {
        exports.BaseComponent.call(this);
        this.dataPin = pins;
        this.componentsEl = document.querySelector('#components');
    }

    ThermistorNTC.prototype =  Object.create(exports.BaseComponent.prototype);

    ThermistorNTC.prototype.init = function() {
        var self = this;

        var el = this._el = document.createElement('div');
        el.classList.add('component');

        el.addEventListener('click', this.handleClick.bind(this));

        var tooltip = document.createElement('div');
        tooltip.id = 'customTooltip';
        tooltip.className = 'tooltip';

        var wrapper = document.createElement('div');
        wrapper.classList.add('thermistor-ntc');
        wrapper.innerHTML =
            '<div class="thermistor-img"><img src="/img/ntcCurvaThermistor.png" alt="Thermistor NTC" width="210" height="200"></div>' +
            '<div class="thermometer thermistor-ntc-comp"><div class="dht11-before"></div><span class="dht11-content">3.22&deg;C</span><div class="dht11-after"></div></div>';
        el.appendChild(wrapper);

        var divntcrange = document.createElement('div');
        divntcrange.classList.add('thermistor-ntc-range');

        var resistanceRange = document.createElement('input');
        resistanceRange.setAttribute('min', 0);
        resistanceRange.setAttribute('max', 10000);
        resistanceRange.step = 100;
        resistanceRange.value = JSHal.gpio.read(this.dataPin.SIGNAL);
        resistanceRange.setAttribute('type', 'range');

        resistanceRange.addEventListener('change', function() {
            var selectedResistance = parseFloat(resistanceRange.value);
            self.calculateTemperature(resistanceRange.value);

            window.JSHal.gpio.write(self.dataPin.SIGNAL, resistanceRange.value);
           
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
        divntcrange.appendChild(rangeP);
        
        var voltageP = document.createElement('p');
        var voltageMin = document.createElement('span');
        voltageMin.classList.add('voltage-min');
        voltageMin.textContent = '0 Ω';
        var voltageMax = document.createElement('span');
        voltageMax.classList.add('voltage-max');
        voltageMax.textContent = '10000 Ω';

        voltageP.appendChild(voltageMin);
        voltageP.appendChild(voltageMax);

        divntcrange.appendChild(voltageP);
        el.appendChild(divntcrange);

        this.componentsEl.appendChild(el);
    };

    ThermistorNTC.prototype.calculateTemperature = function(resistance) {
        var betaValue = 3950; // Adjust this value based on your thermistor's specifications
        var kelvin = 298.15; // 25°C in Kelvin
        var resistanceRatio = resistance / 1000;
        var temperatureKelvin = betaValue / Math.log(resistanceRatio) + kelvin;
        var temperatureCelsius = temperatureKelvin - 273.15;

        this.graphTemperature(temperatureCelsius);
    };

    ThermistorNTC.prototype.graphTemperature = function(temp) {
        var heightTemp = (temp / 100) / (50 / 146);
        var topTemp = 146 - heightTemp;
        var afterTemp = document.querySelector('.thermometer .dht11-after');
        afterTemp.style.top = topTemp + 6 + 'px';
        afterTemp.style.height = heightTemp + 'px';

        document.querySelector('.thermometer .dht11-content').textContent = (temp / 100).toFixed(2) + '°C';

    };

    ThermistorNTC.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('destroy');
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };

    ThermistorNTC.prototype.destroy = function(param) {
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

    exports.ThermistorNTC = ThermistorNTC;

})(window.JSUI);
