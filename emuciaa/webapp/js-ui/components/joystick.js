(function(exports) {
    function Joystick(pins) {
        exports.BaseComponent.call(this);
        this.dataPin = pins;
        this.componentsEl = document.querySelector('#components');

        JSHal.adc.update_adc(this.dataPin.ADCx);
        JSHal.adc.update_adc(this.dataPin.ADCy);
    }

    Joystick.prototype =  Object.create(exports.BaseComponent.prototype);

    Joystick.prototype.init = function() {
        var self = this;
        var el = this._el = document.createElement('div');

        var wrapper = document.createElement('div');
        wrapper.classList.add('joystick');
        wrapper.innerHTML =
             '<object id="analog_stick-svg" data="/img/analog_stick.svg" type="image/svg+xml"></object>';
        el.appendChild(wrapper);

        el.addEventListener('click', this.handleClick.bind(this));

        el.querySelector('#analog_stick-svg').addEventListener('load', function() {
            const svgObject = el.querySelector('#analog_stick-svg');
            this.svgDoc = svgObject.contentDocument;
    
            var pin_ADCx = this.pinNameForPin(self.dataPin.ADCx);
            var txtADCx = this.svgDoc.getElementById('pin_ADCx');
            txtADCx.textContent = pin_ADCx;

            var pin_ADCy = this.pinNameForPin(self.dataPin.ADCy);
            var txtADCy = this.svgDoc.getElementById('pin_ADCy');
            txtADCy.textContent = pin_ADCy;

            var pin_SW = this.pinNameForPin(self.dataPin.SW);
            var txtSW = this.svgDoc.getElementById('pin_SW');
            txtSW.textContent = pin_SW;
    
        }.bind(this));

        this.componentsEl.appendChild(el);

     };

    Joystick.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('destroy');
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };

    Joystick.prototype.destroy = function(param) {
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

    exports.Joystick = Joystick;

})(window.JSUI);
