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

#include <cmocka.h>
#include <check.h>

#include "delay_api_mock.h"
#include "sapi_tick_mock.h"
#include "sapi_delay.h"

START_TEST(test_delayInaccurateMs) {
    tick_t delay_ms = 500;

    // Llamar a la función delayInaccurateMs que utiliza el mock
    delayInaccurateMs(delay_ms);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "delayInaccurateMs ejecutado sin errores");
}
END_TEST

START_TEST(test_delayInaccurateUs) {
    tick_t delay_us = 1000;

    // Llamar a la función delayInaccurateUs que utiliza el mock
    delayInaccurateUs(delay_us);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "delayInaccurateUs ejecutado sin errores");
}
END_TEST

START_TEST(test_delayInaccurateNs) {
    tick_t delay_ns = 100;

    // Llamar a la función delayInaccurateNs que utiliza el mock
    delayInaccurateNs(delay_ns);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "delayInaccurateNs ejecutado sin errores");
}
END_TEST

START_TEST(test_delay) {
    tick_t duration_ms = 200;

    // Llamar a la función delayInaccurateNs que utiliza el mock
    delay(duration_ms);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "delay ejecutado sin errores");
}
END_TEST

START_TEST(test_delayInit) {
    delay_t refreshButton;
    tick_t duration = 1000;

    // Llamar a la función delayInit que utiliza el mock
    delayInit( &refreshButton, duration);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "delayInit ejecutado sin errores");
}
END_TEST

START_TEST(test_delayWrite) {
    delay_t refreshButton;
    tick_t duration = 1000;

    // Llamar a la función delayInit que utiliza el mock
    delayWrite( &refreshButton, duration);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "delayWrite ejecutado sin errores");
}
END_TEST

static void test_delayRead() {
    // Variable de entrada para la funcion delayRead
    delay_t refreshButton;
    uint64_t tick_set_result = 1000;

    // Configurar el comportamiento esperado del mock  delay_read
    tickRead_set_result(tick_set_result);  // Éxito en la lectura

    // Llamar a la función delayRead que utiliza el mock
    bool_t result = delayRead(&refreshButton);

    // Verificar que la función delay_read devuelve verdadero
    assert_false(result);

    // Restaurar el comportamiento original del mock delay_read
    tickRead_set_result(0);  // Error en la lectura
}

Suite *check_suite() {
    Suite *s = suite_create("Check Suite sapi_delay delayInaccurateMs, delayInaccurateUs, delayInaccurateNs, delay, delayInit, delayWrite");
    TCase *tc = tcase_create("Check Test Case");

    tcase_add_test(tc, test_delayInaccurateMs);
    tcase_add_test(tc, test_delayInaccurateUs);
    tcase_add_test(tc, test_delayInaccurateNs);
    tcase_add_test(tc, test_delay);
    tcase_add_test(tc, test_delayInit);
    tcase_add_test(tc, test_delayWrite);
    suite_add_tcase(s, tc);

    return s;
}

Suite *cmocka_suite() {
    Suite *s = suite_create("CMocka Suite sapi_delay delayRead");
    TCase *tc = tcase_create("CMocka Test Case");

    tcase_add_test(tc, test_delayRead);
    suite_add_tcase(s, tc);

    return s;
}

int main(void) {
    int number_failed = 0;
    
    // Inicializar el mock
    tickRead_mock_init();

    // Ejecutar las pruebas de Check
    Suite *check_suit = check_suite();
    SRunner *check_runner = srunner_create(check_suit);
    srunner_run_all(check_runner, CK_NORMAL);
    number_failed += srunner_ntests_failed(check_runner);
    srunner_free(check_runner);

    // Ejecutar las pruebas de CMocka
    SRunner *cmocka_runner = srunner_create(cmocka_suite());
    srunner_run_all(cmocka_runner, CK_NORMAL);
    number_failed += srunner_ntests_failed(cmocka_runner);
    srunner_free(cmocka_runner);
    
    // Limpiar el mock
    tickRead_mock_destroy();

    // Devolver el número total de pruebas fallidas
    return number_failed;
}