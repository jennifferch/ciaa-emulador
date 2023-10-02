#ifndef SAPI_UART_MOCK_H
#define SAPI_UART_MOCK_H

#include <stdint.h>
#include <string.h>  
#include <stdbool.h>
#include "sapi_peripheral_map.h"

#ifdef __cplusplus
extern "C" {
#endif

void uartRxReady_mock_init(void);

void uartRxReady_mock_destroy(void);

void uartRxReady_set_result(bool result);

void uartTxReady_mock_init(void);

void uartTxReady_mock_destroy(void);

void uartTxReady_set_result(bool result);

void uartReadByte_mock_init(void);

void uartReadByte_mock_destroy(void);

void uartReadByte_set_result(bool result);

bool_t uartRxReady( uartMap_t uart );

bool_t uartTxReady( uartMap_t uart );

uint8_t uartRxRead( uartMap_t uart );

void uartTxWrite( uartMap_t uart, uint8_t value );

void uartInit( uartMap_t uart, uint32_t baudRate );

void uartInit2( uartMap_t uart, uint32_t baudRate, 
                uint8_t dataBits, uint8_t parity, uint8_t stopBits );

bool_t uartReadByte( uartMap_t uart, uint8_t* receivedByte );

void uartWriteByte( uartMap_t uart, const uint8_t value );

void uartWriteString( uartMap_t uart, const char* str );

void uartWriteByteArray( uartMap_t uart, const uint8_t* byteArray, uint32_t byteArrayLen );

void uartInterrupt( uartMap_t uart, bool_t enable );

void uartSetPendingInterrupt(uartMap_t uart);

void uartClearPendingInterrupt(uartMap_t uart);

void UART0_IRQHandler(void);

void UART2_IRQHandler(void);

void UART3_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif

