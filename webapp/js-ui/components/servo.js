(function(exports) {

    function Servo(pins) {

   
    }

    Servo.prototype = Object.create(exports.BaseComponent.prototype);

    Servo.prototype.init = function() {
        var el = this._el = document.createElement('div');
        el.classList.add('component');
        var p = document.createElement('p');
        p.classList.add('description');

        p.textContent = 'ServoMotor';
        el.appendChild(p);

        var img = document.createElement('img');
        img.src = "/img/motorServo.png";

        el.appendChild(img);
        el.addEventListener('click', this.handleClick.bind(this));

        this.componentsEl.appendChild(el);


    };

    Servo.prototype.handleClick = function(event) {

      };

    Servo.prototype.destroy = function() {

    };

  
    exports.Servo = Servo;

})(window.JSUI);
