(function(exports) {

    function Potentiometer(pins) {   
        this.dataPin = pins;
        this.range = 1.65;
        exports.BaseComponent.call(this);
        this.componentsEl = document.querySelector('#components');
        JSHal.adc.update_adc(this.dataPin.ADC);
    }

    Potentiometer.prototype =  Object.create(exports.BaseComponent.prototype);

    Potentiometer.prototype.init = function() {
        var el = this._el = document.createElement('div');
        el.classList.add('component');

        var wrapper = document.createElement('div');
        wrapper.classList.add('pote');
        wrapper.innerHTML =
            '<object id="pote-svg" data="/img/potentiometer.svg" type="image/svg+xml"></object>';
        el.appendChild(wrapper);

        el.addEventListener('click', this.handleClick.bind(this));

        el.querySelector('#pote-svg').addEventListener('load', function() {
            const svgObject = el.querySelector('#pote-svg');
            this.svgDoc = svgObject.contentDocument;
    
            //update pin GPIO
            var pin_ADC = this.pinNameForPin(this.dataPin.ADC);
            var txtADC = this.svgDoc.getElementById('pin_ADC');
            txtADC.textContent = pin_ADC;
            

            const self = this;

            this.svgDoc.addEventListener('click', function(event) {
                handleClick();

                const clickX = event.clientX;
                const clickY = event.clientY;

                const poteRect = self.svgDoc.getElementById('pote-rect');
                const poteRange = self.svgDoc.getElementById('pote-range');
                const rectPoteBoundingBox = poteRect.getBoundingClientRect();

                if (isPointInsideRect(clickX, clickY, rectPoteBoundingBox)) {              
                    const range = calculateRange(clickX, rectPoteBoundingBox, poteRange);
                    window.JSHal.gpio.write(self.dataPin.ADC, range/ 3.3 * 1023);
                    var voltage = (Math.floor(range/ 3.3 * 1023)* 3.3 / 1023.0).toFixed(2);
                    var VR = parseFloat(voltage);
                    self.svgDoc.getElementById('txtVR').textContent = ": " +VR + " V";

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
                    self.svgDoc.getElementById('R12').textContent = ': ' + (R12 / 1000).toFixed(1) + ' KΩ';
                    self.svgDoc.getElementById('R23').textContent = ': ' + (R23 / 1000).toFixed(1) + ' KΩ';
                    self.svgDoc.getElementById('txtSample').textContent = self.pinNameForPin(self.dataPin.ADC)+': ' +  window.JSHal.gpio.read(self.dataPin.ADC);                
                }
            });

            function isPointInsideRect(clickX, clickY, rect) {
                return clickX >= rect.left && clickX <= rect.right &&
                       clickY >= rect.top && clickY <= rect.bottom;
            }

            function calculateRange(x, boundingBox, range) {
                const rectWidth = boundingBox.right - boundingBox.left;
                const clampedX = Math.max(boundingBox.left, Math.min(x, boundingBox.right));
                let lectura = ((clampedX - boundingBox.left) / rectWidth) * 3.3;
                if (clampedX === boundingBox.left) {
                    lectura = 0;
                } else if (clampedX === boundingBox.right) {
                    lectura = 3.3;
                }
              
                const cxMin = 2200.8;
                const cxMax = 4850.8;
                const cx = ((lectura - 0.08) / (3.28 - 0.08)) * (cxMax - cxMin) + cxMin;
                const clampedCx = Math.min(Math.max(cx, cxMin), cxMax); 
                const floatCX = parseFloat(clampedCx.toFixed(2));
                range.setAttribute("cx", floatCX);
                console.log('Lectura clampedCx:', clampedCx);
                return parseFloat(lectura.toFixed(2));
            }

            function handleClick () {
                var destroy = document.getElementById("DELETE_ID");
                while (destroy.classList.length > 0) {
                    destroy.classList.remove(destroy.classList.item(0));
                }
                destroy.classList.add('destroy');
                destroy.classList.add('enabled');
                destroy.addEventListener('click', function(param) {
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
        
        this.componentsEl.appendChild(el);

        window.JSHal.gpio.write(this.dataPin.ADC, this.range/ 3.3 * 1023);
      
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