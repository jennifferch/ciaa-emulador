window.JSHal.servo = (function() {
    var sensors = {};

    var obj = {};
    var values = {};

    obj.init = function(id, sda, scl) {
        sensors[id] = {
            sda: sda,
            scl: scl
        };
    };

    obj.read_position = function(id) {
        if (!(id in sensors)) return 0;
        var key = sensors[id].sda + '_' + sensors[id].scl;

        console.log( " read_position  key " + key);

        return (values[key]);
    };

    return obj;
})();
