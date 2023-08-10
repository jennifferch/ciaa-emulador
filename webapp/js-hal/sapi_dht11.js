window.JSHal.dht11 = (function() {
    var sensors = {};

    var obj = {};
    var values = {};

    obj.init = function(id, gpio, gnd) {
        sensors[id] = {
            gpio: gpio,
            gnd: gnd
        };
    };

    obj.read_temperature = function(id) {
        if (!(id in sensors)) return 0;
        var key = sensors[id].gpio + '_' + sensors[id].gnd;

        console.log( " read_temperature  key " + key);
        console.log( " values[key]  " + values[key] );

        return (values[key] || { temp: 0 }).temp;
    };

    obj.read_humidity = function(id) {
        if (!(id in sensors)) return 0;
        var key = sensors[id].gpio + '_' + sensors[id].gnd;

        return (values[key] || { humidity: 0 }).humidity;
    };

    obj.update_temperature = function(gpio, gnd, temp) {
        console.log( "update_temperature " + temp);
        var key = gpio + '_' + gnd;

        values[key] = values[key] || {
            temp: 0,
            humidity: 0
        };

        values[key].temp = temp;
    };

    obj.update_humidity = function(gpio, gnd, humidity) {
        console.log( "update_humidity " + humidity);
        var key = gpio + '_' + gnd;

        values[key] = values[key] || {
            temp: 0,
            humidity: 0
        };

        values[key].humidity = humidity;
    };

    return obj;
})();
