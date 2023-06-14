const launchServer = require('./server/launch-server');
const Path = require('path');

launchServer(Path.join(__dirname, 'outUser'), process.env.PORT || 7829, 3600000, true, function(err) {
    if (err) return console.error(err);

});
