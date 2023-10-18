(function(exports) {

const LINES = 4;  // Definir la cantidad de líneas
const CHARS_PER_LINE = 20;  // Definir la cantidad de caracteres por línea

const textLine = "".padEnd(CHARS_PER_LINE, " ");

const COL_PX = 5;  // Definir los píxeles por columna
const ROW_PX = 8;  // Definir los píxeles por fila

    function Lcd20x4(pins) {
        exports.BaseComponent.call(this);
        this.pins = pins;
        this.componentsEl = document.querySelector('#components');

        this.displayTextLines = Array(LINES).fill(textLine); 
        this.currentXPosition = 0; // Indice en x actual
        this.currentYPosition = 0; // Indice en y actual

        this._on_update_display = this.on_update_display.bind(this);
        this._on_update_char_display = this.on_update_char_display.bind(this);
        this._on_display_clear = this._on_display_clear.bind(this);
    }

    Lcd20x4.prototype = Object.create(exports.BaseComponent.prototype);

    Lcd20x4.prototype.init = function() {
        window.JSHal.display.on('update_display', this._on_update_display);
        window.JSHal.display.on('lcd_update_char_display', this._on_update_char_display);
        window.JSHal.display.on('display_clear_lcd', this._on_display_clear);

        var el = this._el = document.createElement('div');  
        el.classList.add('component');
       
        var wrapper = document.createElement('div');
        wrapper.innerHTML =
            '<object id="lcd-svg" data="/img/lcd_hd44780_c20x4_with_pins.svg" type="image/svg+xml"></object>';
        el.appendChild(wrapper);
        el.addEventListener('click', this.handleClick.bind(this));

        el.querySelector('#lcd-svg').addEventListener('load', function() {
          const svgObject = this._el.querySelector('#lcd-svg');
          this.svgDoc = svgObject.contentDocument;
  
          const self = this;
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

              var rectElement = self.svgDoc.getElementById("rectElement");
              rectElement.setAttribute('class', 'fil1Select');
              var polygonElement = self.svgDoc.getElementById("polygonElement");
              var currentClass = polygonElement.getAttribute('class');
              if (!currentClass.includes('str0Select')) {
                var updatedClass = currentClass.replace('str0', 'str0Select');
                polygonElement.setAttribute('class', updatedClass);
              }

              destroy.addEventListener('click', function() {
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
    };

    Lcd20x4.prototype.on_update_display = function(mosi, miso, sck, buffer) {
      const svgObject = this._el.querySelector('#lcd-svg');
      if (svgObject && svgObject.contentDocument && svgObject.contentDocument.rootElement) {
          this.svgDoc = svgObject.contentDocument;
        
          for (let l_idx = 0; l_idx < LINES; l_idx++) {
            for (let c_idx = 0; c_idx < CHARS_PER_LINE; c_idx++) {
                const charGroupId = `lcd_char_c${c_idx}_l${l_idx}`;
                for (let y_idx = 0; y_idx < ROW_PX; y_idx++) {
                    for (let x_idx = 0; x_idx < COL_PX; x_idx++) {
                        const rectId = `lcd_pixel_c${c_idx}_l${l_idx}_x${x_idx}_y${y_idx}`;
                        const rectElement = this.svgDoc.getElementById(rectId);
                        
                        if (rectElement) {
                            const ix = c_idx * COL_PX + x_idx;
                            const iy = l_idx * ROW_PX + y_idx;
                            rectElement.setAttribute('class', buffer[iy * 128 + ix] === 1 ? 'pixel_on' : 'pixel_off');
                        }
                    }
                }
            }
          }
      }else {
          console.log("svg null");
      } 
    };

    Lcd20x4.prototype.on_update_char_display = function(x, y, buffer) {
        this.displayCharPositionWrite(x, y);
        const str = this.convertToCharacter(buffer);
        this.displayStringWrite(str);
    };

    Lcd20x4.prototype.displayCharPositionWrite = function(charPositionX, charPositionY ) {
        var err = false; 
        if ( charPositionX < 0 || charPositionX > CHARS_PER_LINE - 1) {
          console.err( "ERROR: En displayCharPositionWrite(" + charPositionX + ", " + charPositionY + "); charPositionX puede tener valores de 0 a " + (CHARS_PER_LINE-1) );
          err = true; 
        }
        if ( charPositionY < 0 || charPositionY > LINES - 1) {
          console.err( "ERROR: En displayCharPositionWrite(" + charPositionX + ", " + charPositionY + "); charPositionY puede tener valores de 0 a " + (LINES-1) );    
          err = true; 
        }  
        if ( !err ) {
          this.currentXPosition = charPositionX;
          this.currentYPosition = charPositionY;
          console.log( "displayCharPositionWrite(" + this.currentXPosition + ", " + this.currentYPosition + ");");
        }
    };

    Lcd20x4.prototype.convertToCharacter = function(buffer) {
        let result = '';
        for (let i = 0; i < buffer.length; i++) {
          const charCode = buffer[i];
          let trimmedLine = '';
          if (charCode !== 0) {
            trimmedLine = String.fromCharCode(charCode);
          }else{
            trimmedLine = '';
          }
           result += trimmedLine;
        }
        return result.trimEnd(); 
    };

    Lcd20x4.prototype.displayStringWrite = function(str) {
      const svgObject = this._el.querySelector('#lcd-svg');
      if (svgObject && svgObject.contentDocument && svgObject.contentDocument.rootElement) {
          this.svgDoc = svgObject.contentDocument;

          const oldCutLeft = this.displayTextLines[this.currentYPosition].substr( 0, this.currentXPosition );
        
          const oldCutRight = this.displayTextLines[this.currentYPosition].substr( str.length + this.currentXPosition, CHARS_PER_LINE );
        
          var newTextLine = oldCutLeft + str + oldCutRight;
          newTextLine = newTextLine.substr( 0, CHARS_PER_LINE );
        
          this.displayTextLines[this.currentYPosition] = newTextLine;
        
          this.currentXPosition = str.length + this.currentXPosition; // Actualizo la posicion en x
        
          for (let i = 0; i < this.displayTextLines.length; i++) {
              const elemento = this.displayTextLines[i];
              const caracteres = [];
              for (let i = 0; i < elemento.length; i++) {
                caracteres.push(elemento.charAt(i));
              }
              for (let e = 0; e < caracteres.length; e++) {
                  const text = caracteres[e];
                  if (text != " "){
                    console.log(`Elemento ${e}: ${text}`);
                    var textId = `lcd_pixel_c${e}_l${i}`;
                    
                    var textSvg = this.svgDoc.getElementById(textId);
                    if (textSvg) {
                        textSvg.textContent = text;
                    }
                  }
              }
            }
      }else {
          console.log("svg null");
      } 
    };

    Lcd20x4.prototype._on_display_clear = function() {
        this.displayTextLines = Array(LINES).fill(textLine);
        this.currentXPosition = 0; 
        this.currentYPosition = 0; 

        const svgObject = this._el.querySelector('#lcd-svg');
        if (svgObject && svgObject.contentDocument && svgObject.contentDocument.rootElement) {
          this.svgDoc = svgObject.contentDocument;
      
            for (let i = 0; i < LINES; i++) {
              for (let e = 0; e < CHARS_PER_LINE; e++) {
                    var textId = `lcd_pixel_c${e}_l${i}`;
                    var textSvg = this.svgDoc.getElementById(textId);
                    if (textSvg) {
                      textSvg.textContent = "";
                    }
              }
            }
        }
    };

    Lcd20x4.prototype.handleClick = function(event) {
      var destroy = document.getElementById("DELETE_ID");
      while (destroy.classList.length > 0) {
          destroy.classList.remove(destroy.classList.item(0));
      }
      destroy.classList.add('destroy');
      destroy.classList.add('enabled');

      destroy.addEventListener('click', () => this.destroy(this));
    };

    Lcd20x4.prototype.destroy = function(param) {
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

    exports.Lcd20x4 = Lcd20x4;

})(window.JSUI);
