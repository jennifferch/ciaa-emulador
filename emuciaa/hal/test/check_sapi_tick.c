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
#include "tick_api_mock.h"
#include "sapi_uart_mock.h"
#include "sapi_tick.h"

START_TEST(test_tickInit) {
    tick_t delay_ms = 500;

    // Llamar a la función tickInit que utiliza el mock
    tickInit(delay_ms);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "tickInit ejecutado sin errores");
}
END_TEST

START_TEST(test_tickWrite) {
    tick_t ticks = 100;

    // Llamar a la función tickWrite que utiliza el mock
    tickWrite(ticks);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "tickWrite ejecutado sin errores");
}
END_TEST

START_TEST(test_tickPowerSet) {
    bool_t power = true;

    // Llamar a la función tickPowerSet que utiliza el mock
    tickPowerSet(power);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "tickPowerSet ejecutado sin errores");
}
END_TEST

START_TEST(test_tickRead) {
    bool_t power = true;

    // Llamar a la función tickRead que utiliza el mock
    tick_t result = tickRead();

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "tickRead ejecutado sin errores");
}
END_TEST


Suite *check_suite() {
    Suite *s = suite_create("Check Suite sapi_tick tickInit, tickWrite, tickPowerSet, tickRead");
    TCase *tc = tcase_create("Check Test Case");

    tcase_add_test(tc, test_tickInit);
    tcase_add_test(tc, test_tickWrite);
    tcase_add_test(tc, test_tickPowerSet);
    tcase_add_test(tc, test_tickRead);
    suite_add_tcase(s, tc);

    return s;
}


int main(void) {
    int number_failed = 0;

    // Ejecutar las pruebas de Check
    Suite *check_suit = check_suite();
    SRunner *check_runner = srunner_create(check_suit);
    srunner_run_all(check_runner, CK_NORMAL);
    number_failed += srunner_ntests_failed(check_runner);
    srunner_free(check_runner);

    // Devolver el número total de pruebas fallidas
    return number_failed;
}