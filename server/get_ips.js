'use strict';

var os = require('os');

module.exports = function () {
    var ifaces = os.networkInterfaces();
    var ret = [];

    Object.keys(ifaces).forEach(function (ifname) {
        var alias = 0;

        ifaces[ifname].forEach(function (iface) {
            if ('IPv4' !== iface.family || iface.internal !== false) {
                return;
            }

            if (alias >= 1) {
                ret.push({ name: ifname + ':' + alias, iface: iface });
            } else {
                ret.push({ name: ifname, iface: iface });
            }
            ++alias;
        });
    });

    return ret;
};