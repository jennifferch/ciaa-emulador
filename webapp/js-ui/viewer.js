(function() {

    var activeComponents = [];
    var activeComponentModel = [];
    
    window.removeComponent = function(instance) {
        var ix = activeComponents.indexOf(instance);
        activeComponentModel.splice(ix, 1);
        sessionStorage.setItem('model', JSON.stringify(activeComponentModel));
        sessionStorage.setItem('model-dirty', true);
    };
    
    var components = [
        {   component: 'LedRed', 
            id: 'ledRed', 
            name: 'Red LED', 
            pins: [ 'LED' ] },
        { component: 'LedBlue', id: 'ledBlue', name: 'Blue LED', pins: [ 'LED' ] },
        { component: 'LedYellow', id: 'ledYellow', name: 'Yellow LED', pins: [ 'LED' ] },
        { component: 'LedWhite', id: 'ledWhite', name: 'White LED', pins: [ 'LED' ] },
        {
            component: 'Dht11',
            id: 'dht11',
            name: 'Dht11 temperature / humidity sensor',
            pins: [ { name: 'SDA/SDI', value: [ 'GND'] }, 
            { name: 'SIGNAL', value: [ 'GPIO1']  } ,
             { name: 'VCC', value: [ '3V3']  } ]
        },
        {
            component: 'Lcd20x4',
            id: 'lcd20x4',
            name: 'LCD display',
            pins: [
                { name: 'MOSI', value: [ 'p5', 'p11' ] },
                { name: 'MISO', value: [ 'p6', 'p12' ] }]
        },
        {
            component: 'Lcd16x4',
            id: 'lcd16x4',
            name: 'LCD display',
            pins: [
                { name: 'SPI_MOSI', value: [ 'p5', 'p11' ] },
                { name: 'SPI_MISO', value: [ 'p6', 'p12' ] }]
        },
        {
            component: 'Servo',
            id: 'motorServo',
            name: 'Motor Servo',
            pins: [ { name: 'SDA/T_FIL1(SERVO0)', value: [ 'PWM'] }, 
             { name: 'VCC', value: ['5V']  } ,
             { name: 'GND', value: [ 'Ground']  }]
        },
        {
            component: 'Termistor',
            id: 'termistor',
            name: 'Termistor',
            pins: [ { name: 'SDA/T_FIL1(SERVO0)', value: [ 'PWM'] }, 
             { name: 'VCC', value: ['5V']  } ,
             { name: 'GND', value: [ 'Ground']  }]
        }

    ];
    
   Module.preRun.push(function() {
        var peripherals = window.peripheralsToLoad;
        console.log("peripherals ",peripherals);
    
        if (sessionStorage.getItem('model-dirty')) {
            try {
                peripherals = JSON.parse(sessionStorage.getItem('model'));
            }
            catch (ex) {}
        }
    
        if (peripherals) {
            peripherals.forEach(function(m) {
                var args = m.args;
                Object.keys(args).forEach(function(k) {
                    if (typeof args[k] === 'string' && args[k].indexOf('gpioMap.') === 0) {
                        args[k] = JSHal.gpioMap[args[k].replace('gpioMap.', '')];
                    }
                });
    
                var component = new window.JSUI[m.component](args);
                component.init();
                activeComponents.push(component);
                activeComponentModel.push(m);
            });
    
            sessionStorage.setItem('model', JSON.stringify(activeComponentModel));
            sessionStorage.setItem('model-dirty', true);
        }
    });


    const component_grid_item = document.querySelectorAll('.editor__component_item');
    component_grid_item.forEach(box => {
        box.addEventListener('mousedown', mousedown)
    });

    function mousedown(e) {
        document.querySelector('#overlay').style.display = 'flex';
        var obj = components[components.findIndex(item => item.id === e.currentTarget.id)];
        document.getElementById("component").innerHTML = obj.name;
        var pinsEl = document.querySelector('#pins');
        pinsEl.innerHTML = '';
    
        obj.pins.forEach(function(pin) {
            var label = document.createElement('label');
            label.textContent = typeof pin === 'object' ? pin.name : pin;
            var select = document.createElement('select');
    
            if (typeof pin === 'object') {
                select.dataset.pin = pin.name;
    
                pin.value.forEach(function(p) {
                    var opt = document.createElement('option');
                    opt.textContent = p;
                    opt.value = JSHal.gpioMap[p];
                    select.appendChild(opt);
                });
            }
            else {
                select.dataset.pin = pin;

                if (pin == "LED"){

                    const list = Object.keys(JSHal.gpioMap);
                    const iT_FIL1 = list.indexOf('T_FIL1');
                    const listLcd = list.slice(iT_FIL1);
                    listLcd.map(function(p) {
                        var opt = document.createElement('option');
                        opt.textContent = p;
                        opt.value = JSHal.gpioMap[p];
                        select.appendChild(opt);
                    });
                }else{
                    Object.keys(JSHal.gpioMap).map(function(p) {
                        var opt = document.createElement('option');
                        opt.textContent = p;
                        opt.value = JSHal.gpioMap[p];
                        select.appendChild(opt);
                    });
                }
            }
            pinsEl.appendChild(label);
            pinsEl.appendChild(select);
        });

        document.querySelector('#add-component-btn').onclick = function() {
            var args = [].reduce.call(pinsEl.querySelectorAll('#pins select'), function(curr, select) {
                var s = select.options[select.options.selectedIndex];
                curr[select.dataset.pin] = Number(s.value);
                return curr;
            }, {});
            console.log('args reduce call ', args);
            var component = new window.JSUI[obj.component](args);
            component.init();
            activeComponents.push(component);
            activeComponentModel.push({ component: obj.component, args: args });
            sessionStorage.setItem('model', JSON.stringify(activeComponentModel));
            sessionStorage.setItem('model-dirty', true);
            document.querySelector('#overlay').style.display = 'none';

            document.querySelector('#collapseButton').click();
        };
    };

    document.querySelector('#overlay').onclick = function(e) {
        if (e.target === e.currentTarget) {
            this.style.display = 'none';
        }
    };
    
    })();
    