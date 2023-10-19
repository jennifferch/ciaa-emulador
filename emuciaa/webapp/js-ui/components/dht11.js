(function(exports) {

    function Dht11(img, pins) {
        this.img = img;
        this.pins = pins;
        this.temp = 20.50;
        this.humidity = 30.00;
        this.geolocationTimer;
        this.geolocationTimeout = 5000; 
        this.userOption = false; 

        this.getTemperatureHumidity();
        exports.BaseComponent.call(this);
        this.components = document.querySelector('#components');  
    }

    Dht11.prototype = Object.create(exports.BaseComponent.prototype);

    Dht11.prototype.getTemperatureHumidity = function() {
        this.request = new XMLHttpRequest();
        if (navigator.geolocation) {
            var self = this; 
            this.geolocationTimer = setTimeout(function() {
                self.getDefaultCityFromAPI(self.request); 
            }, this.geolocationTimeout);
            this.getNavigatorCityFromAPI(self.request);
        } else {
            this.getDefaultCityFromAPI(request);
        }
    }   

    Dht11.prototype.getNavigatorCityFromAPI = function(request) {
        var self = this; 
        navigator.geolocation.getCurrentPosition(function(position) {
            clearTimeout(self.geolocationTimer);
            const apiKey = "16df248820826ba8bd599c2ce8648dd2"; 
            const latitude = position.coords.latitude;
            const longitude = position.coords.longitude;         
            const apiUrl = `https://api.openweathermap.org/data/2.5/weather?lat=${latitude}&lon=${longitude}&appid=${apiKey}&units=metric`;
                request.onreadystatechange = function() {
                    if (request.readyState === XMLHttpRequest.DONE) {
                        if (request.status === 200) {
                            const data = JSON.parse(request.responseText);
                            const cityName = data.name;
                            console.log( "cityName " + cityName);
                            console.log( "data Temperatura " + data.main.temp);
                            console.log( "data Humedad " + data.main.humidity);
                            this.temp = data.main.temp;
                            this.humidity = data.main.humidity;
                            self.renderTemperature(this.temp);
                            self.renderHumidity(this.humidity);
                            JSHal.dht11.update_humidity(self.pins.DATA, JSHal.gpioMap.GND, this.humidity + "00"); 
                        }
                    }  
                }   
                request.open('GET', apiUrl, true);
                request.send(); 
        });
    };

    Dht11.prototype.getDefaultCityFromAPI = function(request) {
        var self = this;
        clearTimeout(self.geolocationTimer);
        console.log("La geolocalización no es soportada por este navegador.");
        request.open('GET', 'https://api.openweathermap.org/data/2.5/weather?q=Buenos%20Aires&appid=16df248820826ba8bd599c2ce8648dd2&units=metric', true);                   
        request.onload = function () {
                const data = JSON.parse(this.response);
                console.log( "data Temperatura" + data.main.temp);
                console.log( "data Humedad" + data.main.humidity);
                this.temp = data.main.temp;
                this.humidity = data.main.humidity;
                self.renderTemperature(this.temp);
                self.renderHumidity(this.humidity);    
                JSHal.dht11.update_humidity(self.pins.DATA, JSHal.gpioMap.GND, this.humidity + "00");            
        }
        request.send();
    };

    Dht11.prototype.init = function() {
        var divElement = this.element = document.createElement('div');
        this.createHTML(divElement);

        divElement.addEventListener('click', this.handleClick.bind(this));

        divElement.querySelector('#dht11-svg').addEventListener('load', function() {
            const svgObject = divElement.querySelector('#dht11-svg');
            this.svgDoc = svgObject.contentDocument;

            //update pin GPIO
            var pin_GPIO = this.pinNameForPin(this.pins.DATA);
            var txtGPIO = this.svgDoc.getElementById('pin_GPIO');
            txtGPIO.textContent = pin_GPIO;

            const self = this;
            this.svgDoc.addEventListener('click', function(event) {
                handleClick();

                const clickX = event.clientX;
                const clickY = event.clientY;

                const circleManual = self.svgDoc.getElementById('tempManual');
                const circleLocal = self.svgDoc.getElementById('tempLocal');
                const pathThermometer = self.svgDoc.getElementById('thermometer');
                const pathHumidity = self.svgDoc.getElementById('humidity');

                const circleManualBoundingBox = circleManual.getBoundingClientRect();
                const circleLocalBoundingBox = circleLocal.getBoundingClientRect();
                const pathThermometerBoundingBox = pathThermometer.getBoundingClientRect();
                const pathHumidityBoundingBox = pathHumidity.getBoundingClientRect();

                const svgTrash = self.svgDoc.getElementById('trash');

                if (isPointInsideCircle(clickX, clickY, circleManualBoundingBox)){
                    self.userOption = true;
                    circleManual.setAttribute("class", "fil19"); 
                    circleLocal.setAttribute("class", "fil0 str4");
                    self.renderTemperature(self.temp);
                    self.renderHumidity(self.humidity);
                    JSHal.dht11.update_humidity(self.pins.DATA, JSHal.gpioMap.GND, self.humidity + "00");    
                }else if ( isPointInsideCircle(clickX, clickY, circleLocalBoundingBox)){
                    self.userOption = false;
                    circleLocal.setAttribute("class", "fil19");
                    circleManual.setAttribute("class", "fil0 str4"); 
                    self.getTemperatureHumidity();
                }

                if (isPointInsidePath(clickX, clickY, pathThermometer, pathThermometerBoundingBox)) {
                    if(self.userOption){                  
                        const lecturaTemperatura = calculateTemperature(clickY, pathThermometerBoundingBox);
                        self.renderTemperature(lecturaTemperatura);
                    }
                }

                if (isPointInsidePath(clickX, clickY, pathHumidity, pathHumidityBoundingBox)) {
                    if(self.userOption){                  
                        const readHumidity= calculateHumidity(clickY, pathHumidityBoundingBox);
                        self.renderHumidity(readHumidity);
                        JSHal.dht11.update_humidity(self.pins.DATA, JSHal.gpioMap.GND, Math.round(readHumidity * 100)); 
                    }
                }

                if (isPointInsideTrash(svgTrash, clickX, clickY)) {
                    window.removeComponent(this);
                    try {
                        while ( self.element.firstChild) {
                            self.element.removeChild(self.element.firstChild);
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

            function isPointInsideCircle(x, y, circleBoundingBox) {
                const circleCenterX = circleBoundingBox.left + circleBoundingBox.width / 2;
                const circleCenterY = circleBoundingBox.top + circleBoundingBox.height / 2;
                const distance = Math.sqrt((x - circleCenterX) ** 2 + (y - circleCenterY) ** 2);
                return distance <= circleBoundingBox.width / 2;
            }

            function isPointInsidePath(x, y, path, boundingBox) {
                    const svgObject = divElement.querySelector('#dht11-svg');
                    this.svgDoc = svgObject.contentDocument;
                    if (
                        x >= boundingBox.left &&
                        x <= boundingBox.right &&
                        y >= boundingBox.top &&
                        y <= boundingBox.bottom
                    ) {
                        const svgPoint = this.svgDoc.documentElement.createSVGPoint();
                        svgPoint.x = x;
                        svgPoint.y = y;

                        const inverseTransform = path.getScreenCTM().inverse();
                        const transformedPoint = svgPoint.matrixTransform(inverseTransform);

                        return path.isPointInFill(transformedPoint);
                    } else {
                        return false;
                    }
              }

              function calculateTemperature(y, boundingBox) {
                    const termometroAltura = boundingBox.bottom - boundingBox.top;
                    const porcentajeAltura = 1 - (y - boundingBox.top) / termometroAltura;
                    let lectura = porcentajeAltura * 52;

                    const mathlectura = Math.floor(lectura);
                    if (mathlectura >= 50) {
                        lectura = 50;
                    }
                    const lecturaConDosDecimales = parseFloat(lectura.toFixed(2));
                    return lecturaConDosDecimales;
              }

              function calculateHumidity(y, boundingBox) {
                const humidityAltura = boundingBox.bottom - boundingBox.top;
                const porcentajeAltura = 1 - (y - boundingBox.top) / humidityAltura;
                let lectura = porcentajeAltura * 102;

                const mathlectura = Math.floor(lectura);
                if (mathlectura >= 100) {
                    lectura = 100;
                }
                const lecturaConDosDecimales = lectura.toFixed(2);
                return parseFloat(lecturaConDosDecimales);
              }

              function handleClick () {
                var destroy = document.getElementById("DELETE_ID");
                while (destroy.classList.length > 0) {
                    destroy.classList.remove(destroy.classList.item(0));
                }
                destroy.classList.add('destroy');
                destroy.classList.add('enabled');

                /*var rectElement = self.svgDoc.getElementById("rectElement");
                rectElement.setAttribute('class', 'fil1Select');
                var polygonElement = self.svgDoc.getElementById("rectPolygonElement");
                var currentClass = polygonElement.getAttribute('class');
                if (!currentClass.includes('str0Select')) {
                  var updatedClass = currentClass.replace('str0', 'str0Select');
                  polygonElement.setAttribute('class', updatedClass);
                }*/

                destroy.addEventListener('click', function(param) {
                    window.removeComponent(this);
                    try {
                        while ( self.element.firstChild) {
                            self.element.removeChild(self.element.firstChild);
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
        this.components.appendChild(divElement);
    };

    Dht11.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('destroy');
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };

    Dht11.prototype.createHTML = function(divElement){
        divElement.id = 'Dht11';
        divElement.classList.add('component');
       
        var wrapper = document.createElement('div');
        wrapper.classList.add('dht11');
        wrapper.innerHTML =
           '<object id="dht11-svg" data="/img/'+this.img+'"' + 'type="image/svg+xml"></object>';
        divElement.appendChild(wrapper);
    }

    Dht11.prototype.destroy = function(param) {
        window.removeComponent(this);
        param.element.remove();
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('destroy');
        destroy.classList.add('disabled');
    };

    Dht11.prototype.renderTemperature = function(temp) {
        var polygonTemp = this.svgDoc.querySelector('#thermometer_dht11-after');
        var pointsTemp = polygonTemp.getAttribute("points").split(" ");

        var roundTemp = Math.round(temp);
        var topTemp = Math.min(50, Math.max(0, roundTemp));
        var normalizedTemp = (topTemp / 50) * 2000;
        var yT2 = 3200 - normalizedTemp;
        //update points
        pointsTemp[2] =  "1079.87," + yT2 + ".02"; 
        pointsTemp[3] =  "889.65," + yT2 + ".02"; 

        polygonTemp.setAttribute("points", pointsTemp.join(" "));

        var Temp_C = parseFloat(temp).toFixed(2);
        var Temp_K = parseFloat((parseFloat(Temp_C) + 273.15).toFixed(2));

        var txtTempC = this.svgDoc.querySelector('#txtTempC');
        txtTempC.textContent = "T: "+Temp_C+ '°C';
        var txtTempK = this.svgDoc.querySelector('#txtTempK');
        txtTempK.textContent = Temp_K + "K";
        JSHal.dht11.update_temperature(this.pins.DATA, JSHal.gpioMap.GND, temp * 100);
    };

    Dht11.prototype.renderHumidity = function(humidity) {
        var polygonHum = this.svgDoc.querySelector('#humidity_dht11-after');
        var pointsHum = polygonHum.getAttribute("points").split(" ");

        var roundHum = Math.round(humidity);
        var topHum = Math.min(100, Math.max(0, roundHum));
        var normalizedHum = (topHum / 100) * 2000;
        var yH2 = 3200 - normalizedHum;
 
        pointsHum[2] = "4804.3," + yH2 + ".02"; 
        pointsHum[3] = "4614.08," + yH2 + ".02"; 
        polygonHum.setAttribute("points", pointsHum.join(" "));

        var Hum = parseFloat(humidity).toFixed(2);

        var txtHum = this.svgDoc.querySelector('#txtHum');
        txtHum.textContent = "H:"+ Hum + '%';
    };
    exports.Dht11 = Dht11.bind(Dht11, 'dht11.svg');
    exports.Dht11Module = Dht11.bind(Dht11, 'dht11_module.svg');
})(window.JSUI);