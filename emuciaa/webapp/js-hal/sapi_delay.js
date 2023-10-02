window.JSHal.delay = (function() {

    var obj = {};
    var wait = {};

    obj.timeout_setup = function (duration) {
        setTimeout(() => {
            console.log("Delayed.");
          }, duration);
    }

    obj.delay_setup = function (id, interval) {
        wait[id] = setInterval(() => {
            ccall('handle_delay', null, [], [], { async: false });
        }, interval);
    }

    obj.delay_detach = function (id) {
            clearInterval(wait[id]);
    }

    return obj;

})();