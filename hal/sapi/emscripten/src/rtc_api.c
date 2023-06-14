#include "rtc_api.h"
#include "emscripten.h"

//#if DEVICE_RTC

static int64_t rtc_correction = 0;

struct tm time_init = {0};

void rtc_init(void) {

}

void rtc_free(void) {

}

int rtc_isenabled(void) {
    return 1;
}

struct tm rtc_read(void) {
    struct tm t;
    // time_t curr = EM_ASM_INT({ return Date.now() / 1000 | 0; });
    EM_ASM_({
        JSHal.rtc.update();
    });
    t.tm_hour =  EM_ASM_INT({ return window.JSHal.rtc.read_hours() });
    t.tm_min = EM_ASM_INT({ return window.JSHal.rtc.read_minutes() });
    t.tm_sec = EM_ASM_INT({ return window.JSHal.rtc.read_seconds() });
    t.tm_year = EM_ASM_INT({ return window.JSHal.rtc.read_year() });
    t.tm_mon = EM_ASM_INT({ return window.JSHal.rtc.read_month() });
    t.tm_mday = EM_ASM_INT({ return window.JSHal.rtc.read_day() });
    // return curr + rtc_correction;
    return t;
}

void rtc_write(struct tm* t) {
    EM_ASM_({
        JSHal.rtc.write($0, $1, $2, $3, $4, $5);
    }, t->tm_hour, t->tm_min, t->tm_sec, 
       t->tm_year, t->tm_mon, t->tm_mday);
}

//#endif // RTC_TIME
