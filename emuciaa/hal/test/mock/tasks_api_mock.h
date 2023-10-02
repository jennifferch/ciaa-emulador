#ifndef TASKS_API_MOCK_H
#define TASKS_API_MOCK_H

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

void getTickCount_mock_init(void);

void getTickCount_mock_destroy(void);

void getTickCount_set_result(uint64_t result);

void xStartTickCount();

int getTickCount();
 
void setTaskDelayUntil(int pxPreviousWakeTime, int xTimeIncrement);

#ifdef __cplusplus
}
#endif

#endif 
