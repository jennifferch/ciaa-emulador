(function(exports) {

    function Termistor(pins) {

       this.components = document.querySelector('#components');
    }

    Termistor.prototype = Object.create(exports.BaseComponent.prototype);

    Termistor.prototype.init = function() {
        var divElement = this.element = document.createElement('div');
        divElement.classList.add('component');
        var p = document.createElement('p');
        p.classList.add('description');

        p.textContent = 'Termistor';
        divElement.appendChild(p);

        var img = document.createElement('img');
        img.src = "/img/termistor.png";

        divElement.appendChild(img);
        divElement.addEventListener('click', this.handleClick.bind(this));

        this.components.appendChild(divElement);

    };

    Termistor.prototype.handleClick = function(event) {
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
          destroy.classList.remove(destroy.classList.item(0));
        }
        destroy.classList.add('enabled');
        destroy.addEventListener('click', () => this.destroy(this));
    };

    Termistor.prototype.destroy = function(param) {
        window.removeComponent(this);
        param.element.remove();
        var destroy = document.getElementById("DELETE_ID");
        while (destroy.classList.length > 0) {
            destroy.classList.remove(destroy.classList.item(0));
          }
        destroy.classList.add('disabled');
    };

  
    exports.Termistor = Termistor;

})(window.JSUI);
