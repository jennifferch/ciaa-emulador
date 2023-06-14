(function() {

    var svg = document.querySelector('#board-svg');

    if (svg.contentDocument && svg.contentDocument.rootElement) {
        attachHandlers(svg.contentDocument);
    }
    else {
        svg.addEventListener('load', function() {
            attachHandlers(this.contentDocument);
        });
    }

    function attachHandlers(board) {
        JSHal.gpio.init_out(null, JSHal.gpioMap.LED1, 0);
        JSHal.gpio.init_out(null, JSHal.gpioMap.LED2, 0);
        JSHal.gpio.init_out(null, JSHal.gpioMap.LED3, 0);
        JSHal.gpio.init_out(null, JSHal.gpioMap.LEDR, 0);
        JSHal.gpio.init_out(null, JSHal.gpioMap.LEDG, 0);
        JSHal.gpio.init_out(null, JSHal.gpioMap.LEDB, 0);

        JSHal.gpio.init_in(null, JSHal.gpioMap.TEC1, 0);
        JSHal.gpio.init_in(null, JSHal.gpioMap.TEC2, 0);
        JSHal.gpio.init_in(null, JSHal.gpioMap.TEC3, 0);
        JSHal.gpio.init_in(null, JSHal.gpioMap.TEC4, 0);
        JSHal.gpio.init_in(null, JSHal.gpioMap.RESET, 0);

        var builtInLeds = {};
        builtInLeds[JSHal.gpioMap.LED1] = board.querySelector('#led_yellow');
        builtInLeds[JSHal.gpioMap.LED2] = board.querySelector('#led_red');
        builtInLeds[JSHal.gpioMap.LED3] = board.querySelector('#led_green');
        builtInLeds[JSHal.gpioMap.LEDB] = board.querySelector('#led_rgb');
        builtInLeds[JSHal.gpioMap.LEDG] = board.querySelector('#led_rgb');
        builtInLeds[JSHal.gpioMap.LEDR] = board.querySelector('#led_rgb');

        var builtInLeds_light = {};
        builtInLeds_light[JSHal.gpioMap.LED1] = board.querySelector('#led_yellow_light');
        builtInLeds_light[JSHal.gpioMap.LED2] = board.querySelector('#led_red_light');
        builtInLeds_light[JSHal.gpioMap.LED3] = board.querySelector('#led_green_light');
        builtInLeds_light[JSHal.gpioMap.LEDR] = board.querySelector('#led_red_light_rgb');
        builtInLeds_light[JSHal.gpioMap.LEDG] = board.querySelector('#led_green_light_rgb');
        builtInLeds_light[JSHal.gpioMap.LEDB] = board.querySelector('#led_blue_light_rgb');

        var builtInButtons_release = {};
        builtInButtons_release[JSHal.gpioMap.TEC1] = board.querySelector('#tec1_release');
        builtInButtons_release[JSHal.gpioMap.TEC2] = board.querySelector('#tec2_release');
        builtInButtons_release[JSHal.gpioMap.TEC3] = board.querySelector('#tec3_release');
        builtInButtons_release[JSHal.gpioMap.TEC4] = board.querySelector('#tec4_release');
        builtInButtons_release[JSHal.gpioMap.RESET] = board.querySelector('#tec_reset_release');

        var builtInButtons_push = {};
        builtInButtons_push[JSHal.gpioMap.TEC1] = board.querySelector('#tec1_push');
        builtInButtons_push[JSHal.gpioMap.TEC2] = board.querySelector('#tec2_push');
        builtInButtons_push[JSHal.gpioMap.TEC3] = board.querySelector('#tec3_push');
        builtInButtons_push[JSHal.gpioMap.TEC4] = board.querySelector('#tec4_push');
        builtInButtons_push[JSHal.gpioMap.RESET] = board.querySelector('#tec_reset_push');


        function setBuiltInLed(pin, value, type) {
            if (type !== JSHal.gpio.TYPE.DIGITAL) {
                return console.error('LED no soportado');
            }

            if (value === 1) {
                builtInLeds_light[pin].setAttribute('display', 'block');
                builtInLeds[pin].setAttribute('display', 'none');
            }else {
                builtInLeds_light[pin].setAttribute('display', 'none');
                builtInLeds[pin].setAttribute('display', 'block');
                
            }
        }

        window.JSHal.gpio.on('gpio_write', function(pin, value, type) {
            if (pin in builtInLeds) {
                setBuiltInLed(pin, value, type);
            }
        });

        Object.keys(builtInLeds).forEach(function(pin) {
            var v = window.JSHal.gpio.read(pin);
            if (v !== -1) {
                setBuiltInLed(pin, v, JSHal.gpio.TYPE.DIGITAL);
            }
        });

        Object.keys(builtInButtons_release).forEach(function(pin) {
            var button = builtInButtons_release[pin];

            var entro = false;

            button.addEventListener('mousedown', function(event) {
                console.log("button onmousedown");                
                window.JSHal.gpio.write(pin, 0); 
                builtInButtons_push[pin].setAttribute('fill', '#ccc');
                builtInButtons_release[pin].setAttribute('fill', '#1a1a1a');
                console.log("termino addEventListener");  
            });

            button.addEventListener('mouseup', function(event) {
                console.log("button onmouseup");
                window.JSHal.gpio.write(pin, 1);
                builtInButtons_release[pin].setAttribute('fill', '#4d4d4d');
                builtInButtons_push[pin].setAttribute('fill', '#e7e8e9');
            });

          
        });
    }

})();
