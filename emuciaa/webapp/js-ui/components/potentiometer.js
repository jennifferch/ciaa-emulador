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

        var wrapper = document.createElement('div');
        wrapper.classList.add('pote');
        wrapper.innerHTML =
            '<object id="pote-svg" data="/img/potentiometer.svg" type="image/svg+xml"></object>';
        el.appendChild(wrapper);

        el.classList.add('pote-range');

        el.addEventListener('click', this.handleClick.bind(this));

        el.querySelector('#pote-svg').addEventListener('load', function() {
            const svgObject = el.querySelector('#pote-svg');
            this.svgDoc = svgObject.contentDocument;
    
            //update pin GPIO
            var pin_ADC = this.pinNameForPin(self.dataPin.ADC);
            var txtADC = this.svgDoc.getElementById('pin_ADC');
            txtADC.textContent = pin_ADC;
            
            const circle = this.svgDoc.getElementById('pote-range');
            let isDragging = false;

            circle.addEventListener('mousedown', function(event) {
                console.log("button onmousedown");                
              
            });

            circle.addEventListener('mouseup', function(event) {
                console.log("button onmouseup");
               
            });
            
            
    
        }.bind(this));
        
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
