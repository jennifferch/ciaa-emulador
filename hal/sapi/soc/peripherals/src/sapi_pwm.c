/* Copyright 2016, Ian Olivieri
 * Copyright 2016, Eric Pernia.
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
 */

/* Date: 2016-02-10 */

/*==================[inclusions]=============================================*/
#include "sapi_pwm.h"

/*==================[c++]====================================================*/

/*==================[macros and definitions]=================================*/

/*==================[internal functions declaration]=========================*/
void pwm_set_instance(gpioMap_t pin);
void lock_deep_sleep(bool _deep_sleep_locked);
void unlock_deep_sleep(bool _deep_sleep_locked);
pwmOutClass* pwm_get_instance(gpioMap_t pin);

/*==================[internal data definition]===============================*/

pwmOutClass _pwm_instances[PWM_INST_NUM];
int32_t pwm_index_instance = 0;
/*==================[external functions definition]==========================*/


int32_t _pwm_get_inst_index(gpioMap_t pin){
    int32_t index = 0;
    /* Find index for ADC instance. */
    for (uint32_t i = 0; i < PWM_INST_NUM; i++) {
        if (pin == _pwm_instances[i].pin ) {
            return i;
        }
    }

    /* Invalid data given. */
   // Assert(false);
    return 0;
}

pwmOutClass* pwm_get_instance(gpioMap_t pin
                                  ){
   	int32_t i;
	for (i = 0; i < PWM_INST_NUM; i++) {
		if (pin == _pwm_instances[i].pin)
			return &_pwm_instances[i];
	}
	return NULL;
}

void lock_deep_sleep(bool _deep_sleep_locked){
    if (_deep_sleep_locked == false) {
        _deep_sleep_locked = true;
    }
}

    /** Unlock deep sleep in case it is locked */
void unlock_deep_sleep(bool _deep_sleep_locked){
    if (_deep_sleep_locked == true) {
        _deep_sleep_locked = false;
    }
}


void pwmInit(gpioMap_t pin, pwmInit_t config){
        pwm_set_instance(pin);
}

/*
 * @brief:   change the value of the pwm at the selected pin
 * @param:   pwmNumber:   ID of the pwm, from 0 to 10
 * @param:   value:   8bit value, from 0 to 255
 * @return:   True if the value was successfully changed, False if not.
 */
bool_t pwmWrite( gpioMap_t pin, uint8_t value){
   bool_t success = FALSE;

   pwmOutClass* pwmOut = pwm_get_instance(pin);
   pwmOut->value = value;
   lock_deep_sleep(pwmOut->_deep_sleep_locked_instance);
   pwm_write(&pwmOut->_pwm_instance, value);

   return success;
}

/*
 * @brief:   read the value of the pwm in the pin
 * @param:   pwmNumber:   ID of the pwm, from 0 to 10
 * @return:   value of the pwm in the pin (0 ~ 255).
 *   If an error ocurred, return = EMPTY_POSITION = 255
 */
uint8_t pwmRead( gpioMap_t pin){
    pwmOutClass* pwmOut = pwm_get_instance(pin);

    float val = pwm_read(&pwmOut->_pwm_instance);
    return val;
}

void pwm_set_instance(gpioMap_t pin
                        ){

   // First find a gap in the array (if there is one)
  /* while( (_pwmOutClass_list[index].pin != pin) && (index < MAX_INSTANCES) ){
      index++;
   }*/
   pwm_index_instance++;

   pwm_t _pwm_init;
   // If we're here, there is a space in the task array
   _pwm_instances[pwm_index_instance]._pwm_instance  = _pwm_init;
   _pwm_instances[pwm_index_instance]._deep_sleep_locked_instance  = false;
   _pwm_instances[pwm_index_instance].pin = pin;
   _pwm_instances[pwm_index_instance].value = 0;

   pwm_init(&_pwm_instances[pwm_index_instance]._pwm_instance, _pwm_instances[pwm_index_instance].pin );

}

uint8_t pwmIsAttached( pwmMap_t pwmNumber ){
    
}


