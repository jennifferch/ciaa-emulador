window.JSHal.timers = (function() {

    var tickers = {};

    function ticker_setup(id, interval) {
        if (tickers[id]) {
            clearInterval(tickers[id]);
        }

        tickers[id] = setInterval(() => {
            ccall('invoke_ticker', null, [ 'number' ], [ id ], { async: true });
        }, interval);
    }


    function ticker_detach(id) {
        if (!(id in tickers)) return;

        clearInterval(tickers[id]);
        delete tickers[id];
    }


    return {
        ticker_setup: ticker_setup,
        ticker_detach: ticker_detach
    };

})();