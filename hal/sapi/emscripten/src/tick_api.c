#include "tick_api.h"
#include "emscripten.h"

static sapi_tick_handler tick_handler;

EMSCRIPTEN_KEEPALIVE
void handle_tick_in() {
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

int tick_init(sapi_tick_handler handler) {
    tick_handler = handler;
    EM_ASM_({
         console.log('::::::::::: tick_init');
         window.JSHal.tick.systick();
    });

    return 0;
}
