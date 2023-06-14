/* Copyright 2015-2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/* Date: 2015-09-23 */

/*==================[inclusions]=============================================*/
#include "gpio_api.h"
#include "emscripten.h"

uint32_t gpio_set(gpioMap_t pin) {
    return pin;
}

void gpio_init(gpio_t *obj, gpioMap_t pin) {
    obj->pin = pin;
    if (pin == (gpioMap_t)NC)
        return;

    obj->mask = gpio_set(pin);

    EM_ASM_({
        JSHal.gpio.init($0, $1);
    }, obj, obj->pin);
}

void gpio_mode(gpio_t *obj, PinMode mode) {
    EM_ASM_({
        JSHal.gpio.mode($0, $1);
    }, obj->pin, mode);
}

void gpio_dir(gpio_t *obj, PinDirection direction) {
    EM_ASM_({
        JSHal.gpio.dir($0, $1);
    }, obj->pin, direction);
}

void gpio_init_in(gpio_t* gpio, gpioMap_t pin) {
    gpio->pin = pin;
    if (pin == (gpioMap_t)NC)
        return;

    gpio->mask = gpio_set(pin);

    EM_ASM_({
        JSHal.gpio.init_in($0, $1, 3);
    }, gpio, gpio->pin);
}

void gpio_init_in_ex(gpio_t* gpio, gpioMap_t pin, PinMode mode) {
    gpio->pin = pin;
    if (pin == (gpioMap_t)NC)
        return;

    gpio->mask = gpio_set(pin);

    EM_ASM_({
        JSHal.gpio.init_in($0, $1, $2);
    }, gpio, gpio->pin, mode);
}

void gpio_init_out(gpio_t* gpio, gpioMap_t pin) {
    gpio->pin = pin;
    if (pin == (gpioMap_t)NC)
        return;

    gpio->mask = gpio_set(pin);

    EM_ASM_({
        JSHal.gpio.init_out($0, $1, 0);
    }, gpio, gpio->pin);
}

void gpio_init_out_ex(gpio_t* gpio, gpioMap_t pin, int value) {
    gpio->pin = pin;
    if (pin == (gpioMap_t)NC)
        return;

    gpio->mask = gpio_set(pin);

    EM_ASM_({
        JSHal.gpio.init_out($0, $1, $2);
    }, gpio, gpio->pin, value);
}

void gpio_init_inout(gpio_t* gpio, gpioMap_t pin, PinDirection direction, PinMode mode, int value) {
    gpio->pin = pin;
    if (pin == (gpioMap_t)NC)
        return;

    gpio->mask = gpio_set(pin);

    EM_ASM_({
        JSHal.gpio.init_inout($0, $1, $2, $3, $4);
    }, gpio, gpio->pin, direction, mode, value);
}

void gpio_write(gpio_t *obj, int value) {
    EM_ASM_({
        JSHal.gpio.write($0, $1);
    }, obj->pin, value);
}

int gpio_read(gpio_t *obj) {
    return EM_ASM_INT({
        return JSHal.gpio.read($0);
    }, obj->pin);
}

int gpio_is_connected(const gpio_t *obj) {
    return 1;
}