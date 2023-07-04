(function(exports) {

    function Servo(pins) {

       this.components = document.querySelector('#components');
    }

    Servo.prototype = Object.create(exports.BaseComponent.prototype);

    Servo.prototype.init = function() {
        var divElement = this.element = document.createElement('div');
        divElement.classList.add('component');
        var p = document.createElement('p');
        p.classList.add('description');

        p.textContent = 'ServoMotor';
        divElement.appendChild(p);

        var img = document.createElement('img');
        img.src = "/img/motorServo.png";

        divElement.appendChild(img);
        divElement.addEventListener('click', this.handleClick.bind(this));

        this.components.appendChild(divElement);

    };

    Servo.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
          destroy.classList.remove(destroy.classList.item(0));
        }
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };

    Servo.prototype.destroy = function(param) {
        window.removeComponent(this);
        param.element.remove();
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('disabled');
    };

  
    exports.Servo = Servo;

})(window.JSUI);
