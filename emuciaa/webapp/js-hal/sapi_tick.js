window.JSHal.tick = (function() {

    var obj = {};
    var count = 0;
    var init = false;
    var ticks = 0;
    var ticks = {};

    obj.setTickInit = function (enable){
        init = enable;  
    }

    obj.config = function (ticks_param){
        console.log("inicio de la configuracion");
        this.setTickInit(true);  
        ticks = ticks_param;
    }

    obj.tickRead = function (){
        return count;
    }

    obj.tick_setup = function (id, interval) {
        if (ticks[id]) {
            clearInterval(ticks[id]);
        }

        ticks[id] = setInterval(() => {
            ccall('handle_ticker', null, [], [], { async: true });
        }, interval);
    }

    obj.timer_detach = function (id) {
        if (!(id in ticks)) return;

        clearInterval(ticks[id]);
        delete ticks[id];
    }

    return obj;

})();