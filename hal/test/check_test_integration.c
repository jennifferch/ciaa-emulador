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
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdlib.h> 
#include <cmocka.h>
#include <check.h>

#include "gpio_api_mock.h"
#include "sapi_interrupt_mock.h"
#include "sapi_gpio.h"
#include "delay_api_mock.h"
#include "sapi_tick_mock.h"
#include "sapi_delay.h"



// Definir la prueba unitaria para la función gpioInit
START_TEST(test_interrupt_with_gpio_interaction) {
    // Variable de entrada para la funcion gpioRead
    gpioMap_t pin = TEC1;

    // Configurar el comportamiento esperado del mock gpio_read
    interrupt_set_result(ON);  // Éxito en la lectura

    // Llamar a la función gpioRead que utiliza el mock
    bool_t result = gpioRead(pin);

    // Verificar que la función gpio_read devuelve verdadero
    assert_true(result);

    // Restaurar el comportamiento original del mock gpio_read
    interrupt_set_result(OFF);  // Error en la lectura
}
END_TEST

START_TEST( test_gpioWrite_with_interrupt_interaction)  {
    // Variable de entrada para la funcion gpioRead
    gpioMap_t pin = LED1;
    bool_t value = ON;

    // Llamar a la función gpioWrite que utiliza el mock
    bool_t result = gpioWrite(pin, ON);

    // Verificar que la función gpio_read devuelve verdadero
    assert_true(result);

}
END_TEST

START_TEST( test_gpioToggle_with_interrupt_interaction ) {
    // Variable de entrada para la funcion gpioRead
    gpioMap_t pin = LED1;

    // Llamar a la función gpioWrite que utiliza el mock
    bool_t result = gpioToggle(pin);

    // Verificar que la función gpio_read devuelve verdadero
    assert_true(result);

}
END_TEST

START_TEST(test_delayInaccurateNs_with_tick_interaction) {
    tick_t delay_ms = 500;

    // Llamar a la función delayInaccurateMs que utiliza el mock
    delayInaccurateMs(delay_ms);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "delayInaccurateMs ejecutado sin errores");
}
END_TEST

START_TEST(test_delay_with_tick_interaction) {
    tick_t duration_ms = 200;

    // Llamar a la función delayInaccurateNs que utiliza el mock
    delay(duration_ms);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "delay ejecutado sin errores");
}
END_TEST

START_TEST(test_delayWrite_with_tick_interaction) {
    delay_t refreshButton;
    tick_t duration = 1000;

    // Llamar a la función delayInit que utiliza el mock
    delayWrite( &refreshButton, duration);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "delayWrite ejecutado sin errores");
}
END_TEST

START_TEST(test_delayInaccurateMs_with_tick_interaction) {
    tick_t delay_ms = 500;

    // Llamar a la función delayInaccurateMs que utiliza el mock
    delayInaccurateMs(delay_ms);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "delayInaccurateMs ejecutado sin errores");
}
END_TEST

START_TEST(test_delayInaccurateUs_with_tick_interaction) {
    tick_t delay_us = 1000;

    // Llamar a la función delayInaccurateUs que utiliza el mock
    delayInaccurateUs(delay_us);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "delayInaccurateUs ejecutado sin errores");
}
END_TEST


START_TEST(test_delayInit_with_tick_interaction) {
    delay_t refreshButton;
    tick_t duration = 1000;

    // Llamar a la función delayInit que utiliza el mock
    delayInit( &refreshButton, duration);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "delayInit ejecutado sin errores");
}
END_TEST

START_TEST(test_delayRead_with_tick_interaction) {
    // Variable de entrada para la funcion delayRead
    delay_t refreshButton;
    uint64_t tick_set_result = 500;

    // Configurar el comportamiento esperado del mock  delay_read
    tickRead_set_result(tick_set_result);  // Éxito en la lectura

    // Llamar a la función delayRead que utiliza el mock
    bool_t result = delayRead(&refreshButton);

    // Verificar que la función delay_read devuelve verdadero
    assert_true(result);

    // Restaurar el comportamiento original del mock delay_read
    tickRead_set_result(0);  // Error en la lectura
}
END_TEST

int main(void) {
    Suite *s = suite_create("Integration Tests");
    TCase *tc_core = tcase_create("Core");

    // Pruebas de integración
    tcase_add_test(tc_core, test_interrupt_with_gpio_interaction);
    tcase_add_test(tc_core, test_delayInaccurateNs_with_tick_interaction);
    tcase_add_test(tc_core, test_delayWrite_with_tick_interaction);
    tcase_add_test(tc_core, test_delay_with_tick_interaction);
    tcase_add_test(tc_core, test_gpioWrite_with_interrupt_interaction);
    tcase_add_test(tc_core, test_gpioToggle_with_interrupt_interaction);
    tcase_add_test(tc_core, test_delayInaccurateMs_with_tick_interaction);
    tcase_add_test(tc_core, test_delayInaccurateUs_with_tick_interaction);
    tcase_add_test(tc_core, test_delayInit_with_tick_interaction);
    tcase_add_test(tc_core, test_delayRead_with_tick_interaction);

    suite_add_tcase(s, tc_core);

    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}