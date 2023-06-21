#ifndef _RTC_API_MOCK_H
#define _RTC_API_MOCK_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdbool.h>


#include <stdint.h>
#include <string.h> 
#include <time.h>

#include "sapi_peripheral_map.h"

#ifdef __cplusplus
extern "C" {
#endif

void tick_enable(uint32_t tickRateMSvalue);

#ifdef __cplusplus
}
#endif

#endif 
