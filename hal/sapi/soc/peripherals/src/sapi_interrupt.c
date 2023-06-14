/* Copyright 2015-2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/* Date: 2015-09-23 */

/*==================[inclusions]=============================================*/
#include <stdlib.h>
#include "peripherals/inc/sapi_interrupt.h"
#include "peripherals/inc/sapi_gpio.h"
#include "peripherals/inc/sapi_delay.h"

#include "callback/CallbackInterface.h"
/*==================[macros and definitions]=================================*/
#define INTERRUP_IRQ_INST_NUM  50   
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
typedef struct {
    gpio_irq_event event_rise;
    gpio_irq_event event_fall;
    gpioMap_t pin;
    uint32_t id;
    gpio_t gpio;
    gpio_irq_t gpio_irq;
    bool_t state;

} config_interrupIn;

typedef struct {
  CallbackWrapper* rise;
  CallbackWrapper* fall;
} InterruptInC;

InterruptInC* interrupt;

config_interrupIn _irq_instances[INTERRUP_IRQ_INST_NUM];
int32_t index_irq_instance = 0;
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* Set up and initialize board hardware */
void interruptInit(gpioMap_t pin){
    // Have we reached the end of the list?
    if(index_irq_instance < INTERRUP_IRQ_INST_NUM ){
       index_irq_instance++;
    }else{
    // Initialize?
       index_irq_instance = 1;
    }

    gpio_t gpio;
    gpio_irq_t gpio_irq;
    gpio_interrupt_init(&gpio_irq, pin, (&_irq_handler), index_irq_instance);
    
    gpio_init_in(&gpio, pin);

    gpio_interrupt_set(&gpio_irq, IRQ_FALL, ON);

    gpio_interrupt_set(&gpio_irq, IRQ_RISE, ON);


   _irq_instances[index_irq_instance].pin = pin;
   _irq_instances[index_irq_instance].id = index_irq_instance;
   _irq_instances[index_irq_instance].gpio = gpio;
   _irq_instances[index_irq_instance].gpio_irq = gpio_irq;
   _irq_instances[index_irq_instance].state = ON;

   interrupt = (InterruptInC*)malloc(sizeof(InterruptInC));
   interrupt->rise = NULL;
   interrupt->fall = NULL;

}

int32_t get_interrupt_index(uint32_t id){
    /* Find index for INTERRUP instance. */
    for (uint32_t i = 0; i < INTERRUP_IRQ_INST_NUM; i++) {
        if (id == _irq_instances[i].id ) {
            return i;
        }
    }
    /* Invalid data given. */
    // Assert(false);
    return 0;
}

void _irq_handler(uint32_t id, gpio_irq_event event){
    int32_t index =  get_interrupt_index(id);

    if ((index != 0)) {
        switch (event) {
            case IRQ_RISE:

                 if(_irq_instances[index].state == OFF){
                   _irq_instances[index].state = ON;
                }else{
                   _irq_instances[index].state = ON;
                }
                if (interrupt->rise) {               
                     callback_call(interrupt->rise);
                }
                break;
            case IRQ_FALL:

                if(_irq_instances[index].state == ON){
                   _irq_instances[index].state = OFF;

                }else{
                   _irq_instances[index].state = OFF;
                }

                if (interrupt->fall) {                
                     callback_call(interrupt->fall);
                }


                break;
            case IRQ_NONE:
                break;
        }
    }
}


uint8_t get_interrupt_state(gpioMap_t pin){
   	/* Find index for GPIO instance. */
	for (int32_t i = 0; i < INTERRUP_IRQ_INST_NUM; i++) {
		if (pin == _irq_instances[i].pin)
			return _irq_instances[i].state;
	}
    /* Invalid data given. */
	return ON;
}

bool_t  read_event_state(gpioMap_t pin){
    bool_t ret_val = ON;

    // wait until supply switched off
    delay(1);

    ret_val = get_interrupt_state(pin);

    return ret_val;
}


void interruptin_fall(void (*func)())
{ 
    CallbackWrapper* callFunc = callback_create(func);
    if (func) {
        interrupt->fall = callFunc;
    } else {
        interrupt->fall = NULL;
    }   
}


void interruptin_rise(void (*func)())
{ 
    CallbackWrapper* callFunc = callback_create(func);

    if (func) {
        interrupt->rise = callFunc;
    } else {
        interrupt->rise = NULL;
    }
}

/*==================[end of file]============================================*/
