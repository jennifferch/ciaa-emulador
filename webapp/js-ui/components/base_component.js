(function(exports) {

    function BaseComponent() {
    }

    BaseComponent.prototype.createDestroyEl = function() {
        var destroy = document.createElement('span');
        destroy.classList.add('destroyX');
        destroy.textContent = 'X';
        destroy.onclick = function() {
            if (confirm('Deseas eliminar este componente?')) {
                this.destroy();
            }
        }.bind(this);

        return destroy;
    };

    BaseComponent.prototype.pinNameForPin = function(pin) {
        return Object.keys(JSHal.gpioMap).find(function(p) {
            return JSHal.gpioMap[p] === pin;
        }.bind(this));
    };

    exports.BaseComponent = BaseComponent;

})(window.JSUI);
