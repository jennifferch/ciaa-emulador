(function(exports) {

    function BaseComponent() {
    }

    BaseComponent.prototype.pinNameForPin = function(pin) {
        return Object.keys(JSHal.gpioMap).find(function(p) {
            return JSHal.gpioMap[p] === pin;
        }.bind(this));
    };

    exports.BaseComponent = BaseComponent;

})(window.JSUI);
