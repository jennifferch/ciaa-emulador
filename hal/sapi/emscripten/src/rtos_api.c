/* mbed Microcontroller Library
 * Copyright (c) 2017 ARM Limited
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



#include <limits.h>
#include <stdio.h>
#include "rtos_api.h"

us_timestamp_t uptime(void)
{
    return EM_ASM_INT({ return window.JSHal.sleep.uptime() });
}

 static uint64_t get_date(void) 
{
    return EM_ASM_INT({
                return Date.now();
    });
}