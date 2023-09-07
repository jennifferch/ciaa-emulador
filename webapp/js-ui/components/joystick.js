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

        var p = document.createElement('p');
        p.classList.add('description');

        p.textContent = 'Joystick ( SIGNAL: ' +
        this.pinNameForPin(self.dataPin.SIGNAL) + ')';

        el.appendChild(p);

        var wrapper = document.createElement('div');
        wrapper.classList.add('joystick');
        wrapper.innerHTML =
            '<div class="joystick-img"><img src="/img/joystick.jpeg" alt="Joystick"></div>' + 
            '<div id="joyDiv" style="width:200px;height:200px;margin-bottom:10px;float:left;margin-right:auto;"></div>'+
            '<div>'+
            '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;X:<input id="joy3X" type="text" /><br />'+
            '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Y:<input id="joy3Y" type="text" /><br />'+
            'Dirección:<input id="joy3Direzione" type="text" /><br /><br />'+
            '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;VRx :<input id="joy3X" type="text" /></br>'+
            '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;VRy :<input id="joy3Y" type="text" /></br>'+
            '&nbsp;&nbsp;&nbsp;&nbsp;ADCx :<input id="joy3X" type="text" /></br>'+
            '&nbsp;&nbsp;&nbsp;&nbsp;ADCy :<input id="joy3Y" type="text" />'+
            '</div>';
        el.appendChild(wrapper);

        el.addEventListener('click', this.handleClick.bind(this));

        this.componentsEl.appendChild(el);

        var Joy = new JoyStick('joyDiv')
        
        var joy3IinputPosX = document.getElementById("joy3PosizioneX");
        var joy3InputPosY = document.getElementById("joy3PosizioneY");
        var joy3Direzione = document.getElementById("joy3Direzione");
        var joy3X = document.getElementById("joy3X");
        var joy3Y = document.getElementById("joy3Y");
        
      //  setInterval(function(){ joy3IinputPosX.value=Joy.GetPosX(); }, 50);
      //  setInterval(function(){ joy3InputPosY.value=Joy.GetPosY(); }, 50);
      //  setInterval(function(){ joy3Direzione.value=Joy.GetDir(); }, 50);
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
