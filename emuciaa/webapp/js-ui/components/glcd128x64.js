(function(exports) {

const LINES = 4;  // Definir la cantidad de líneas
const CHARS_PER_LINE = 16;  // Definir la cantidad de caracteres por línea

const textLine = "".padEnd(CHARS_PER_LINE, " ");

const SCREEN_PX_X = Object.freeze(128);     // Definir la cantidad de pixeles de la pantalla GLCD en x
const SCREEN_PX_Y = Object.freeze(64);      // Definir la cantidad de pixeles de la pantalla GLCD en y

    function Glcd128x64(pins) {
        exports.BaseComponent.call(this);
        this.pins = pins;
        this.componentsEl = document.querySelector('#components');

        this.displayTextLines = Array(LINES).fill(textLine); 
        this.currentXPosition = 0; // Indice en x actual
        this.currentYPosition = 0; // Indice en y actual

        this.screen = ( new Uint8Array(SCREEN_PX_X*SCREEN_PX_Y) ).fill(0x00);
        this._on_update_char_display = this.on_update_char_display.bind(this);
        this._on_update_graphic_display = this._on_update_graphic_display.bind(this);
        this._on_display_clear = this._on_display_clear.bind(this);
        this._on_update_char_position = this.on_update_char_position.bind(this);
      }

    Glcd128x64.prototype = Object.create(exports.BaseComponent.prototype);

    Glcd128x64.prototype.init = function() {
        window.JSHal.display.on('glcd_update_char_display', this._on_update_char_display);
        window.JSHal.display.on('update_graphic_display', this._on_update_graphic_display);
        window.JSHal.display.on('display_clear_glcd', this._on_display_clear);
        window.JSHal.display.on('glcd_update_char_position', this._on_update_char_position);

        var el = this._el = document.createElement('div');  
        el.classList.add('component');

        var wrapper = document.createElement('div');
        wrapper.innerHTML =
            '<object id="glcd-svg" data="/img/glcd_st7920_g128x64_c16x4_with_pins.svg" type="image/svg+xml"></object>';
        el.appendChild(wrapper);
        el.addEventListener('click', this.handleClick.bind(this));

        el.querySelector('#glcd-svg').addEventListener('load', function() {
          const svgObject = this._el.querySelector('#glcd-svg');
          this.svgDoc = svgObject.contentDocument;
  
          const self = this;
          this.svgDoc.addEventListener('click', function(event) {
              handleClick();
              const clickX = event.clientX;
              const clickY = event.clientY;
              
              const svgTrash = self.svgDoc.getElementById('trash');
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

          function handleClick () {
              var destroy = document.getElementById("DELETE_ID");
              while (destroy.classList.length > 0) {
                  destroy.classList.remove(destroy.classList.item(0));
              }
              destroy.classList.add('destroy');
              destroy.classList.add('enabled');

              /*  var rectElement = self.svgDoc.getElementById("rectElement");
              rectElement.setAttribute('class', 'fil1Select');
              var polygonElement = self.svgDoc.getElementById("polygonElement");
              var currentClass = polygonElement.getAttribute('class');
              if (!currentClass.includes('str0Select')) {
                var updatedClass = currentClass.replace('str0', 'str0Select');
                polygonElement.setAttribute('class', updatedClass);
              }*/

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

        this.componentsEl.appendChild(el);
    };

    Glcd128x64.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
        }
        destroy.classList.add('destroy');
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };

    Glcd128x64.prototype.destroy = function(param) {
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

    Glcd128x64.prototype._on_update_graphic_display = function(bitmap) {
      this.screen = bitmap;
      this.graphicDisplay();
    };

    Glcd128x64.prototype.graphicDisplay = function() {
      const svgObject = this._el.querySelector('#glcd-svg');
      if (svgObject && svgObject.contentDocument && svgObject.contentDocument.rootElement) {
        this.svgDoc = svgObject.contentDocument;

        const bytesPerLine = SCREEN_PX_X/8;
        for( let line=0; line<SCREEN_PX_Y; line++ ) {
          for( let byte=0; byte<bytesPerLine; byte++ ) {
            for( let bit=7; bit>=0; bit-- ) {
              var  x = (7-bit) + byte*8;
              var rectId = `glcd_pixel_x${x}_y${line}`;
              var rect = this.svgDoc.getElementById(rectId);
              if( ((this.screen[byte + line*bytesPerLine]>>bit) & 1) != 0 ) {
                if (rect) {
                  rect.setAttribute('class', 'pixel_on');
                }
              } else {
                if (rect) {
                  rect.setAttribute('class', 'pixel_off');
                }
              }
            }
          }
        }
      }else {
        console.log("svg null");
      } 
    };

    Glcd128x64.prototype.on_update_char_display = function(buffer) {
        const str = this.convertToCharacter(buffer);
        this.displayStringWrite(str);
    };

    Glcd128x64.prototype.on_update_char_position = function(charPositionX, charPositionY ) {
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

    Glcd128x64.prototype.displayStringWrite = function(str) {
        const svgObject = this._el.querySelector('#glcd-svg');
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
                      var textId = `glcd_pixel_l${i}_c${e}`;
                      if (svgObject && svgObject.contentDocument && svgObject.contentDocument.rootElement) {
                          var textSvg = this.svgDoc.getElementById(textId);
                          if (textSvg) {
                            textSvg.textContent = text;
                          }
                      }
                    }
                }
              }
        }else {
          console.log("svg null");
        }    
    };

    Glcd128x64.prototype.convertToCharacter = function(buffer) {
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


    Glcd128x64.prototype._on_display_clear = function() {
    this.displayTextLines = Array(LINES).fill(textLine);
    this.currentXPosition = 0; 
    this.currentYPosition = 0; 
    this.screen = ( new Uint8Array(SCREEN_PX_X*SCREEN_PX_Y) ).fill(0x00);

    const svgObject = this._el.querySelector('#glcd-svg');
    if (svgObject && svgObject.contentDocument && svgObject.contentDocument.rootElement) {
      this.svgDoc = svgObject.contentDocument;
      for (let i = 0; i < LINES; i++) {
        for (let e = 0; e < CHARS_PER_LINE; e++) {              
              var textId = `glcd_pixel_l${i}_c${e}`;
              var textSvg = this.svgDoc.getElementById(textId);
              if (textSvg) {
                textSvg.textContent = "";
              }
        }
      }

      for( let y=0; y<=63; y++ ) {
        for( let x=0; x<=127; x++ ) {
            var rectId = `glcd_pixel_x${x}_y${y}`;
            var rect = this.svgDoc.getElementById(rectId);
            if (rect) {
                rect.setAttribute('class', 'pixel_off');
            }

          }
        }
      }
  };

  exports.Glcd128x64 = Glcd128x64;

})(window.JSUI);
