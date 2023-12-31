/* Copyright 2015, Eric Pernia.
 * Copyright 2016, Ian Olivieri.
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

/* Date: 2015-09-23 */

#ifndef _SAPI_PERIPHERALMAP_H_
#define _SAPI_PERIPHERALMAP_H_

/*==================[inclusions]=============================================*/

#include "sapi_datatypes.h"

/*==================[typedef]================================================*/

/* ----- Begin Pin Init Structs NXP LPC4337 ----- */

typedef struct {
   int8_t port;
   int8_t pin;
} pinInitLpc4337_t;

typedef struct {
   uint8_t lpcScuPort;
   uint8_t lpcScuPin;
   uint8_t lpcScuFunc;
} lpc4337ScuPin_t;

/* ------ End Pin Init Structs NXP LPC4337 ------ */


/* ------- Begin EDU-CIAA-NXP Peripheral Map ------ */

/* Defined for sapi_gpio.h */

#define BOARD edu_ciaa_nxp

typedef enum {

   // Configure GPIO pins for each board

   #if (BOARD == edu_ciaa_nxp)
      VCC = -2, GND = -1,
      // P1 headere
      T_FIL1 = 15,    T_COL2,    T_COL0,    T_FIL2,      T_FIL3,  T_FIL0,     T_COL1,
      CAN_TD,    CAN_RD,    RS232_TXD, RS232_RXD,
      // P2 header
      GPIO5 = 32,  
      GPIO0 = 16, GPIO1 = 17, GPIO2 = 18, GPIO3 = 19, GPIO7 = 20, GPIO8 = 21, 
      LCD1,      LCD2,      LCD3,      LCDRS,       LCD4,
    //  SPI_MISO = 22,
      ENET_TXD1, ENET_TXD0, ENET_MDIO, ENET_CRS_DV, ENET_MDC, ENET_TXEN, ENET_RXD1,
      GPIO6 = 59,     GPIO4 = 22,   
      LCDEN,
    //  SPI_MOSI = 23,
      ENET_RXD0,
      // Switches
      // 36   37     38     39
      TEC1 = 36,  TEC2 = 37,  TEC3 = 38,  TEC4 = 39,
      // Leds
      // 40   41     42     43     44     45

      LEDR  = 40,  
      LEDG  = 41,  
      LEDB  = 42,
      //#error EDU-CIAA-NXP
      RESET = 1337, 
      NC = (int)0xFFFFFFFF,

      I2C_SDA = 10,
      I2C_SCL = 11,
      LED1 = 50,
      LED2 = 52,
      LED3 = 53,
      LED4 = 55,
      SPI_MOSI = 9,
      SPI_MISO = 8,
      SPI_SCK  = 7,

      BUTTON2 = 1338, // hope this is not used yet
      SW1 = 1337, // hope this is not used yet
      SW2 = 1338 // hope this is not used yet
   #elif (BOARD == ciaa_nxp)
      DOUT0_C = -3, DOUT1_C = -3, DOUT2_C = -3, DOUT3_C = -3, DIN_COM = -3, 
      VCC = -2, VIN_24V = -2, VOUT_24V = -2,
      GND = -1, GNDA0 = -1, GNDA1 = -1, GND0 = -1, GND1 = -1, GND2 = -1, GND3 = -1, 
      // Born digital inputs
      I0   = 0, I1   = 1, DI2  = 2, I3   = 3, I4   = 4, I5   = 5, I6   = 6, I7   = 7,
      DI0  = 0, DI1  = 1, DI3  = 3, DI4  = 4, DI5  = 5, DI6  = 6, DI7  = 7,
      DIN0 = 0, DIN1 = 1, DIN2 = 2, DIN3 = 3, DIN4 = 4, DIN5 = 5, DIN6 = 6, DIN7 = 7,
      // Born digital outputs
      Q0    = 8, Q1    = 9, Q2    = 10, Q3    = 11, Q4    = 12, Q5    = 13, Q6    = 14, Q7    = 15,
      DO0   = 8, DO1   = 9, DO2   = 10, DO3   = 11, DO4   = 12, DO5   = 13, DO6   = 14, DO7   = 15,
      DOUT0 = 8, DOUT1 = 9, DOUT2 = 10, DOUT3 = 11, DOUT4 = 12, DOUT5 = 13, DOUT6 = 14, DOUT7 = 15,
      // P12 header
      GPIO0 = 16, GPIO1 = 17, GPIO2 = 18, GPIO3 = 19, GPIO7 = 20, GPIO8 = 21, 
      // P14 header
     // SPI_MISO = 22, SPI_MOSI = 23, SPI_CS = 23,
      //#error CIAA-NXP

      TEC1 = 36,  TEC2 = 37,  TEC3 = 38,  TEC4 = 39,
              LEDR  = 40,  
      LEDG  = 41,  
      LEDB  = 42,
      RESET = 1337, 
      NC = (int)0xFFFFFFFF,
      p5 = 9,
      p6 = 8,
      p7 = 7,
      p11 = 18,
      p12 = 17,
      p13 = 15,
      I2C_SDA = 10,
      I2C_SCL = 11,
      LED1 = 50,
      LED2 = 52,
      LED3 = 53,
      LED4 = 55,
      SPI_MOSI = 9,
      SPI_MISO = 8,
      SPI_SCK  = 7,

      BUTTON2 = 1338, // hope this is not used yet
      SW1 = 1337, // hope this is not used yet
      SW2 = 1338 // hope this is not used yet
   #else
      #error BOARD not supported yet!
   #endif
} gpioMap_t; 

// Configure GPIO pins for each board

#if (BOARD == ciaa_nxp)
   #define BTN                 DI7
   #define LED                 DO7
#elif (BOARD == edu_ciaa_nxp)
   #define BTN                 TEC1
   #define LED                 LEDB
#else
   #error BOARD not supported yet!
#endif
#define CIAA_BOARD_BUTTON   BTN
#define CIAA_BOARD_LED      LED

/* Defined for sapi_adc.h */
typedef enum {
	#if (BOARD == edu_ciaa_nxp)
	   CH1 = 0, // CH1 =   2 ADC0_1/ADC1_1
	   CH2 = 1, // CH2 = 143 ADC0_2/ADC1_2
	   CH3 = 2, // CH3 = 139 ADC0_3/ADC1_3
	   CH4 = 3, // CH4 =  ADC0_4/ADC1_4
	#elif (BOARD == ciaa_nxp)
	   AIN0 = 0, // AIN0 =   2 ADC0_1/ADC1_1
	   AIN1 = 1, // AIN1 = 143 ADC0_2/ADC1_2
	   AIN2 = 2, // AIN2 = 139 ADC0_3/ADC1_3
	   AIN3 = 3, // AIN3 = 138 ADC0_4/ADC1_4
	   AI0 = 0,  // AIN0 =   2 ADC0_1/ADC1_1
	   AI1 = 1,  // AIN1 = 143 ADC0_2/ADC1_2
	   AI2 = 2,  // AIN2 = 139 ADC0_3/ADC1_3
	   AI3 = 3,  // AIN3 = 138 ADC0_4/ADC1_4
	#else
	   #error BOARD not supported yet!
	#endif
} adcMap_t;

/* Defined for sapi_dac.h */
typedef enum {
	#if (BOARD == edu_ciaa_nxp)
		DAC  = 0,
		DAC0 = 0,
	#elif (BOARD == ciaa_nxp)
		AO  = 0,
		AO0 = 0,
		AOUT = 0,
		DAC  = 0,
		DAC0 = 0,
	#else
	   #error BOARD not supported yet!
	#endif
} dacMap_t;

/* Defined for sapi_uart.h */
// Note that:
// - If use UART_GPIO you can't use UART_485 and vice versa.
// - If use UART_USB you can't use UART_ENET and vice versa.
typedef enum {
	#if (BOARD == edu_ciaa_nxp)
	   UART_GPIO = 0, // Hardware UART0 via GPIO1(TX), GPIO2(RX) pins on header P0
	   UART_485  = 1, // Hardware UART0 via RS_485 A, B and GND Borns
		// Hardware UART1 not routed
	   UART_USB  = 3, // Hardware UART2 via USB DEBUG port
	   UART_ENET = 4, // Hardware UART2 via ENET_RXD0(TX), ENET_CRS_DV(RX) pins on header P0
	   UART_232  = 5, // Hardware UART3 via 232_RX and 232_tx pins on header P1
	#elif (BOARD == ciaa_nxp)
	   UART_485  = 1, // Hardware UART0 via RS_485 A, B and GND Borns
					  // Hardware UART1 not routed
	   UART_USB  = 3, // Hardware UART2 via USB DEBUG port
	   UART_232  = 5, // Hardware UART3 via 232_RX and 232_tx pins on header P1
	#else
	   #error BOARD not supported yet!
	#endif
   UART_MAXNUM,
} uartMap_t;

/*Defined for sapi_timer.h*/
//NOTE: if servo is enable (servoInit used) the only available timer to use is TIMER0
typedef enum {
   TIMER0, TIMER1, TIMER2, TIMER3
} timerMap_t;
typedef enum {
   TIMERCOMPAREMATCH0, TIMERCOMPAREMATCH1, TIMERCOMPAREMATCH2, TIMERCOMPAREMATCH3
} timerCompareMatch_t;

/*Defined for sapi_sct.h*/
// NOTE: CTOUT11 has no SCT mode associated, so it can't be used!
// NOTE: if pwm is enable (pwmInit used) there will be no sct channels available
typedef enum {
   CTOUT0, CTOUT1, CTOUT2, CTOUT3, CTOUT4, CTOUT5, CTOUT6, CTOUT7, CTOUT8,
   CTOUT9, CTOUT10, CTOUT11, CTOUT12, CTOUT13
} sctMap_t;

/*Defined for sapi_pwm.h*/
typedef enum {
   PWM0, PWM1, PWM2, PWM3, PWM4, PWM5, PWM6, PWM7, PWM8, PWM9, PWM10
} pwmMap_t;

/*Defined for sapi_servo.h*/
typedef enum {
   SERVO0, SERVO1, SERVO2, SERVO3, SERVO4, SERVO5, SERVO6, SERVO7, SERVO8
} servoMap_t;

/*Defined for sapi_i2c.h*/
/* Comment because already defined in "i2c_18xx_43xx.h"*/
/*
typedef enum{
   I2C0 // TODO: Add support for I2C1
} i2cMap_t;
*/
typedef uint8_t i2cMap_t;

typedef enum {
   SPI0
} spiMap_t;

typedef enum {
    PullUp = 0,
    PullDown = 3,
    PullNone = 2,
    Repeater = 1,
    OpenDrain = 4,
    PullDefault = PullDown
} PinMode;

// version of PINCON_TypeDef using register arrays
typedef struct {
  uint32_t PINSEL[11];
  uint32_t RESERVED0[5];
  uint32_t PINMODE[10];
  uint32_t PINMODE_OD[5];
} PINCONARRAY_TypeDef;

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

#ifndef __IO
#define __IO volatile
#endif
#ifndef __I
#define __I  volatile const
#endif
#ifndef __O
#define __O  volatile
#endif

typedef struct {
    gpioMap_t  pin;
    uint32_t mask;

    __IO uint32_t *reg_dir;
    __IO uint32_t *reg_set;
    __IO uint32_t *reg_clr;
    __I  uint32_t *reg_in;
} gpio_t;

/** GPIO IRQ events
 */
typedef enum {
    IRQ_NONE,
    IRQ_RISE,
    IRQ_FALL
} gpio_irq_event;

struct gpio_irq_s {
    uint32_t port;
    uint32_t pin;
    uint32_t id;
};

typedef struct gpio_irq_s gpio_irq_t;
/*==================[end of file]============================================*/
#endif /* _SAPI_PERIPHERALMAP_H_ */
