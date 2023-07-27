#include "rtc_api_mock.h"
#include <stdio.h>

void rtc_init(void){
    printf("Mock: rtc_init invocado\n");
}

struct tm rtc_read(void){
    time_t now = time(NULL);
    return *localtime(&now);
}

void rtc_write(struct tm* t){
    printf("Mock: rtc_write invocado\n");
}

/*==================[c++]====================================================*/

