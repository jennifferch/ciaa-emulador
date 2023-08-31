(function(exports) {
    function Joystick(pins) {
        exports.BaseComponent.call(this);
        this.dataPin = pins;
        this.componentsEl = document.querySelector('#components');
    }

    Joystick.prototype =  Object.create(exports.BaseComponent.prototype);

    Joystick.prototype.init = function() {
        var self = this;

        var el = this._el = document.createElement('div');
        el.classList.add('component');
        el.classList.add('thermistor');

        var wrapper = document.createElement('div');
        wrapper.classList.add('joystick');
        wrapper.innerHTML =
            '<div class="joystick-img"><img src="/img/joystick.jpeg" alt="Joystick"></div>' + 
            '<div id="joyDiv" style="width:200px;height:200px;margin-bottom:10px;float:left;margin-right:auto;"></div>'+
            '<div>'+
            'Posición X:<input id="joy3PosizioneX" type="text" /><br />'+
            'Posición Y:<input id="joy3PosizioneY" type="text" /><br />'+
            'Dirección:<input id="joy3Direzione" type="text" /><br />'+
            'X :<input id="joy3X" type="text" /></br>'+
            'Y :<input id="joy3Y" type="text" />'+
            '</div>';
        el.appendChild(wrapper);

      //  var joyDiv = document.createElement('div');
      //  joyDiv.id = 'joyDiv';
     //   el.appendChild(joyDiv);

        el.addEventListener('click', this.handleClick.bind(this));

     /*    var rangeH = document.createElement('input');
        rangeH.setAttribute('min', 0);
        rangeH.setAttribute('max', 3.3);
        rangeH.step = 0.01;
        rangeH.value = JSHal.gpio.read(this.dataPin) / 1024 * 5;
        rangeH.setAttribute('type', 'range');

        rangeH.addEventListener('change', function() {
            window.JSHal.gpio.write(self.dataPin, rangeH.value / 5 * 1024);
        });

        var rangeP = document.createElement('p');
        rangeP.classList.add('p-imagen');
        rangeP.appendChild(rangeH);

        el.appendChild(rangeP);

        var voltageP = document.createElement('p');
        var voltageMin = document.createElement('span');
        voltageMin.classList.add('voltage-min');
        voltageMin.textContent = '0V';
        var voltageMax = document.createElement('span');
        voltageMax.classList.add('voltage-max');
        voltageMax.textContent = '3.3V';

        voltageP.appendChild(voltageMin);
        voltageP.appendChild(voltageMax);

        el.appendChild(voltageP);

        var divVertical = document.createElement('div');
        divVertical.classList.add('vertical-input');

        var rangeV = document.createElement('input');
        rangeV.setAttribute('min', 0);
        rangeV.setAttribute('max', 3.3);
        rangeV.step = 0.01;
        rangeV.value = JSHal.gpio.read(this.dataPin) / 1024 * 5;
        rangeV.setAttribute('type', 'range');

        rangeV.addEventListener('change', function() {
            window.JSHal.gpio.write(self.dataPin, rangeV.value / 5 * 1024);
        });

        var rangeP = document.createElement('p');
       // rangeP.classList.add('p-imagen');
        rangeP.appendChild(rangeV);

        divVertical.appendChild(rangeP);

        el.appendChild(divVertical);

        var voltageP = document.createElement('p');
        var voltageMin = document.createElement('span');
        voltageMin.classList.add('voltage-min');
        voltageMin.textContent = '0V';
        var voltageMax = document.createElement('span');
        voltageMax.classList.add('voltage-max');
        voltageMax.textContent = '3.3V';

        voltageP.appendChild(voltageMin);
        voltageP.appendChild(voltageMax);

        el.appendChild(voltageP);*/

        this.componentsEl.appendChild(el);

        var Joy = new JoyStick('joyDiv')
        
        var joy3IinputPosX = document.getElementById("joy3PosizioneX");
        var joy3InputPosY = document.getElementById("joy3PosizioneY");
        var joy3Direzione = document.getElementById("joy3Direzione");
        var joy3X = document.getElementById("joy3X");
        var joy3Y = document.getElementById("joy3Y");
        
        setInterval(function(){ joy3IinputPosX.value=Joy.GetPosX(); }, 50);
        setInterval(function(){ joy3InputPosY.value=Joy.GetPosY(); }, 50);
        setInterval(function(){ joy3Direzione.value=Joy.GetDir(); }, 50);
        setInterval(function(){ joy3X.value=Joy.GetX(); }, 50);
        setInterval(function(){ joy3Y.value=Joy.GetY(); }, 50);
 
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
