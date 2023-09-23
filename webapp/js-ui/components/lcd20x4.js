(function(exports) {

    var PIXEL_SIZE = 2;

    function Lcd20x4(pins) {
        exports.BaseComponent.call(this);
        this.pins = pins;
        this.componentsEl = document.querySelector('#components');
        this._on_update_display = this.on_update_display.bind(this);

      //  JSHal.adc.update_adc(this.dataPin.ADC);
    }

    Lcd20x4.prototype = Object.create(exports.BaseComponent.prototype);

    Lcd20x4.prototype.init = function() {
        window.JSHal.lcd.on('update_display', this._on_update_display);

        var el = this._el = document.createElement('div');  
        el.style.border = "1px solid black";
        el.style.marginTop = '20px';
        el.classList.add('component');
       
        var p = document.createElement('p');
        p.classList.add('description');

        p.innerHTML = 'Lcd display 20x4 (<strong>LCD</strong>: ' +
        this.pinNameForPin(this.pins.LCD) + ')';

        p.appendChild(this.createDestroyEl());
        el.appendChild(p);

        var cnvs = this.cnvs = document.createElement('canvas');
        cnvs.height = 32 * PIXEL_SIZE;
        cnvs.width = 128 * PIXEL_SIZE;

        cnvs.style.height = 32 * PIXEL_SIZE + 'px';
        cnvs.style.width = 128 * PIXEL_SIZE + 'px';

        el.appendChild(cnvs);

        this.componentsEl.appendChild(el);
        
      //  this._on_update_display(this.pins.MOSI, this.pins.MISO, this.pins.SCK, { length: 4096 });
        this._on_update_display(22, 25, 36, { length: 4096 });

    };

    Lcd20x4.prototype.destroy = function() {
        window.JSHal.lcd.removeListener('update_display', this._on_update_display);
        window.removeComponent(this);
        this.componentsEl.removeChild(this._el);
    };

    Lcd20x4.prototype.on_update_display = function(mosi, miso, sck, buffer) {
      //  if (this.pins.MOSI !== mosi || this.pins.MISO !== miso || this.pins.SCK !== sck) return;
      //  this.convert_binary_to_characters(buffer);
      /*  var x = 0;
        var y = 0;

        var ctx = this.cnvs.getContext('2d');
        for (var ix = 0; ix < buffer.length; ix++) {
            ctx.fillStyle = buffer[ix] === 1 ? '#000' : '#767c69';
            ctx.fillRect(x, y, PIXEL_SIZE, PIXEL_SIZE);

            x += PIXEL_SIZE;
            if (x === (128 * PIXEL_SIZE)) {
                x = 0;
                y += PIXEL_SIZE;
            }

        }*/

        var x = 0;
        var y = 0;
        var textContent = ''; // Variable para almacenar el texto generado
    
        var ctx = this.cnvs.getContext('2d');
        for (var ix = 0; ix < buffer.length; ix++) {
            // Dibuja el contenido en el canvas
            ctx.fillStyle = buffer[ix] === 1 ? '#000' : '#767c69';
            ctx.fillRect(x, y, PIXEL_SIZE, PIXEL_SIZE);
    
            // Genera y almacena texto basado en el valor de buffer
            textContent += buffer[ix] === 1 ? '1' : '0';
    
            x += PIXEL_SIZE;
            if (x === (128 * PIXEL_SIZE)) {
                x = 0;
                y += PIXEL_SIZE;
            }
        }
    
        // Ahora, textContent contendrá el texto generado
        console.log(textContent);
    };

    Lcd20x4.prototype.convert_binary_to_characters = function(buffer) {
       /* var printableBuffer = new Uint8Array(6); // Tamaño para "temp"

        var printableString = "";

        // Itera a través de buffer y agrega solo los caracteres imprimibles
        for (var i = 0; i < buffer.length; i += 100) {
            var decimalValue = buffer[i];
            if (decimalValue >= 32 && decimalValue <= 126) {
                printableString += String.fromCharCode(decimalValue);
            }
        }
        
        // Ahora, printableString contendrá los caracteres imprimibles
        console.log(printableString);*/


        var characterData =buffer;
        // Convierte los datos de caracteres en una cadena de texto
        var characterString = String.fromCharCode.apply(null, characterData);

        // Imprime characterString
        console.log(characterString);
      };

    exports.Lcd20x4 = Lcd20x4;

})(window.JSUI);
