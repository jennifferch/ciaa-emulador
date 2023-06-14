/* Copyright 2016, Ian Olivieri
 * Copyright 2016, Eric Pernia.
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

/* Date: 2016-02-10 */

#ifndef _SAPI_PWM_H_
#define _SAPI_PWM_H_

/*==================[inclusions]=============================================*/
#include "sapi_datatypes.h"
#include "sapi_peripheral_map.h"

#include "pwm_api.h"
#include <stdbool.h>
/*==================[c++]====================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros and definitions]=================================*/

#define pwmConfig pwmInit
#define PWM_INST_NUM      50

/*==================[typedef]================================================*/
typedef enum{
   PWM_ENABLE, PWM_DISABLE,
   PWM_ENABLE_OUTPUT, PWM_DISABLE_OUTPUT
} pwmInit_t;

typedef struct{
    pwm_t _pwm_instance;
    bool _deep_sleep_locked_instance;
    gpioMap_t pin;
    uint8_t value;
} pwmOutClass;

/*==================[external functions declaration]=========================*/
void pwmInit(gpioMap_t pin, pwmInit_t config);
uint8_t pwmIsAttached( pwmMap_t pwmNumber );
uint8_t pwmRead( gpioMap_t pin);
bool_t pwmWrite( gpioMap_t pin, uint8_t value);

/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _SAPI_PWM_H_ */
