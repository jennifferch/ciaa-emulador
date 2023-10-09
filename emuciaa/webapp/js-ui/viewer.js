(function() {

    var activeComponents = [];
    var activeComponentModel = [];

    var getPeripherals = function() {
        var peripherals = window.peripheralsToLoad;
        if (peripherals && peripherals.length != 0 ) {
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

                sessionStorage.setItem('model', JSON.stringify(activeComponentModel));
                sessionStorage.setItem('model-dirty', true);
            });
    
            document.querySelector('#collapseButton').click();
        }
    };
    
    window.removeComponent = function(instance) {
        var ix = activeComponents.indexOf(instance);
        activeComponentModel.splice(ix, 1);
        sessionStorage.setItem('model', JSON.stringify(activeComponentModel));
        sessionStorage.setItem('model-dirty', true);
    };
    
    var components = [
        {   component: 'LedRed', id: 'ledRed', name: 'Red LED', pins: [ { name: 'DATA', value: [ 'GPIO0', 'GPIO1', 'GPIO2', 'GPIO3', 'GPIO4', 'GPIO5', 'GPIO6', 'GPIO7', 'GPIO8',  
                                                                                                 'LCD1', 'LCD2','LCD3', 'LCD4','LCDRS', 'LCDEN',
                                                                                                 'T_FIL0', 'T_FIL1','T_FIL2', 'T_FIL3','T_COL0', 'T_COL1', 'T_COL2']  },
                                                                         { name: 'GND', value: [ 'GND']  } ] },
        { component: 'LedBlue', id: 'ledBlue', name: 'LED Azul', pins: [ { name: 'DATA', value:  [ 'GPIO0', 'GPIO1', 'GPIO2', 'GPIO3', 'GPIO4', 'GPIO5', 'GPIO6', 'GPIO7', 'GPIO8',  
                                                                                                   'LCD1', 'LCD2','LCD3', 'LCD4','LCDRS', 'LCDEN',
                                                                                                   'T_FIL0', 'T_FIL1','T_FIL2', 'T_FIL3','T_COL0', 'T_COL1', 'T_COL2']   },
                                                                         { name: 'GND', value: [ 'GND']  } ] },
        { component: 'LedYellow', id: 'ledYellow', name: 'Yellow LED', pins: [ { name: 'DATA', value:  [ 'GPIO0', 'GPIO1', 'GPIO2', 'GPIO3', 'GPIO4', 'GPIO5', 'GPIO6', 'GPIO7', 'GPIO8',  
                                                                                                         'LCD1', 'LCD2','LCD3', 'LCD4','LCDRS', 'LCDEN',
                                                                                                         'T_FIL0', 'T_FIL1','T_FIL2', 'T_FIL3','T_COL0', 'T_COL1', 'T_COL2']  },
                                                                         { name: 'GND', value: [ 'GND']  } ] },
        { component: 'LedWhite', id: 'ledWhite', name: 'White LED', pins: [ { name: 'DATA', value: [ 'GPIO0', 'GPIO1', 'GPIO2', 'GPIO3', 'GPIO4', 'GPIO5', 'GPIO6', 'GPIO7', 'GPIO8',  
                                                                                                     'LCD1', 'LCD2','LCD3', 'LCD4','LCDRS', 'LCDEN',
                                                                                                     'T_FIL0', 'T_FIL1','T_FIL2', 'T_FIL3','T_COL0', 'T_COL1', 'T_COL2']  },
                                                                            { name: 'GND', value: [ 'GND']  } ] },
        {
            component: 'Dht11',
            id: 'dht11',
            name: 'Dht11 temperature / humidity sensor',
            pins: [ { name: 'GND', value: [ 'GND'] }, 
                { name: 'DATA', value: [ 'GPIO0', 'GPIO1', 'GPIO2', 'GPIO3', 'GPIO4', 'GPIO5', 'GPIO6', 'GPIO7', 'GPIO8',  
                                         'LCD1', 'LCD2','LCD3', 'LCD4','LCDRS', 'LCDEN',
                                         'T_FIL0', 'T_FIL1','T_FIL2', 'T_FIL3','T_COL0', 'T_COL1', 'T_COL2'] } ,
                { name: 'VCC', value: [ '3V3']  } ]
        },
        {
            component: 'Dht11Module',
            id: 'dht11Module',
            name: 'Dht11 temperature / humidity módulo',
            pins: [ { name: 'GND', value: [ 'GND'] }, 
                { name: 'DATA', value: [ 'GPIO0', 'GPIO1', 'GPIO2', 'GPIO3', 'GPIO4', 'GPIO5', 'GPIO6', 'GPIO7', 'GPIO8',  
                                         'LCD1', 'LCD2','LCD3', 'LCD4','LCDRS', 'LCDEN',
                                         'T_FIL0', 'T_FIL1','T_FIL2', 'T_FIL3','T_COL0', 'T_COL1', 'T_COL2'] } ,
                { name: 'VCC', value: [ '3V3']  } ]
        },
        {
            component: 'Lcd20x4',
            id: 'lcd20x4',
            name: 'Lcd display 20x4',
            pins: [
                { name: 'LCD', value: [ 'LCD1', 'LCD2', 'LCD3', 'LCD4'] },
                { name: 'RS', value: [ 'LCDRS' ] },
                { name: 'E', value: [ 'LCDEN' ] },
                { name: 'VCC', value: ['5V']  }]
        },
        {
            component: 'Lcd128x64',
            id: 'lcd128x64',
            name: 'GLCD 128x64',
            pins: [
                { name: 'LCD', value: [ 'LCD1', 'LCD2', 'LCD3', 'LCD4'] },
                { name: 'RS', value: [ 'LCDRS' ] },
                { name: 'E', value: [ 'LCDEN' ] },
                { name: 'VCC', value: ['5V']  }]
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
            component: 'ThermistorNTC',
            id: 'thermistorNTC',
            name: 'Thermistor NTC',
            pins: [ { name: 'ADC', value: [ 'CH1', 'CH2', 'CH3'] }, { name: 'GND', value: [ 'GNDA' ] }, { name: 'VCC', value: [ '3V3']} ]
        },
        {
            component: 'ThermistorPTC',
            id: 'thermistorPTC',
            name: 'Thermistor PTC',
            pins: [ { name: 'ADC', value: [ 'CH1', 'CH2', 'CH3'] }, { name: 'GND', value: [ 'GNDA' ] }, { name: 'VCC', value: [ '3V3']} ]
        },
        {
            component: 'Potentiometer',
            id: 'potentiometer',
            name: 'Potenciómetro',
            pins: [ { name: 'ADC', value: [ 'CH1', 'CH2', 'CH3'] }, { name: 'GND', value: [ 'GNDA' ] }, { name: 'VCC', value: [ '3V3']} ]
        },
        {
            component: 'Joystick',
            id: 'joystick',
            name: 'Analog stick',
            pins: [ { name: 'VRx', value: [ 'CH1', 'CH2', 'CH3'] }, { name: 'VRy', value: [ 'CH1', 'CH2', 'CH3'] }, 
                    { name: 'SW', value: [ 'GPIO0', 'GPIO1', 'GPIO2', 'GPIO3', 'GPIO4', 'GPIO5', 'GPIO6', 'GPIO7', 'GPIO8',  
                                           'LCD1', 'LCD2','LCD3', 'LCD4','LCDRS', 'LCDEN',
                                           'T_FIL0', 'T_FIL1','T_FIL2', 'T_FIL3','T_COL0', 'T_COL1', 'T_COL2'] },
                    { name: '+5V', value: [ '3V3'] },
                    { name: 'GND', value: [ 'GNDA' ] }]
        }
    ];
    
   Module.preRun.push(function() {
       var peripherals = window.peripheralsToLoad;
        console.log("peripherals test ",peripherals);
    
        if (sessionStorage.getItem('model-dirty')) {
            try {
                peripherals = JSON.parse(sessionStorage.getItem('model'));
            }
            catch (ex) {}
        }
    
        if (peripherals && peripherals.length != 0 ) {
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
            document.querySelector('#collapseButton').click();
        }

        Module.setStatus('En ejecución');

        var refresh = document.getElementById("refresh");
        var refreshIcon = document.getElementById("refreshIcon");
        refresh.classList.remove("disabled-refresh");
        refreshIcon.classList.remove("disabled-refresh");
        refresh.classList.add('enabled');
        refreshIcon.classList.add('enabled');
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
                if (pin.value  == "LED"){

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
                    pin.value.forEach(function(p) {
                        var opt = document.createElement('option');
                        opt.textContent = p;
                        opt.value = JSHal.gpioMap[p];
                        select.appendChild(opt);
                    });
                }  
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

    getPeripherals();
    Module.setStatus('');
    
    })();
    