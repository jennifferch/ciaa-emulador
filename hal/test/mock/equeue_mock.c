#include "equeue_mock.h"
#include <stdio.h>

static int equeue_create_result;
static int equeue_create_inplace_result;
static int equeue_call_result;
static int equeue_call_in_result;
static int equeue_call_every_result;
static int equeue_post_result;
static int equeue_timeleft_result;

void equeue_create_mock_init(void) {
    // Inicializar el estado del mock
    equeue_create_result = 0;
}

void equeue_create_mock_destroy(void) {
    // Limpiar el estado del mock
    equeue_create_result = 0;
}

void equeue_create_set_result(bool result) {
    // Establecer el resultado del mock
    equeue_create_result = result;
}

void equeue_create_inplace_mock_init(void) {
    // Inicializar el estado del mock
    equeue_create_inplace_result = 0;
}

void equeue_create_inplace_mock_destroy(void) {
    // Limpiar el estado del mock
    equeue_create_inplace_result = 0;
}

void equeue_create_inplace_set_result(bool result) {
    // Establecer el resultado del mock
    equeue_create_inplace_result = result;
}

void equeue_call_mock_init(void) {
    // Inicializar el estado del mock
    equeue_call_result = 0;
}

void equeue_call_mock_destroy(void) {
    // Limpiar el estado del mock
    equeue_call_result = 0;
}

void equeue_call_set_result(bool result) {
    // Establecer el resultado del mock
    equeue_call_result = result;
}

void equeue_call_in_mock_init(void) {
    // Inicializar el estado del mock
    equeue_call_in_result = 0;
}

void equeue_call_in_mock_destroy(void) {
    // Limpiar el estado del mock
    equeue_call_in_result = 0;
}

void equeue_call_in_set_result(bool result) {
    // Establecer el resultado del mock
    equeue_call_in_result = result;
}

void equeue_call_every_mock_init(void) {
    // Inicializar el estado del mock
    equeue_call_every_result = 0;
}

void equeue_call_every_mock_destroy(void) {
    // Limpiar el estado del mock
    equeue_call_every_result = 0;
}

void equeue_call_every_set_result(bool result) {
    // Establecer el resultado del mock
    equeue_call_every_result = result;
}

void equeue_post_mock_init(void) {
    // Inicializar el estado del mock
    equeue_post_result = 0;
}

void equeue_post_mock_destroy(void) {
    // Limpiar el estado del mock
    equeue_post_result = 0;
}

void equeue_post_set_result(bool result) {
    // Establecer el resultado del mock
    equeue_post_result = result;
}

void equeue_timeleft_mock_init(void) {
    // Inicializar el estado del mock
    equeue_timeleft_result = 0;
}

void equeue_timeleft_mock_destroy(void) {
    // Limpiar el estado del mock
    equeue_timeleft_result = 0;
}

void equeue_timeleft_set_result(bool result) {
    // Establecer el resultado del mock
    equeue_timeleft_result = result;
}

int equeue_create(equeue_t *queue, size_t size){
    printf("Mock: equeue_create invocado con size_t = %zu\n", size);
    return equeue_create_result;
}

int equeue_create_inplace(equeue_t *queue, size_t size, void *buffer){
    printf("Mock: equeue_create_inplace invocado con size_t = %zu\n", size);
    return equeue_create_inplace_result;
}

void equeue_destroy(equeue_t *queue){
    printf("Mock: equeue_destroy invocado\n");
}

void equeue_dispatch(equeue_t *queue, int ms){
    printf("Mock: equeue_dispatch invocado con ms = %d\n", ms);
}

void equeue_break(equeue_t *queue){
    printf("Mock: equeue_break invocado\n");
}

int equeue_call(equeue_t *queue, void (*cb)(void *), void *data){
    printf("Mock: equeue_call invocado\n");
    return equeue_call_result;
}

int equeue_call_in(equeue_t *queue, int ms, void (*cb)(void *), void *data){
    printf("Mock: equeue_call_in invocado con ms = %d\n", ms);
    return equeue_call_in_result;
}

int equeue_call_every(equeue_t *queue, int ms, void (*cb)(void *), void *data){
    printf("Mock: equeue_call_every invocado con ms = %d\n", ms);
    return equeue_call_every_result;
}

void *equeue_alloc(equeue_t *queue, size_t size){
    printf("Mock: equeue_alloc invocado con size = %zu\n", size);
}

void equeue_dealloc(equeue_t *queue, void *event){
    printf("Mock: equeue_dealloc invocado\n");
}

void equeue_event_delay(void *event, int ms){
    printf("Mock: equeue_event_delay invocado con int = %d\n", ms);
}

void equeue_event_period(void *event, int ms){
    printf("Mock: equeue_event_period invocado con int = %d\n", ms);
}

void equeue_event_dtor(void *event, void (*dtor)(void *)){
    printf("Mock: equeue_event_dtor invocado\n");
}

int equeue_post(equeue_t *queue, void (*cb)(void *), void *event){
    printf("Mock: equeue_post invocado\n");
}

void equeue_cancel(equeue_t *queue, int id){
    printf("Mock: equeue_cancel invocado con int = %d\n", id);
}

int equeue_timeleft(equeue_t *q, int id){
    printf("Mock: equeue_timeleft invocado con int = %d\n", id);
    return equeue_timeleft_result;
}

void equeue_background(equeue_t *queue,
        void (*update)(void *timer, int ms), void *timer){
    printf("Mock: equeue_background invocado\n");
}

void equeue_chain(equeue_t *queue, equeue_t *target){
    printf("Mock: equeue_chain invocado\n");
}