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
        this.temp = 25.00;
        this.sample = 0; // ADC Read retuns an integer in range [0,1023] (10 bits resolution)
        this.componentsEl = document.querySelector('#components');
        JSHal.adc.update_adc(this.dataPin.ADC);
    }

    ThermistorNTC.prototype =  Object.create(exports.BaseComponent.prototype);

    ThermistorNTC.prototype.init = function() {
        var el = this._el = document.createElement('div');
        el.classList.add('component');

        var wrapper = document.createElement('div');
        wrapper.classList.add('thermistor-ntc');
        wrapper.innerHTML =
           '<object id="termistor_ntc-svg" data="/img/termistor_ntc.svg" type="image/svg+xml"></object>';
        el.appendChild(wrapper);

        el.addEventListener('click', this.handleClick.bind(this));

        el.querySelector('#termistor_ntc-svg').addEventListener('load', function() {
            const svgObject = el.querySelector('#termistor_ntc-svg');
            this.svgDoc = svgObject.contentDocument;
    
            //update pin GPIO
            var pin_ADC = this.pinNameForPin(this.dataPin.ADC);
            var txtADC = this.svgDoc.getElementById('pin_ADC');
            txtADC.textContent = pin_ADC;

            const self = this;
            this.svgDoc.addEventListener('click', function(event) {
                const clickX = event.clientX;
                const clickY = event.clientY;

                const pathThermometer = self.svgDoc.getElementById('thermometer');
                const pathThermometerBoundingBox = pathThermometer.getBoundingClientRect();

                if (isPointInsidePath(clickX, clickY, pathThermometer, pathThermometerBoundingBox)) {              
                        const lecturaTemperatura = calculateTemperature(clickY, pathThermometerBoundingBox);
                        self.temp = lecturaTemperatura;
                        self.renderTemperature();
                        self.renderResistance();
                }
            });

            function isPointInsidePath(x, y, path, boundingBox) {
                const svgObject = el.querySelector('#termistor_ntc-svg');
                this.svgDoc = svgObject.contentDocument;
                if (
                    x >= boundingBox.left &&
                    x <= boundingBox.right &&
                    y >= boundingBox.top &&
                    y <= boundingBox.bottom
                ) {
                    const svgPoint = this.svgDoc.documentElement.createSVGPoint();
                    svgPoint.x = x;
                    svgPoint.y = y;

                    const inverseTransform = path.getScreenCTM().inverse();
                    const transformedPoint = svgPoint.matrixTransform(inverseTransform);

                    return path.isPointInFill(transformedPoint);
                } else {
                    return false;
                }
            }

            function calculateTemperature(y, boundingBox) {
                const termometroAltura = boundingBox.bottom - boundingBox.top;
                const porcentajeAltura = 1 - (y - boundingBox.top) / termometroAltura;
                const lectura = porcentajeAltura * 100;
                const lecturaConDosDecimales = parseFloat(lectura.toFixed(2));
                return lecturaConDosDecimales;
            }

            self.renderTemperature();
            self.renderResistance();
        }.bind(this));
        
        this.componentsEl.appendChild(el);
    };
    
    ThermistorNTC.prototype.renderTemperature = function() {
        const svgObject = this._el.querySelector('#termistor_ntc-svg');
        this.svgDoc = svgObject.contentDocument;
        var polygonTemp = this.svgDoc.querySelector('#thermometer_dht11-after');
        var pointsTemp = polygonTemp.getAttribute("points").split(" ");

        var roundTemp = Math.round(this.temp);
        var topTemp = Math.min(100, Math.max(0, roundTemp));
        var normalizedTemp = (topTemp / 100) * 2200;
        var yT2 = 3800 - normalizedTemp;
        //update points
        pointsTemp[2] =  "1079.87," + yT2 + ".31"; 
        pointsTemp[3] =  "889.65," + yT2 + ".31"; 

        polygonTemp.setAttribute("points", pointsTemp.join(" "));

        var Temp_C = parseFloat(this.temp).toFixed(2);
        var Temp_K = parseFloat((parseFloat(Temp_C) + 273.15).toFixed(2));

        var txtTempC = this.svgDoc.querySelector('#txtTempC');
        txtTempC.textContent = "T: "+Temp_C+ '°C';
        var txtTempK = this.svgDoc.querySelector('#txtTempK');
        txtTempK.textContent = Temp_K + "K";
    };


    ThermistorNTC.prototype.renderResistance = function() {
        Temp_C = parseFloat(this.temp).toFixed(2);
        Temp_K = parseFloat((parseFloat(Temp_C) + 273.15).toFixed(2));
        R_NTC = parseFloat(Math.exp((((T0 * B_param) / Temp_K) - B_param) / T0) * R_10k).toFixed(2);

        this.updateSampleADC(R_NTC);
        this.svgDoc.querySelector('#txtR_NTC').textContent = R_NTC + 'Ω'; 
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
