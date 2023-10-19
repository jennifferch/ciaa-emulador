(function(exports) {
    function Joystick(pins) {
        exports.BaseComponent.call(this);
        this.dataPin = pins;
        this.componentsEl = document.querySelector('#components');

        JSHal.adc.update_adc(this.dataPin.VRx);
        JSHal.adc.update_adc(this.dataPin.VRy);
    }

    Joystick.prototype =  Object.create(exports.BaseComponent.prototype);

    Joystick.prototype.init = function() {
        var self = this;
        var el = this._el = document.createElement('div');
        el.classList.add('component');

        var wrapperDivMain = document.createElement('div');
        wrapperDivMain.id ="divMain";
        wrapperDivMain.classList.add('joystick');


        var wrapperDivHtml = document.createElement('div');
        wrapperDivHtml.innerHTML =
            '<div><object id="border-svg" data="/img/border_stick.svg" type="image/svg+xml"></object></div>' +
            '<div id="joyDiv" style="width:200px;height:200px;margin-bottom:10px;float:left;margin-left:auto;margin-right:auto;"></div>'+
            '<div style="margin-top: 30px;">'+
            '<p class="fil5 fnt1" style="display: inline;">x: </p><p class="fil5 fnt1" style="display: inline;" id="joy3X"></p><br>'+
            '<p class="fil5 fnt1" style="display: inline;">y: </p><p class="fil5 fnt1" style="display: inline;" id="joy3Y"></p><br>'+
            '<p class="fil5 fnt1" style="display: inline;">Dirección: </p><p class="fil5 fnt1" style="display: inline;" id="joy3Direzione"></p><br><br>'+
            '</div>' +

            '<div>'+
            '<p class="fil7 fnt1" style="display: inline;">VRx: </p><p class="fil7 fnt1" style="display: inline;" id="joyVRx"></p><br>'+
            '<p id="CHx" class="fil8 fnt1" style="display: inline;">CH1: </p><p class="fil8 fnt1" style="display: inline;" id="joyADCx"></p><br><br>'+
            '</div>'+

            '<div>'+
            '<p class="fil7 fnt1" style="display: inline;">VRy: </p><p class="fil7 fnt1" style="display: inline;" id="joyVRy"></p><br>'+
            '<p id="CHy" class="fil8 fnt1" style="display: inline;">CH2: </p><p class="fil8 fnt1" style="display: inline;" id="joyADCy"><br>'+
            '</div>';
        wrapperDivMain.appendChild(wrapperDivHtml);

        var wrapperSVG = document.createElement('div');
        wrapperSVG.innerHTML =
             '<object id="analog_stick-svg" data="/img/analog_stick_2.svg" type="image/svg+xml"></object>';
        wrapperDivMain.appendChild(wrapperSVG);

        el.appendChild(wrapperDivMain);
        this.componentsEl.appendChild(el);

        el.addEventListener('click', this.handleClick.bind(this));


        var Joy = new JoyStick('joyDiv')
        
        var joy3Direzione = document.getElementById("joy3Direzione");
        var joy3X = document.getElementById("joy3X");
        var joy3Y = document.getElementById("joy3Y");

        var joyVRx = document.getElementById("joyVRx");
        var joyVRy = document.getElementById("joyVRy");

        var joyADCx = document.getElementById("joyADCx");
        var joyADCy = document.getElementById("joyADCy");

        var CHx = document.getElementById("CHx");
        var CHy = document.getElementById("CHy");

        CHx.textContent = self.pinNameForPin(self.dataPin.VRx) + ":";
        CHy.textContent = self.pinNameForPin(self.dataPin.VRy) + ":";
        
        setInterval(function(){ joy3Direzione.textContent=Joy.GetDir(); }, 50);
        setInterval(function(){ joy3X.textContent=Joy.GetX(); }, 50);
        setInterval(function(){ joy3Y.textContent=Joy.GetY(); }, 50);
        setInterval(function(){
            var VRx = Joy.GetVRx();
            var voltage = (Math.floor(VRx/ 3.3 * 1023)* 3.3 / 1023.0).toFixed(2);
            joyVRx.textContent = voltage;
            joyADCx.textContent = Math.trunc(VRx/ 3.3 * 1023);
            window.JSHal.gpio.write(self.dataPin.VRx, VRx/ 3.3 * 1023);

        }, 50);
        setInterval(function(){ 
            var VRy = Joy.GetVRy();
            var voltage = (Math.floor(VRy/ 3.3 * 1023)* 3.3 / 1023.0).toFixed(2);
            joyVRy.textContent = voltage;
            joyADCy.textContent = Math.trunc(VRy/ 3.3 * 1023);
            window.JSHal.gpio.write(self.dataPin.VRy, VRy/ 3.3 * 1023);
        }, 50);

        el.querySelector('#border-svg').addEventListener('load', function() {
            const svgObject = el.querySelector('#border-svg');
            this.svgDoc = svgObject.contentDocument;

            const svgTrash = this.svgDoc.getElementById('trash');
            const self = this;
            this.svgDoc.addEventListener('click', function(event) {
                const clickX = event.clientX;
                const clickY = event.clientY;

                if (isPointInsideTrash(svgTrash, clickX, clickY)) {
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
                }
            });

            function isPointInsideTrash(trashElement, clickX, clickY) {
                const trashRect = trashElement.getBoundingClientRect();
                if (
                  clickX >= trashRect.left &&
                  clickX <= trashRect.right &&
                  clickY >= trashRect.top &&
                  clickY <= trashRect.bottom
                ) {
                  return true;
                } else {
                  return false;
                }
            }
        }.bind(this));

        el.querySelector('#analog_stick-svg').addEventListener('load', function() {
            const svgObject = el.querySelector('#analog_stick-svg');
            this.svgDoc = svgObject.contentDocument;
    
            var pin_ADCx = this.pinNameForPin(self.dataPin.VRx);
            var txtADCx = this.svgDoc.getElementById('pin_ADCx');
            txtADCx.textContent = pin_ADCx;

            var pin_ADCy = this.pinNameForPin(self.dataPin.VRy);
            var txtADCy = this.svgDoc.getElementById('pin_ADCy');
            txtADCy.textContent = pin_ADCy;

            var pin_SW = this.pinNameForPin(self.dataPin.SW);
            var txtSW = this.svgDoc.getElementById('pin_SW');
            txtSW.textContent = pin_SW;

            this.svgDoc.addEventListener('click', function(event) {
                handleClick();
            });

            function handleClick () {
                var destroy = document.getElementById("DELETE_ID");
                while (destroy.classList.length > 0) {
                    destroy.classList.remove(destroy.classList.item(0));
                }
                destroy.classList.add('destroy');
                destroy.classList.add('enabled');

                const borderSvgObject = el.querySelector('#border-svg');
                var rectElement = borderSvgObject.contentDocument.getElementById("rect790");
                rectElement.setAttribute('class', 'fil1Select');

                var divElement = el.querySelector('#divMain');  
                if (divElement.classList.contains('joystick')) {
                    divElement.classList.remove('joystick');
                    divElement.classList.add('joystickSelect');
                }

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
     };

    Joystick.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('destroy');
        destroy.classList.add('enabled');

      /*  const borderSvgObject = this._el.querySelector('#border-svg');
        if (borderSvgObject && borderSvgObject.contentDocument && borderSvgObject.contentDocument.rootElement) {
            var rectElement = borderSvgObject.contentDocument.getElementById("rect790");
            rectElement.setAttribute('class', 'fil1Select');
        }
        var divElement = this._el.querySelector('#divMain');  
        if (divElement.classList.contains('joystick')) {
            divElement.classList.remove('joystick');
            divElement.classList.add('joystickSelect');
        }*/

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
