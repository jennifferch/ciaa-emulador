/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "tick_api.h"
#include "emscripten.h"

static sapi_tick_handler tick_handler;

EMSCRIPTEN_KEEPALIVE
void handle_tick_in() {
    EM_ASM_({
        console.log('::::::::::: llego handle_tick ');
    });
    tick_handler();
}

void tick_enable(uint32_t tickRateMSvalue) {
    EM_ASM_({
        console.log('::::::::::: tick_enable tick from board');
        window.JSHal.tick.config($0);
    }, tickRateMSvalue);
}

int tick_init(sapi_tick_handler handler) {
    tick_handler = handler;
    EM_ASM_({
         console.log('::::::::::: tick_init event ');
         window.JSHal.tick.systick();
    });

    return 0;
}
