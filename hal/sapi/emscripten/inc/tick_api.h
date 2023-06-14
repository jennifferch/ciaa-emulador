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

/** \addtogroup hal */
/** @{*/

#ifndef TICK_API_H
#define TICK_API_H

#include "sapi_datatypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[external functions definition]==========================*/

typedef void (*sapi_tick_handler)(void);

void tick_enable(uint32_t tickRateMSvalue);

int tick_init(sapi_tick_handler handler);

/*==================[ISR external functions declaration]======================*/

#ifdef __cplusplus
}
#endif

#endif

/** @}*/
