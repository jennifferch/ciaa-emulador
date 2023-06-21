#ifndef _DELAY_API_MOCK_H
#define _DELAY_API_MOCK_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdbool.h>

#include "sapi_peripheral_map.h"

#ifdef __cplusplus
extern "C" {
#endif

void wait(float s);
void retard_ms(int ms);
void duration_us(int us);
void duration_ns(int ns);

#ifdef __cplusplus
}
#endif
#endif 
