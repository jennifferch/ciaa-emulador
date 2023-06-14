(function(exports) {

    function BaseComponent() {
    }

    BaseComponent.prototype.createDestroyEl = function() {
      var destroy = document.getElementById("DELETE_ID");

        destroy.onclick = function() {
         
               this.destroy();

            
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
