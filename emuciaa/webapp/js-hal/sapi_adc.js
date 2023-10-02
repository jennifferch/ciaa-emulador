window.JSHal.adc = (function() {

    var obj = {};

    obj.update_adc= function( pin) {
        console.log( "update_adc " + pin);
        window.JSHal.gpio.init_analogin(0, pin);
    };

    return obj;
})();
