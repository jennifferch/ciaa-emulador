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

#include "rtc_api_mock.h"
#include "sapi_delay_mock.h"
#include "sapi_rtc.h"

// Definir la prueba unitaria para la función gpioInit
START_TEST(test_rtcInit) {
    // Llamar a la función rtcInit que utiliza el mock
    bool_t result = rtcInit();
    assert_true(result);
}
END_TEST

static void test_rtcRead()
{
    // Variable de entrada para la funcion rtcRead
    rtc_t rtc;

    struct tm resultTM = rtc_read();
    assert_true(resultTM.tm_sec >= 0 && resultTM.tm_sec <= 59);
    assert_true(resultTM.tm_min >= 0 && resultTM.tm_min <= 59);
    assert_true(resultTM.tm_hour >= 0 && resultTM.tm_hour <= 23);
    assert_true(resultTM.tm_mday >= 1 && resultTM.tm_mday <= 31);
    assert_true(resultTM.tm_mon >= 0 && resultTM.tm_mon <= 11);
    assert_true(resultTM.tm_year >= 0); 
    assert_true(resultTM.tm_wday >= 0 && resultTM.tm_wday <= 6);
    assert_true(resultTM.tm_yday >= 0 && resultTM.tm_yday <= 365);

    bool_t result = rtcRead(&rtc);
    // Verificar que la función rtcWrite devuelve verdadero
    assert_true(result);
}

static void test_rtcWrite() {
    // Variable de entrada para la funcion rtcWrite
    rtc_t rtc;

    // Llamar a la función rtcWrite que utiliza el mock
    bool_t result = rtcWrite(&rtc);

    // Verificar que la función rtcWrite devuelve verdadero
    assert_true(result);

}

Suite *check_suite() {
    Suite *s = suite_create("Check Suite sapi_rtc rtcInit");
    TCase *tc = tcase_create("Check Test Case");

    tcase_add_test(tc, test_rtcInit);
    suite_add_tcase(s, tc);

    return s;
}

Suite *cmocka_suite() {
    Suite *s = suite_create("CMocka Suite sapi_rtc rtcRead rtcWrite");
    TCase *tc = tcase_create("CMocka Test Case");

    tcase_add_test(tc, test_rtcRead);
    tcase_add_test(tc, test_rtcWrite);
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

    // Ejecutar las pruebas de CMocka
    SRunner *cmocka_runner = srunner_create(cmocka_suite());
    srunner_run_all(cmocka_runner, CK_NORMAL);
    number_failed += srunner_ntests_failed(cmocka_runner);
    srunner_free(cmocka_runner);

    // Devolver el número total de pruebas fallidas
    return number_failed;
}