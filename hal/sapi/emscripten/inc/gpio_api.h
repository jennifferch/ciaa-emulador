/* Copyright 2015, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
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
 */

/* Date: 2015-09-23 */

#ifndef _SAPI_GPIO_API_H
#define _SAPI_GPIO_API_H

#include "sapi_peripheral_map.h"

/*==================[c]====================================================*/
#ifdef __cplusplus
extern "C" {
#endif

uint32_t gpio_set(gpioMap_t pin);
void gpio_init(gpio_t *obj, gpioMap_t pin);
void gpio_mode(gpio_t *obj, PinMode mode);
void gpio_dir(gpio_t *obj, PinDirection direction);
void gpio_init_in(gpio_t* gpio, gpioMap_t pin);
void gpio_init_in_ex(gpio_t* gpio, gpioMap_t pin, PinMode mode);
void gpio_init_out(gpio_t* gpio, gpioMap_t pin);
void gpio_init_out_ex(gpio_t* gpio, gpioMap_t pin, int value);
void gpio_init_inout(gpio_t* gpio, gpioMap_t pin, PinDirection direction, PinMode mode, int value);

void gpio_write(gpio_t *obj, int value);
int gpio_read(gpio_t *obj);
int gpio_is_connected(const gpio_t *obj);

/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _SAPI_GPIO_API_H_ */
