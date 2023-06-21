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