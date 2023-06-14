window.JSHal.tick = (function() {

    var obj = {};
    var count = 0;
    var init = false;
    var ticks = 0;

    obj.setTickInit = function (enable){
        init = enable;  
    }

    obj.config = function (ticks_param){

        console.log("inicio de la configuracion");
        this.setTickInit(true);  
        ticks = ticks_param;
    }

    obj.systick = function (){

       for(;true;) { 
           console.log(" systick inicio ");
           ccall('handle_tick_in');
           console.log(" systick fin ");
        }
    }

    obj.tickRead = function (){
        return count;
    }

    return obj;

})();