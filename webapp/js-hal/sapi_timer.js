window.JSHal.timers = (function() {

    var timers = {};

    function timer_setup(id, interval) {
        if (timers[id]) {
            clearInterval(timers[id]);
        }

        timers[id] = setInterval(() => {
            ccall('handle_timer', null, [], [], { async: true });
        }, interval);
    }


    function timer_detach(id) {
        if (!(id in timers)) return;

        clearInterval(timers[id]);
        delete timers[id];
    }

    return {
        timer_setup: timer_setup,
        timer_detach: timer_detach
    };

})();