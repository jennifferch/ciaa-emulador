window.JSHal.rtc = (function() {

    var obj = {};  
    var time_t = new Date();

    obj.write = function (hour, min, sec, year, mon, day) {
        time_t.setFullYear(year);
        time_t.setMonth(mon);
        time_t.setDate(day);
        time_t.setHours(hour);
        time_t.setMinutes(min);
        time_t.setSeconds(sec);
    }

    obj.update = function () {
        var second_t = time_t.getSeconds() +1;
        time_t.setSeconds(second_t);
    }

    obj.read_year = function() {
        
        return time_t.getFullYear(); 
    }

    obj.read_month = function() {
 
        return time_t.getMonth();
    }

    obj.read_day = function () {
 
        return time_t.getDate();
    }
 
    obj.read_hours = function () {
   
        return time_t.getHours();
    }

    obj.read_minutes = function () {
    
        return time_t.getMinutes();
    }

    obj.read_seconds = function () {
    
        return time_t.getSeconds();
    }

    return obj;

})();