#ifndef _EQUEUE_MOCK_H
#define _EQUEUE_MOCK_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdbool.h>


#include <stdint.h>
#include <string.h> 
#include <time.h>

#include <stddef.h>
#include "sapi_peripheral_map.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef volatile int equeue_sema_t;
typedef unsigned equeue_mutex_t;

struct equeue_event {
    unsigned size;
    uint8_t id;
    uint8_t generation;

    struct equeue_event *next;
    struct equeue_event *sibling;
    struct equeue_event **ref;

    unsigned target;
    int period;
    void (*dtor)(void *);

    void (*cb)(void *);
    // data follows
};

// Event queue structure
typedef struct equeue {
    struct equeue_event *queue;
    unsigned tick;
    bool_t break_requested;
    uint8_t generation;

    unsigned char *buffer;
    unsigned npw2;
    void *allocated;

    struct equeue_event *chunks;
    struct equeue_slab {
        size_t size;
        unsigned char *data;
    } slab;

    struct equeue_background {
        bool_t active;
        void (*update)(void *timer, int ms);
        void *timer;
    } background;

    equeue_sema_t eventsema;
    equeue_mutex_t queuelock;
    equeue_mutex_t memlock;

    bool_t dispatch_called;

} equeue_t;

int equeue_create(equeue_t *queue, size_t size);

int equeue_create_inplace(equeue_t *queue, size_t size, void *buffer);

void equeue_destroy(equeue_t *queue);

void equeue_dispatch(equeue_t *queue, int ms);

void equeue_break(equeue_t *queue);

int equeue_call(equeue_t *queue, void (*cb)(void *), void *data);
int equeue_call_in(equeue_t *queue, int ms, void (*cb)(void *), void *data);
int equeue_call_every(equeue_t *queue, int ms, void (*cb)(void *), void *data);

void *equeue_alloc(equeue_t *queue, size_t size);
void equeue_dealloc(equeue_t *queue, void *event);

void equeue_event_delay(void *event, int ms);
void equeue_event_period(void *event, int ms);
void equeue_event_dtor(void *event, void (*dtor)(void *));

int equeue_post(equeue_t *queue, void (*cb)(void *), void *event);

void equeue_cancel(equeue_t *queue, int id);

int equeue_timeleft(equeue_t *q, int id);

void equeue_background(equeue_t *queue,
        void (*update)(void *timer, int ms), void *timer);

void equeue_chain(equeue_t *queue, equeue_t *target);

#ifdef __cplusplus
}
#endif

#endif 
