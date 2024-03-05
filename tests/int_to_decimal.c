#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "s21_tests.h"
#include <limits.h>
// Тест для положительного числа
START_TEST(test_positive) {
    s21_decimal result = {0};
    int success = s21_from_int_to_decimal(15, &result);
    ck_assert_int_eq(success, 0); // Успех, если возвращается 0
    int tem = result.bits[0];
    ck_assert_int_eq(tem, 15);
    ck_assert_int_eq(result.bits[3], 0);
} END_TEST

// Тест для отрицательного числа
START_TEST(test_negative) {
    s21_decimal result = {0};
    int success = s21_from_int_to_decimal(-15, &result);
    ck_assert_int_eq(success, 0); // Успех, если возвращается 0
    ck_assert_int_eq(result.bits[0], 15); // Предполагая, что -15 хранится как 15 с установленным знаковым битом
    ck_assert(result.bits[3] & (1 << 31)); // Проверка установленного знакового бита
} END_TEST

// Тест для нуля
START_TEST(test_zero) {
    s21_decimal result = {0};
    int success = s21_from_int_to_decimal(0, &result);
    ck_assert_int_eq(result.bits[0], 0);
    ck_assert_int_eq(result.bits[3], 0);

    ck_assert_int_eq(success, 0);
} END_TEST

START_TEST(max_min) {
    s21_decimal result = {0};
    int success = s21_from_int_to_decimal(INT_MIN, &result);
    int temp = result.bits[0];
    ck_assert_int_eq(temp, INT_MIN);
    ck_assert(result.bits[3] & (1 << 31));

    ck_assert_int_eq(success, 0);
} END_TEST


// Функция для создания набора тестов
Suite *int_to_decimal(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("s21_decimal_conversion");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_positive);
    tcase_add_test(tc_core, test_negative);
    tcase_add_test(tc_core, test_zero);
    tcase_add_test(tc_core, max_min);
    suite_add_tcase(s, tc_core);

    return s;
}


