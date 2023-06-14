/* Copyright 2015-2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
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

#include "sapi_gpio.h"
#include "gpio_interrupt_api.h"
#include "sapi_interrupt.h"
/*==================[macros and definitions]=================================*/
#define GPIO_INST_NUM  50   
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
void configInit(gpioMap_t pin, gpioMap_t pinAnt);
void set_gpio_instance(gpioMap_t pin, bool_t value);
config_t* get_gpio_instance(gpioMap_t pin);
/*==================[internal data definition]===============================*/

config_t _gpio_instances[GPIO_INST_NUM];
int32_t index_instance_gpio = 0;
/*==================[external functions definition]==========================*/
bool_t gpioInit(gpioMap_t pin, gpioInit_t config){
    if( pin == VCC ){
        return FALSE;
    }
    if( pin == GND ){
        return FALSE;
    }

    bool_t ret_val     = 1;
    int8_t pinNamePort = 0;
    int8_t pinNamePin  = 0;
    int8_t func        = 0;
    int8_t gpioPort    = 0;
    int8_t gpioPin     = 0;

    gpio_t gpio;
    gpio_init(&gpio, pin);

    switch(config) {

        case GPIO_ENABLE:
            /* Initializes GPIO */
            //Chip_GPIO_Init(LPC_GPIO_PORT);
            break;

        case GPIO_INPUT:
        /* Chip_SCU_PinMux(
                pinNamePort,
                pinNamePin,
                SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
                func
            );
            Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), GPIO_INPUT );*/
            break;

        case GPIO_INPUT_PULLUP:
            /*Chip_SCU_PinMux(
                pinNamePort,
                pinNamePin,
                SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
                func
            );
            Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), GPIO_INPUT );*/
            break;

        case GPIO_INPUT_PULLDOWN:
            /*Chip_SCU_PinMux(
                pinNamePort,
                pinNamePin,
                SCU_MODE_PULLDOWN | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
                func
            );
            Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), GPIO_INPUT );*/
            break;
        case GPIO_INPUT_PULLUP_PULLDOWN:
            /*Chip_SCU_PinMux(
                pinNamePort,
                pinNamePin,
                SCU_MODE_REPEATER | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
                func
            );
            Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), GPIO_INPUT );*/
            break;

        case GPIO_OUTPUT:
            /*Chip_SCU_PinMux(
                pinNamePort,
                pinNamePin,
                SCU_MODE_INACT | SCU_MODE_ZIF_DIS | SCU_MODE_INBUFF_EN,
                func
            );
            Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), GPIO_OUTPUT );
            Chip_GPIO_SetPinState( LPC_GPIO_PORT, gpioPort, gpioPin, 0);*/
            break;

        default:
            ret_val = 0;
            break;
    }

    return ret_val;
}

bool_t gpioWrite( gpioMap_t pin, bool_t value ){
    bool_t ret_val  = 1;
    set_gpio_instance(pin, value);
    return  ret_val;
}

bool_t gpioToggle( gpioMap_t pin ){
    return gpioWrite( pin, !gpioRead(pin) );
}

/**
 * Lee el estado logico de un pin.
 * @param gpioMap_t pin a leer.
 * @return estado logico leido.
 */
bool_t gpioRead( gpioMap_t pin ){
    if(pin == TEC1 || pin == TEC2 || 
       pin == TEC3 || pin == TEC4 || 
       pin == RESET){    
        
       return read_event_state(pin);

    }else{
       bool_t ret_val = OFF;
       config_t* instance = get_gpio_instance(pin);

       if(instance != NULL){
        ret_val = (bool_t) gpio_read(&instance->gpio);
       }
        
       return ret_val;
    }
}


config_t* get_gpio_instance(gpioMap_t pin){
   	/* Find index for GPIO instance. */
	for (int32_t i = 0; i < GPIO_INST_NUM; i++) {
		if (pin == _gpio_instances[i].pin)
			return &_gpio_instances[i];
	}
    /* Invalid data given. */
	return NULL;
}


void set_gpio_instance( gpioMap_t pin, bool_t value ){
   // Have we reached the end of the list?
   if( index_instance_gpio < GPIO_INST_NUM ){
     index_instance_gpio++;
   }

   gpio_t gpioInit;
   _gpio_instances[index_instance_gpio].gpio = gpioInit;
   _gpio_instances[index_instance_gpio].pin = pin;
   _gpio_instances[index_instance_gpio].index = index_instance_gpio;

   gpio_init_out_ex(&_gpio_instances[index_instance_gpio].gpio, pin, value);   
}
  
/*==================[end of file]============================================*/
