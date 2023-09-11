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
        el.classList.add('component');
        el.classList.add('thermistor');

        var p = document.createElement('p');
        p.classList.add('description');

        p.innerHTML = 'Joystick ( <strong>ADCx</strong>: ' +
        this.pinNameForPin(this.dataPin.ADCx) + 
        ', <strong>ADCy</strong>: ' +
        this.pinNameForPin(this.dataPin.ADCy) + 
        ', <strong>SW</strong>: ' +
        this.pinNameForPin(this.dataPin.SW) + 
        ')';

        el.appendChild(p);

        var wrapper = document.createElement('div');
        wrapper.classList.add('joystick');
        wrapper.innerHTML =
            '<div class="joystick-img"><img src="/img/joystick.jpeg" alt="Joystick"></div>' + 
            '<div id="joyDiv" style="width:200px;height:200px;margin-bottom:10px;float:left;margin-left:auto;margin-right:auto;"></div>'+
            '<div style="margin-left:auto;margin-right:auto;width:200px;text-align: center;">'+
            '<p style="display: inline;">x: </p><p style="display: inline;" id="joy3X"></p><br>'+
            '<p style="display: inline;">y: </p><p style="display: inline;" id="joy3Y"></p><br>'+
            '<p style="display: inline;">Dirección: </p><p style="display: inline;" id="joy3Direzione"></p><br><br>'+
            '</div>' +

            '<div style="margin-left:auto;margin-right:auto;width:200px;text-align: left;">'+
            '&nbsp;&nbsp;&nbsp;&nbsp<p style="display: inline;">VRx :</p><p style="display: inline;" id="joyVRx"></p>'+
            '&nbsp;&nbsp;&nbsp;&nbsp<p style="display: inline;">ADCx :</p><p style="display: inline;" id="joyADCx"></p>'+
            '</div>'+

            '<div style="margin-left:auto;margin-right:auto;width:200px;text-align: left;">'+
            '&nbsp;&nbsp;&nbsp;&nbsp<p style="display: inline;">VRy :</p><p style="display: inline;" id="joyVRy"></p>'+
            '&nbsp;&nbsp;&nbsp;&nbsp<p style="display: inline;">ADCy :</p><p style="display: inline;" id="joyADCy"></p>'+
            '</div>';
        el.appendChild(wrapper);

        el.addEventListener('click', this.handleClick.bind(this));

        this.componentsEl.appendChild(el);

        var Joy = new JoyStick('joyDiv')
        
        var joy3Direzione = document.getElementById("joy3Direzione");
        var joy3X = document.getElementById("joy3X");
        var joy3Y = document.getElementById("joy3Y");

        var joyVRx = document.getElementById("joyVRx");
        var joyVRy = document.getElementById("joyVRy");

        var joyADCx = document.getElementById("joyADCx");
        var joyADCy = document.getElementById("joyADCy");
        
        setInterval(function(){ joy3Direzione.textContent=Joy.GetDir(); }, 50);
        setInterval(function(){ joy3X.textContent=Joy.GetX(); }, 50);
        setInterval(function(){ joy3Y.textContent=Joy.GetY(); }, 50);
        setInterval(function(){
            var VRx = Joy.GetVRx();
            var voltage = (Math.floor(VRx/ 3.3 * 1023)* 3.3 / 1023.0).toFixed(2);
            joyVRx.textContent = voltage;
            joyADCx.textContent = Math.trunc(VRx/ 3.3 * 1023);
            window.JSHal.gpio.write(self.dataPin.ADCx, VRx/ 3.3 * 1023);

        }, 50);
        setInterval(function(){ 
            var VRy = Joy.GetVRy();
            var voltage = (Math.floor(VRy/ 3.3 * 1023)* 3.3 / 1023.0).toFixed(2);
            joyVRy.textContent = voltage;
            joyADCy.textContent = Math.trunc(VRy/ 3.3 * 1023);
            window.JSHal.gpio.write(self.dataPin.ADCy, VRy/ 3.3 * 1023);
        }, 50);
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
