#include "tick_api.h"
#include "emscripten.h"

static sapi_tick_handler tick_handler;

EMSCRIPTEN_KEEPALIVE
void handle_ticker() {
    EM_ASM_({
        console.log('::::::::::: handle_tick');
    });
    tick_handler();
}

void tick_enable(uint32_t tickRateMSvalue) {
    EM_ASM_({
        console.log('::::::::::: tick_enable');
        window.JSHal.tick.config($0);
    }, tickRateMSvalue);
}

void tick_callback_set() {
    EM_ASM_({
        console.log('::::::::::: tick_callback_set');
        window.JSHal.tick.systick();;
    });
}

int tick_init(sapi_tick_handler handler, int id, int ms) {
    tick_handler = handler;
     EM_ASM_({
         console.log('::::::::::: tick_init');
         JSHal.tick.tick_setup($0, $1);
    }, id, ms);
    
    return 0;
}

int tick_detach(int id) {
    EM_ASM_({
         console.log('::::::::::: tick_detach');
         JSHal.tick.timer_detach($0);
    }, id);

    return 0;
}
