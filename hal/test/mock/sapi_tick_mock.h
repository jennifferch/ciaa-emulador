#ifndef SAPI_DELAY_MOCK_H
#define SAPI_DELAY_MOCK_H

#include <stdint.h>
#include <string.h>  
#include <stdbool.h>
#include "sapi_peripheral_map.h"

#ifdef __cplusplus
extern "C" {
#endif

void tickInit_mock_init(void);

void tickInit_mock_destroy(void);

void tickInit_set_result(bool result);

void tickCallbackSet_mock_init(void);

void tickCallbackSet_mock_destroy(void);

void tickCallbackSet_set_result(bool result);

void tickRead_mock_init(void);

void tickRead_mock_destroy(void);

void tickRead_set_result(uint64_t result);

bool_t tickInit( tick_t tickRateMSvalue );
// Read Tick Counter
tick_t tickRead( void );
// Write Tick Counter
void tickWrite( tick_t ticks );
// Tick interrupt callback
bool_t tickCallbackSet( callBackFuncPtr_t tickCallback, void* tickCallbackParams );
// Enable or disable the peripheral energy and clock
void tickPowerSet( bool_t power );

/*==================[ISR external functions declaration]======================*/

// SysTick Timer ISR Handler
void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif

