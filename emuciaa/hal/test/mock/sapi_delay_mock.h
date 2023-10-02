#ifndef SAPI_DELAY_MOCK_H
#define SAPI_DELAY_MOCK_H

#include <stdint.h>
#include <string.h>  
#include <stdbool.h>
#include "sapi_peripheral_map.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ---- Inaccurate Delay ---- */
void delayInaccurateMs( tick_t delay_ms );
void delayInaccurateUs( tick_t delay_us );
void delayInaccurateNs( tick_t delay_ns ); // Resolution ~5 ns

/* ---- Blocking Delay ---- */
void delay( tick_t duration_ms );

/* ---- Non Blocking Delay ---- */
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );

#ifdef __cplusplus
}
#endif

#endif

