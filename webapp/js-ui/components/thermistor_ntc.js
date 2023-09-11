(function(exports) {
    const adc_resolution = 1023.0; // 1023 for 10 bit resolution ADC of EDU-CIAA
    const Vsupply = 3.3;           // Power supply voltage (3.3V) 
    const R_10k = 9840;            // 10k resistor measured resistance in Ohms (other element in the voltage divider)
    const B_param = 3700;          // B-coefficient of the thermistor
    const T0 = 298.15;             // 25°C in Kelvin

    var Temp_K; // Temperature measured by the thermistor (Kelvin)
    var Vout;   // Voltage divider output
    var R_NTC;  // NTC thermistor resistance in Ohms
    var Temp_C;

    function ThermistorNTC(pins) {
        exports.BaseComponent.call(this);
        this.dataPin = pins;
        this.temp = 2500;
        this.sample = 0; // ADC Read retuns an integer in range [0,1023] (10 bits resolution)
        this.componentsEl = document.querySelector('#components');
        JSHal.adc.update_adc(this.dataPin.ADC);
    }

    ThermistorNTC.prototype =  Object.create(exports.BaseComponent.prototype);

    ThermistorNTC.prototype.init = function() {
        var self = this;

        var el = this._el = document.createElement('div');
        el.classList.add('component');
        el.style.marginTop = '20px';

        var p = document.createElement('p');
        p.classList.add('description');

        p.innerHTML = 'Thermistor NTC ( <strong>ADC</strong>: ' +
        this.pinNameForPin(self.dataPin.ADC) + ')';

        el.appendChild(p);

        el.addEventListener('click', this.handleClick.bind(this));

        var tooltip = document.createElement('div');
        tooltip.id = 'customTooltip';
        tooltip.className = 'tooltip';

        var wrapper = document.createElement('div');
        wrapper.classList.add('thermistor-ntc');
        wrapper.innerHTML =
            '<div class="thermistor-img"><img src="/img/ntcCurvaThermistor.png" alt="Thermistor NTC" width="210" height="200"></div>' +
            '<div class="thermometer thermistor-ntc-comp"><div class="dht11-before"></div><div style="margin-top:-20px; margin-left:-5px"><span class="dht11-content">3.22&deg;C</span></div>' +
            '<div style="margin-top:-222px; margin-left:-50px"><span class="kelvin-content">3.22&deg;K</span></div>'+
            '<div style="margin-top:-50px; margin-left:-5px"><span>R_NTC:</span></div>'+
            '<div style="margin-top:-133px; margin-left:-5px; font-weight: normal;"><span class="ohmn-content">9840.00Ω</span></div><div class="dht11-after"></div></div>';
        el.appendChild(wrapper);

        var divntcrange = document.createElement('div');
        divntcrange.classList.add('thermistor-ntc-range');


        this.tempEl = el.querySelector('.thermometer');
        [].forEach.call(el.querySelectorAll('.thermistor-ntc-comp'), function(c) {
            c.onclick = this.change.bind(this);
        }.bind(this));

        this.componentsEl.appendChild(el);

        this.renderTemperature();
        this.renderResistance();
    };

    ThermistorNTC.prototype.calculateTemperature = function(R_NTC) {
        Temp_K = ((T0 * B_param) / (T0 * Math.log(R_NTC / R_10k) + B_param)).toFixed(2); // Temperature in Kelvin
        Temp_C = (Temp_K - 273.15).toFixed(2);

        this.temp = Math.floor(Temp_C * 100);
        if (this.temp < 0) this.temp = 0;
        if (this.temp > 10000) this.temp = 10000; 
        this.renderTemperature();

        this.tempEl.querySelector('.thermometer .dht11-content').textContent = Temp_C + '°C';
        this.tempEl.querySelector('.thermometer .kelvin-content').textContent = Temp_K + 'K';       
    };

    
    ThermistorNTC.prototype.renderTemperature = function() {
        // 0..146, max temp is 100 degrees
        var height = (this.temp / 100) / (100 / 146);
        var top = 146 - height;

        var after = this.tempEl.querySelector('.thermometer .dht11-after');
        after.style.top = top + 6 + 'px';
        after.style.height = height + 'px';

        this.tempEl.querySelector('.thermometer .dht11-content').textContent = (this.temp / 100).toFixed(2) + '°C';
    };


    ThermistorNTC.prototype.renderResistance = function() {
        Temp_C = parseFloat((this.temp / 100).toFixed(2)); 
        Temp_K = parseFloat((Temp_C + 273.15).toFixed(2)); 
        R_NTC = parseFloat(Math.exp((((T0 * B_param) / Temp_K) - B_param) / T0) * R_10k).toFixed(2);

        this.updateSampleADC(R_NTC);
        this.tempEl.querySelector('.thermometer .kelvin-content').textContent = Temp_K + 'K';       
        this.tempEl.querySelector('.thermometer .ohmn-content').textContent = R_NTC + 'Ω'; 
    };

    ThermistorNTC.prototype.updateSampleADC= function(R_NTC) {
        let R_NTC_float = parseFloat(R_NTC);
        let R_10k_float = parseFloat(R_10k);
        let Vsupply_float = parseFloat(Vsupply);    
        let VoutT = (R_NTC_float * Vsupply_float) / (R_10k_float + R_NTC_float);
        Vout = parseFloat(VoutT.toFixed(2)); 

        this.sample = parseFloat((Vout * 1023.0 / Vsupply).toPrecision(4));
        console.log('this.sample ', this.sample);
        window.JSHal.gpio.write(this.dataPin.ADC, this.sample);     
    };

    ThermistorNTC.prototype.change = function(ev) {
        // this reflows... but I don't feel like fixing it
        var y = ev.pageY - ev.currentTarget.offsetTop;
        if (y < 10) y = 10;
        y -= 10;
        if (ev.currentTarget === this.tempEl) {
            this.temp = (1 - (y / 155)) * 10000 | 0; 
            if (this.temp < 0) this.temp = 0;
            if (this.temp > 10000) this.temp = 10000; 
            this.renderTemperature();
            this.renderResistance();
        }
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
