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

#include "pwm_api.h"
#include "emscripten.h"
#include "sapi_peripheral_map.h"

void pwm_init(pwm_t* obj, gpioMap_t pin) {
    obj->pin = pin;

    EM_ASM_({
        JSHal.gpio.init_pwmout($0, $1, $2, $3);
    }, obj, obj->pin, 20, 0);
}

void pwm_write(pwm_t* obj, float value) {
    EM_ASM_({
        JSHal.gpio.write($0, $1);
    }, obj->pin, (int)(value * 1024.0f));
}

float pwm_read(pwm_t* obj) {
    int v = EM_ASM_({
        return JSHal.gpio.read($0);
    }, obj->pin);

    return ((float)v) / 1024.0f;
}

void pwm_period(pwm_t* obj, float seconds) {
    EM_ASM_({
        JSHal.gpio.period_ms($0, $1);
    }, obj->pin, (int)(seconds * 1000.0f));
}

void pwm_period_ms(pwm_t* obj, int ms) {
    EM_ASM_({
        JSHal.gpio.period_ms($0, $1);
    }, obj->pin, ms);
}

void pwm_period_us(pwm_t* obj, int us) {
    EM_ASM_({
        JSHal.gpio.period_ms($0, $1);
    }, obj->pin, us / 1000);
}

void pwm_pulsewidth(pwm_t* obj, float seconds) {
    EM_ASM_({
        JSHal.gpio.pulsewidth_ms($0, $1);
    }, obj->pin, (int)(seconds * 1000.0f));
}

void pwm_pulsewidth_ms(pwm_t* obj, int ms) {
    EM_ASM_({
        JSHal.gpio.pulsewidth_ms($0, $1);
    }, obj->pin, ms);
}

void pwm_pulsewidth_us(pwm_t* obj, int us) {
    EM_ASM_({
        JSHal.gpio.pulsewidth_ms($0, $1);
    }, obj->pin, us / 1000);
}
