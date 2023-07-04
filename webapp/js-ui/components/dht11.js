(function(exports) {

    function Dht11(pins) {
        const request = new XMLHttpRequest();
        request.open('GET', 'https://api.openweathermap.org/data/2.5/weather?q=Lima&appid=16df248820826ba8bd599c2ce8648dd2&units=metric', true);
                      
        request.onload = function () {
                const data = JSON.parse(this.response);
                console.log( "data Temperatura" + data.main.temp);
                console.log( "data Humedad" + data.main.humidity);
                this.temp = data.main.temp *100;
                this.humidity = data.main.humidity + "00" ;
                this.pins = pins;
            JSHal.dht11.update_temperature('10', '11', this.temp);
            JSHal.dht11.update_humidity('10', '11', this.humidity);         
                
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

        var img = document.createElement('img');
        img.src = "/img/Dht11.png";

        divElement.appendChild(img);
        divElement.addEventListener('click', this.handleClick.bind(this));
        
        this.components.appendChild(divElement);
    };

    Dht11.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };

    Dht11.prototype.destroy = function(param) {
        window.removeComponent(this);
        param.element.remove();
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('disabled');
    };
  
    exports.Dht11 = Dht11;

})(window.JSUI);
