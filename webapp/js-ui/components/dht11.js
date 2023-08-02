(function(exports) {

    function Dht11(pins) {

        this.pins = pins;
        this.temp = 2050;
        this.humidity = 3000;

        const request = new XMLHttpRequest();
      /*  if (navigator.geolocation) {
            navigator.geolocation.getCurrentPosition(function(position) {
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
                                this.temp = data.main.temp *100;
                                this.humidity = data.main.humidity + "00" ;
                                this.pins = pins;
                                JSHal.dht11.update_temperature('10', '11', this.temp);
                                JSHal.dht11.update_humidity('10', '11', this.humidity);         
                            }
                        }  
                    }   
                    request.open('GET', apiUrl, true);
                    request.send(); 
            });
        } else {*/
            console.log("La geolocalización no es soportada por este navegador.");
            request.open('GET', 'https://api.openweathermap.org/data/2.5/weather?q=Buenos%20Aires&appid=16df248820826ba8bd599c2ce8648dd2&units=metric', true);                   
            request.onload = function () {
                    const data = JSON.parse(this.response);
                    console.log( "data Temperatura" + data.main.temp);
                    console.log( "data Humedad" + data.main.humidity);
                    this.temp = data.main.temp *100;
                    this.humidity = data.main.humidity + "00" ;
                    this.pins = pins;
                JSHal.dht11.update_temperature('10', '11', this.temp);
                JSHal.dht11.update_humidity('10', '11', this.humidity);                  
       //     }
            }
        request.send();
        exports.BaseComponent.call(this);
        this.components = document.querySelector('#components');   
    }

    Dht11.prototype = Object.create(exports.BaseComponent.prototype);

    Dht11.prototype.init = function() {
        var divElement = this.element = document.createElement('div');
        divElement.id = 'Dht11';
        divElement.classList.add('component');
        var p = document.createElement('p');
        p.classList.add('description');

        p.textContent = 'DHT11';
        divElement.appendChild(p);

      //  var img = document.createElement('img');
     //   img.src = "/img/Dht11.png";

    //    divElement.appendChild(img);
    //    divElement.addEventListener('click', this.handleClick.bind(this));


        var wrapper = document.createElement('div');
        wrapper.classList.add('sht31');
        wrapper.innerHTML =
            '<div class="dht11-img"><img src="/img/Dht11.png" alt="Descripción de la imagen"></div>' +
            '<div class="thermometer sht31-comp"><div class="sht31-before"></div><span class="sht31-content">20&deg;C</span><div class="sht31-after"></div></div>' +
            '<div class="humidity sht31-comp"><div class="sht31-before"></div><span class="sht31-content">31%</span><div class="sht31-after"></div></div>';

        divElement.appendChild(wrapper);

        var divServidor = document.createElement('div');
        divServidor.classList.add('contenedorLabel');

        var divManual = document.createElement('div');
        divManual.classList.add('contenedorLabel');

        var labelServidor = document.createElement('label');
        labelServidor.textContent = "Obtener temperatura local de servidor climático";
        labelServidor.classList.add('labelDht11');

        var labelManual = document.createElement('label');
        labelManual.textContent = "Establecer temperatura y humedad manualmente";
        labelManual.classList.add('labelDht11');

        var inputServidor = document.createElement('input');
        inputServidor.type = "radio";
        inputServidor.classList.add('inputDht11');

        inputServidor.setAttribute('placeholder', 'Input seleccionado');
        inputServidor.focus();

        var inputManual = document.createElement('input');
        inputManual.type = "radio";
        inputManual.classList.add('inputDht11');

        divServidor.appendChild(inputServidor);
        divServidor.appendChild(labelServidor);

        var labelOpcionManual = document.createElement('label');
        labelOpcionManual.classList.add('labelOpcion');
        labelOpcionManual.textContent = "(haga click sobre los indicadores)";

        var saltoDeLinea = document.createElement("br");
        
        divManual.appendChild(inputManual);
        divManual.appendChild(labelManual);
        divManual.appendChild(saltoDeLinea);
        divManual.appendChild(labelOpcionManual);
        

        divElement.appendChild(divServidor);
        divElement.appendChild(divManual);
    //    divElement.appendChild(labelOpcionManual);
       

        this.tempEl = divElement.querySelector('.thermometer');
        this.humiEl = divElement.querySelector('.humidity');

        this.renderTemperature();
        this.renderHumidity();

        [].forEach.call(divElement.querySelectorAll('.sht31-comp'), function(c) {
            c.onclick = this.change.bind(this);
        }.bind(this));
        
        this.components.appendChild(divElement);
    };

 /*   Dht11.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };*/

    Dht11.prototype.destroy = function(param) {
        window.removeComponent(this);
        param.element.remove();
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('disabled');
    };

    Dht11.prototype.renderTemperature = function() {
        // 0..146, max temp is 50 degrees
        var height = (this.temp / 100) / (50 / 146);
        var top = 146 - height;

        var after = this.tempEl.querySelector('.sht31-after');
        after.style.top = top + 6 + 'px';
        after.style.height = height + 'px';

        this.tempEl.querySelector('.sht31-content').textContent = (this.temp / 100).toFixed(2) + '°C';

       // MbedJSHal.sht31.update_temperature(this.pins.SDA, this.pins.SCL, this.temp);

        JSHal.dht11.update_temperature('10', '11', this.temp);
    };

    Dht11.prototype.renderHumidity = function() {
        // 0..146, max is 100%
        var height = (this.humidity / 100) / (100 / 146);
        var top = 146 - height;

        var after = this.humiEl.querySelector('.sht31-after');
        after.style.top = top + 6 + 'px';
        after.style.height = height + 'px';

        this.humiEl.querySelector('.sht31-content').textContent = (this.humidity / 100).toFixed(2) + '%';

       // MbedJSHal.sht31.update_humidity(this.pins.SDA, this.pins.SCL, this.humidity);
        JSHal.dht11.update_humidity('10', '11', this.humidity); 
    };

    Dht11.prototype.change = function(ev) {
        // this reflows... but I don't feel like fixing it
        var y = ev.pageY - ev.currentTarget.offsetTop;
        if (y < 10) y = 10;
        y -= 10;
        if (ev.currentTarget === this.tempEl) {
            this.temp = (1 - (y / 155)) * 5000 | 0;
            if (this.temp < 0) this.temp = 0;
            this.renderTemperature();
        }
        else if (ev.currentTarget === this.humiEl) {
            this.humidity = (1 - (y / 155)) * 10000 | 0;
            if (this.humidity < 0) this.humidity = 0;
            this.renderHumidity();
        }
    };

    Dht11.prototype.on_update_display = function(mosi, miso, sck, buffer) {
      //  if (this.pins.MOSI !== mosi || this.pins.MISO !== miso || this.pins.SCK !== sck) return;

        // so... we're getting 4096 bytes...
        var x = 0;
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

        }
    };
  
    exports.Dht11 = Dht11;

})(window.JSUI);
