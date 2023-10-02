#include "sapi_uart_mock.h"
#include <stdio.h>

static bool_t uartRxReady_result;
static bool_t uartTxReady_result;
static bool_t uartReadByte_result;

void uartRxReady_mock_init(void) {
    // Inicializar el estado del mock
    uartRxReady_result = false;
}

void uartRxReady_mock_destroy(void) {
    // Limpiar el estado del mock
    uartRxReady_result = false;
}

void uartRxReady_set_result(bool result) {
    // Establecer el resultado del mock
    uartRxReady_result = result;
}

void uartTxReady_mock_init(void) {
    // Inicializar el estado del mock
    uartTxReady_result = false;
}

void uartTxReady_mock_destroy(void) {
    // Limpiar el estado del mock
    uartTxReady_result = false;
}

void uartTxReady_set_result(bool result) {
    // Establecer el resultado del mock
    uartTxReady_result = result;
}

void uartReadByte_mock_init(void) {
    // Inicializar el estado del mock
    uartReadByte_result = false;
}

void uartReadByte_mock_destroy(void) {
    // Limpiar el estado del mock
    uartReadByte_result = false;
}

void uartReadByte_set_result(bool result) {
    // Establecer el resultado del mock
    uartReadByte_result = result;
}

bool_t uartRxReady( uartMap_t uart ){
    printf("Mock: uartRxReady invocado con uartMap_t = %d\n", uart);                    
    return uartRxReady_result;
}

bool_t uartTxReady( uartMap_t uart ){
    printf("Mock: uartTxReady invocado con uartMap_t = %d\n", uart);                    
    return uartTxReady_result;
}

uint8_t uartRxRead( uartMap_t uart ){
    printf("Mock: uartRxRead invocado con uartMap_t = %d\n", uart);                    
}

void uartTxWrite( uartMap_t uart, uint8_t value ){
    printf("Mock: uartTxWrite invocado con uartMap_t = %d\n", uart);                
}

void uartInit( uartMap_t uart, uint32_t baudRate ){
    printf("Mock: uartInit invocado con uartMap_t = %d\n", uart);            
}

void uartInit2( uartMap_t uart, uint32_t baudRate, 
                uint8_t dataBits, uint8_t parity, uint8_t stopBits ){
    printf("Mock: uartInit2 invocado con uartMap_t = %d\n", uart);        
}

bool_t uartReadByte( uartMap_t uart, uint8_t* receivedByte ){
    printf("Mock: uartReadByte invocado con uartMap_t = %d\n", uart);
    return uartReadByte_result;        
}

void uartWriteByte( uartMap_t uart, const uint8_t value ){
    printf("Mock: uartWriteByte invocado con uartMap_t = %d\n", uart);    
}

void uartWriteString( uartMap_t uart, const char* str ){
    printf("Mock: uartWriteString invocado con uartMap_t = %d\n", uart);
}

void uartWriteByteArray( uartMap_t uart, const uint8_t* byteArray, uint32_t byteArrayLen ){
    printf("Mock: uartWriteByteArray invocado con uartMap_t = %d\n", uart);
}

void uartInterrupt( uartMap_t uart, bool_t enable ){
    printf("Mock: uartInterrupt invocado con uartMap_t = %d\n", uart);
}

void uartSetPendingInterrupt(uartMap_t uart){
    printf("Mock: uartSetPendingInterrupt invocado con uartMap_t = %d\n", uart);
}

void uartClearPendingInterrupt(uartMap_t uart){
    printf("Mock: uartClearPendingInterrupt invocado con uartMap_t = %d\n", uart);
}

void UART0_IRQHandler(void){
    printf("Mock: UART0_IRQHandler invocado\n");
}

void UART2_IRQHandler(void){
    printf("Mock: UART2_IRQHandler invocado\n");
}

void UART3_IRQHandler(void){
    printf("Mock: UART3_IRQHandler invocado\n");
}

