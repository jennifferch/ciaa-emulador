#include "gpio_api_mock.h"
#include <stdio.h>

static int gpio_read_result;
static uint32_t gpio_result;

void gpio_api_mock_init(void) {
    // Inicializar el estado del mock
    gpio_read_result = 0;
    gpio_result = 0;
}

void gpio_api_mock_destroy(void) {
    // Limpiar el estado del mock
    gpio_read_result = 0;
    gpio_result = 0;
}

void gpio_read_set_result(int result) {
    // Establecer el resultado del mock
    gpio_read_result = result;
}

void gpio_set_result(uint32_t result) {
    // Establecer el resultado del mock
    gpio_result = result;
}

uint32_t gpio_set(gpioMap_t pin){
    return gpio_result;
}
void gpio_init(gpio_t *obj, gpioMap_t pin){
    printf("Mock: gpio_init invocado con gpioMap_t = %d\n", pin);
}
void gpio_mode(gpio_t *obj, PinMode mode){
    printf("Mock: gpio_mode invocado con pinMode = %d\n", mode);
}
void gpio_dir(gpio_t *obj, PinDirection direction){
    printf("Mock: gpio_dir invocado con pinDirection = %d\n", direction);
}
void gpio_init_in(gpio_t* gpio, gpioMap_t pin){
    printf("Mock: gpio_init_in invocado con gpioMap_t = %d\n", pin);
}
void gpio_init_in_ex(gpio_t* gpio, gpioMap_t pin, PinMode mode){
    printf("Mock: gpio_init_in_ex invocado con gpioMap_t = %d\n", pin);
}
void gpio_init_out(gpio_t* gpio, gpioMap_t pin){
    printf("Mock: gpio_init_in invocado con gpioMap_t = %d\n", pin);
}
void gpio_init_out_ex(gpio_t* gpio, gpioMap_t pin, int value){
    printf("Mock: gpio_init_out invocado con gpioMap_t = %d\n", pin);
}
void gpio_init_inout(gpio_t* gpio, gpioMap_t pin, PinDirection direction, PinMode mode, int value){
    printf("Mock: gpio_init_inout invocado con gpioMap_t = %d\n", pin);
}

void gpio_write(gpio_t *obj, int value){
    printf("Mock: gpio_write invocado con value = %d\n", value);
}
int gpio_read(gpio_t *obj){
    return gpio_read_result;
}
int gpio_is_connected(const gpio_t *obj){
    return gpio_read_result;
}

