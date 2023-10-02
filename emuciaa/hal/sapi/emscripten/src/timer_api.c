#include "timer_api.h"
#include "emscripten.h"

static sapi_timer_handler timer_handler;

EMSCRIPTEN_KEEPALIVE
void handle_timer() {
    EM_ASM_({
        console.log('::::::::::: handle_timer');
    });
    timer_handler();
}

int timer_setup(sapi_timer_handler handler, int id, int ms) {
    timer_handler = handler;
    EM_ASM_({
         console.log('::::::::::: timer_setup');
         JSHal.timers.tick_setup($0, $1);
    }, id, ms/1000);
    
    return 0;
}

int timer_detach(uint32_t id) {
    EM_ASM_({
         console.log('::::::::::: timer_setup');
         JSHal.timers.timer_detach($0);
    }, id);

    return 0;
}
