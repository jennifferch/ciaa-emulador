/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef SAPI_H
#define SAPI_H


// Useful C libraries
#include <math.h>
#include <time.h>
#include <stdio.h> 

// ciaa libraries
#include "sapi_datatypes.h"
#include "sapi_peripheral_map.h"

#include "sapi_board.h"                  // Use clock peripheral
#include "sapi_tick.h"                   // Use Systick peripheral
#include "sapi_gpio.h"                   // Use GPIO peripherals
#include "sapi_uart.h"                   // Use UART peripherals
#include "sapi_adc.h"                    // Use ADC0 peripheral
#include "sapi_dac.h"                    // Use DAC peripheral
#include "sapi_i2c.h"                    // Use I2C0 peripheral
#include "sapi_spi.h"                    // Use SPI0 peripheral
#include "sapi_rtc.h"                    // Use RTC peripheral
#include "sapi_sleep.h"                  // Use ARM ASM instructions
#include "sapi_cyclesCounter.h"          // Use ARM Debug Registers
#include "sapi_usb_device.h"

// High Level peripherals

#include "sapi_stdio.h"                  // Use sapi_uart module
#include "sapi_print.h"                  // Use sapi_uart module
#include "sapi_debugPrint.h"             // Use sapi_print module
#include "sapi_consolePrint.h"           // Use sapi_print module

#include "sapi_convert.h"                // Use <string.h>

#include "sapi_delay.h"                  // Use sapi_tick module
#include "sapi_pwm.h"                    // Use sapi_sct and sapi_gpio modules
#include "sapi_circularBuffer.h"         // It has no dependencies

#include "sapi_button.h"                 // Use sapi_gpio module

// External Peripheral peripherals
#include "sapi_7_segment_display.h"      // Use sapi_gpio and sapi_delay modules
#include "sapi_keypad.h"                 // Use sapi_gpio and sapi_delay modules
#include "sapi_dht11.h"             // Use sapi_gpio peripheral
#include "sapi_servo.h"                  // Use sapi_gpio modules and sapi_timer
#include "sapi_rgb.h"                            // Use TIMER peripheral

#include "sapi_esp8266.h"                // Use sapi_uart module

#include "sapi_magnetometer_hmc5883l.h"  // Use sapi_i2c module
#include "sapi_magnetometer_qmc5883l.h"  // Use sapi_i2c module
#include "sapi_imu_mpu9250.h"            // Use sapi_i2c module
#include "sapi_imu_mpu60X0.h"            // Use sapi_i2c module
#include "sapi_eeprom24xx1025.h"         // Use sapi_i2c module

#include "sapi_ultrasonic_hcsr04.h"      //
#include "display_lcd_hd44780_gpios.h"
#include "sapi_display.h"

#endif