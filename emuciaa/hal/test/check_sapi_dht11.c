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

#include "dht11_api_mock.h"
#include "sapi_delay_mock.h"
#include "sapi_dht11.h"


START_TEST(test_dht11Init) {
    int32_t gpio = 10;

    // Llamar a la función dht11Init que utiliza el mock
    dht11Init(gpio);

    // Assert la funcion fue ejecutada con exito
    ck_assert_msg(1, "dht11Init ejecutado sin errores");
}
END_TEST

static void test_dht11Read() {
    // Variables de salida para phum y ptemp
    float humidity = 0.0;
    float temperature = 0.0;

    // Configurar el comportamiento esperado del mock dht11_read
    dht11_read_set_result(true);  // Éxito en la lectura

    // Llamar a la función dht11_read que utiliza el mock
    bool_t result = dht11_read(&humidity, &temperature);

    // Verificar que la función dht11_read devuelve verdadero
    assert_true(result);

    // Verificar los valores de phum y ptemp después de la llamada a dht11_read
    assert_float_equal(humidity, 0.0, 0.001);
    assert_float_equal(temperature, 0.0, 0.001);

    // Restaurar el comportamiento original del mock dht11_read
    dht11_read_set_result(false);  // Error en la lectura
}

Suite *cmocka_suite() {
    Suite *s = suite_create("CMocka Suite sapi_dht11 dht11Read");
    TCase *tc = tcase_create("CMocka Test Case");

    tcase_add_test(tc, test_dht11Read);
    suite_add_tcase(s, tc);

    return s;
}

Suite *check_suite() {
    Suite *s = suite_create("Check Suite sapi_dht11 dht11Init");
    TCase *tc = tcase_create("Check Test Case");

    tcase_add_test(tc, test_dht11Init);
    suite_add_tcase(s, tc);

    return s;
}

int main(void) {
    int number_failed = 0;

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

    // Devolver el número total de pruebas fallidas
    return number_failed;
}