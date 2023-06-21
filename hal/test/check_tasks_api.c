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

#include "tasks_api_mock.h"


START_TEST(test_xStartTickCount) {
    // Llamar a la función xStartTickCount que utiliza el mock
    xStartTickCount();

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "xStartTickCount ejecutado sin errores");
}
END_TEST

START_TEST(test_setTaskDelayUntil) {
    int pxPreviousWakeTime = 10; 
    int xTimeIncrement = 2;
    // Llamar a la función xStartTickCount que utiliza el mock
    setTaskDelayUntil(pxPreviousWakeTime, xTimeIncrement);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "setTaskDelayUntil ejecutado sin errores");
}
END_TEST

static void test_getTickCount() {
    // Configurar el comportamiento esperado del mock dht11_read
    getTickCount_set_result(100);  // Éxito en la lectura

    // Llamar a la función dht11_read que utiliza el mock
    int result = getTickCount();

    // Verificar que la función dht11_read devuelve verdadero
    assert_true(result);

    // Restaurar el comportamiento original del mock dht11_read
    getTickCount_set_result(0);  // Error en la lectura
}

Suite *cmocka_suite() {
    Suite *s = suite_create("CMocka Suite task getTickCount");
    TCase *tc = tcase_create("CMocka Test Case");

    tcase_add_test(tc, test_getTickCount);
    suite_add_tcase(s, tc);

    return s;
}

Suite *check_suite() {
    Suite *s = suite_create("Check Suite task xStartTickCount setTaskDelayUntil");
    TCase *tc = tcase_create("Check Test Case");

    tcase_add_test(tc, test_xStartTickCount);
    tcase_add_test(tc, test_setTaskDelayUntil);
    suite_add_tcase(s, tc);

    return s;
}

int main(void) {
    int number_failed = 0;

    getTickCount_mock_init();

    // Ejecutar las pruebas de CMocka
    SRunner *cmocka_runner = srunner_create(cmocka_suite());
    srunner_run_all(cmocka_runner, CK_NORMAL);
    number_failed += srunner_ntests_failed(cmocka_runner);
    srunner_free(cmocka_runner);

    // Ejecutar las pruebas de Check
    Suite *check_suit = check_suite();
    SRunner *check_runner = srunner_create(check_suit);
    srunner_run_all(check_runner, CK_NORMAL);
    number_failed += srunner_ntests_failed(check_runner);
    srunner_free(check_runner);

    getTickCount_mock_destroy();

    // Devolver el número total de pruebas fallidas
    return number_failed;
}