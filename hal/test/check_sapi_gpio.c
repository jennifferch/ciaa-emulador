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

#include "gpio_api_mock.h"
#include "sapi_interrupt_mock.h"
#include "sapi_gpio.h"

// Definir la prueba unitaria para la función gpioInit
START_TEST(test_gpioInit) {
    gpioInit_t config = GPIO_INPUT;
    gpioMap_t pin = LED1;

    // Llamar a la función gpioInit que utiliza el mock
    bool_t result = gpioInit(pin, config);
    assert_true(result);
}
END_TEST

static void test_gpioRead() {
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

static void test_gpioWrite() {
    // Variable de entrada para la funcion gpioRead
    gpioMap_t pin = LED1;
    bool_t value = ON;

    // Llamar a la función gpioWrite que utiliza el mock
    bool_t result = gpioWrite(pin, ON);

    // Verificar que la función gpio_read devuelve verdadero
    assert_true(result);

}

static void test_gpioToggle() {
    // Variable de entrada para la funcion gpioRead
    gpioMap_t pin = LED1;

    // Llamar a la función gpioWrite que utiliza el mock
    bool_t result = gpioToggle(pin);

    // Verificar que la función gpio_read devuelve verdadero
    assert_true(result);

}

Suite *check_suite() {
    Suite *s = suite_create("Check Suite sapi_gpio gpioInit");
    TCase *tc = tcase_create("Check Test Case");

    tcase_add_test(tc, test_gpioInit);
    suite_add_tcase(s, tc);

    return s;
}

Suite *cmocka_suite() {
    Suite *s = suite_create("CMocka Suite sapi_gpio gpioRead, gpioWrite, gpioToggle");
    TCase *tc = tcase_create("CMocka Test Case");

    tcase_add_test(tc, test_gpioRead);
    tcase_add_test(tc, test_gpioWrite);
     tcase_add_test(tc, test_gpioToggle);
    suite_add_tcase(s, tc);

    return s;
}

int main(void) {
    int number_failed = 0;
    
    // Inicializar el mock
    gpio_api_mock_init();
    interrupt_api_mock_init();

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
    gpio_api_mock_destroy();
    interrupt_api_mock_destroy();
    // Devolver el número total de pruebas fallidas
    return number_failed;
}