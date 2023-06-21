/* Copyright 2011, ChaN.
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
 *
 */

/* Date: 2016-03-07 */

/*==================[inclusions]=============================================*/

#include "sapi_rtc.h"
#include <time.h>
#include "../test/wrapper/sapi_rtc_wrapper.h"

/*==================[macros and definitions]=================================*/
#define LPC_RTC        
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*
 * @Brief: Configure RTC peripheral.
 * @param  rtc_t rtc: RTC structure
 * @return bool_t true (1) if config it is ok
 */
bool_t rtcInit( void ){
   bool_t ret_val = 1;

      /* RTC Block section ------------------------- */
      // Chip_RTC_Init(LPC_RTC);
      
   rtc_init();
      
      /* Enable rtc (starts increase the tick counter
         and second counter register) */
      //Chip_RTC_Enable(LPC_RTC, ENABLE);
   delay(2100);

   return ret_val;
}

/*
 * @Brief: Get time from RTC peripheral.
 * @param  rtc_t rtc: RTC structure
 * @return bool_t true (1) if config it is ok
 */
bool_t rtcRead( rtc_t * rtc ){
   bool_t ret_val = 1;
   // RTC_TIME_T rtcTime;
   //Chip_RTC_GetFullTime(LPC_RTC, &rtcTime);
   struct tm t = rtc_read();
   rtc->sec =  t.tm_sec;
   rtc->min = t.tm_min;
   rtc->hour = t.tm_hour;
   rtc->wday = t.tm_mday;
   rtc->mday = t.tm_mday;
   rtc->month = t.tm_mon;
   rtc->year = t.tm_year;

   return ret_val;
}

/*
 * @Brief: Set time on RTC peripheral.
 * @param  rtc_t rtc: RTC structure
 * @return bool_t true (1) if config it is ok
 */
bool_t rtcWrite( rtc_t * rtc ){
   bool_t ret_val = 1;
   struct tm t;

   t.tm_sec = rtc->sec;
   t.tm_min = rtc->min;
   t.tm_hour = rtc->hour;
   t.tm_mday = rtc->mday;
   t.tm_mon = rtc->month;
   t.tm_year = rtc->year;

   rtc_write(&t);

   return ret_val;
}

/*==================[end of file]============================================*/
