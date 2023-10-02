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

/* Mock de la función rtc_init */
void rtc_init(void);

/* Mock de la función rtc_read */
struct tm rtc_read(void);

/* Mock de la función rtc_write */
void rtc_write(struct tm* t);

#ifdef __cplusplus
}
#endif

#endif 
