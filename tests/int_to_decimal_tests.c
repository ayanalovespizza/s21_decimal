
#include <limits.h>

#include "s21_tests.h"
// Тест для положительного числа
START_TEST(test_positive) {
  s21_decimal result = {0};
  int success = s21_from_int_to_decimal(15, &result);
  ck_assert_int_eq(success, 0);  // Успех, если возвращается 0
  int tem = result.bits[0];
  ck_assert_int_eq(tem, 15);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

// Тест для отрицательного числа
START_TEST(test_negative) {
  s21_decimal result = {0};
  int success = s21_from_int_to_decimal(-15, &result);
  ck_assert_int_eq(success, 0);  // Успех, если возвращается 0
  ck_assert_int_eq(result.bits[0], 15);  // Предполагая, что -15 хранится как 15
                                         // с установленным знаковым битом
  ck_assert(result.bits[3] &
            (1 << 31));  // Проверка установленного знакового бита
}
END_TEST

// Тест для нуля
START_TEST(test_zero) {
  s21_decimal result = {0};
  int success = s21_from_int_to_decimal(0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);

  ck_assert_int_eq(success, 0);
}
END_TEST

START_TEST(max_min) {
  s21_decimal result = {0};
  int success = s21_from_int_to_decimal(INT_MIN, &result);
  int temp = result.bits[0];
  ck_assert_int_eq(temp, INT_MIN);
  ck_assert(result.bits[3] & (1 << 31));

  ck_assert_int_eq(success, 0);
}
END_TEST

void tests_from_int_to_decimal(int number, s21_decimal decimal_check) {
  s21_decimal result = {0};
  int code = s21_from_int_to_decimal(number, &result);
  int sign_check = (decimal_check.bits[3] & MINUS) ? -1 : 1;
  int sign_result = (result.bits[3] & MINUS) ? -1 : 1;
  ;
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
  //    ck_assert_int_eq(result.bits[0], decimal_check.bits[0]);
  ck_assert_int_eq(sign_check, sign_result);
}

///

START_TEST(tests_from_int_to_decimal_fail) {
  int number = -2147483648;
  int result = s21_from_int_to_decimal(number, NULL);

  ck_assert_int_eq(result, 1);
}
END_TEST

///

START_TEST(tests_from_int_to_decimal_ok1) {
  int number = -2147483648;
  // Converted the Int32 value -2147483648 to the Decimal value -2147483648.
  s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80000000}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok2) {
  int number = -2147483647;
  // Converted the Int32 value -2147483647 to the Decimal value -2147483647.
  s21_decimal decimal_check = {{0x7FFFFFFF, 0x0, 0x0, 0x80000000}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok3) {
  int number = -214748364;
  // Converted the Int32 value -214748364 to the Decimal value -214748364.
  s21_decimal decimal_check = {{0xCCCCCCC, 0x0, 0x0, 0x80000000}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok4) {
  int number = -214748;
  // Converted the Int32 value -214748 to the Decimal value -214748.
  s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x80000000}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok5) {
  int number = -1000;
  // Converted the Int32 value -1000 to the Decimal value -1000.
  s21_decimal decimal_check = {{0x3E8, 0x0, 0x0, 0x80000000}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok6) {
  int number = -1;
  // Converted the Int32 value -1 to the Decimal value -1.
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok7) {
  int number = 0;
  // Converted the Int32 value 0 to the Decimal value 0.
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok8) {
  int number = 1;
  // Converted the Int32 value 1 to the Decimal value 1.
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok9) {
  int number = 1000;
  // Converted the Int32 value 1000 to the Decimal value 1000.
  s21_decimal decimal_check = {{0x3E8, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok10) {
  int number = 214748;
  // Converted the Int32 value 214748 to the Decimal value 214748.
  s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok11) {
  int number = 214748364;
  // Converted the Int32 value 214748364 to the Decimal value 214748364.
  s21_decimal decimal_check = {{0xCCCCCCC, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok12) {
  int number = 2147483646;
  // Converted the Int32 value 2147483646 to the Decimal value 2147483646.
  s21_decimal decimal_check = {{0x7FFFFFFE, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok13) {
  int number = 2147483647;
  // Converted the Int32 value 2147483647 to the Decimal value 2147483647.
  s21_decimal decimal_check = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

Suite *int_to_decimal_suite() {
  Suite *s = suite_create("\033[35mFROM INT TO DECIMAL TESTS\033[0m");
  TCase *tc = tcase_create("case_from_int_to_decimal");

  tcase_add_test(tc, tests_from_int_to_decimal_fail);

  tcase_add_test(tc, tests_from_int_to_decimal_ok1);
  tcase_add_test(tc, tests_from_int_to_decimal_ok2);
  tcase_add_test(tc, tests_from_int_to_decimal_ok3);
  tcase_add_test(tc, tests_from_int_to_decimal_ok4);
  tcase_add_test(tc, tests_from_int_to_decimal_ok5);
  tcase_add_test(tc, tests_from_int_to_decimal_ok6);
  tcase_add_test(tc, tests_from_int_to_decimal_ok7);
  tcase_add_test(tc, tests_from_int_to_decimal_ok8);
  tcase_add_test(tc, tests_from_int_to_decimal_ok9);
  tcase_add_test(tc, tests_from_int_to_decimal_ok10);
  tcase_add_test(tc, tests_from_int_to_decimal_ok11);
  tcase_add_test(tc, tests_from_int_to_decimal_ok12);
  tcase_add_test(tc, tests_from_int_to_decimal_ok13);

  tcase_add_test(tc, test_positive);
  tcase_add_test(tc, test_negative);
  tcase_add_test(tc, test_zero);
  tcase_add_test(tc, max_min);
  suite_add_tcase(s, tc);

  suite_add_tcase(s, tc);
  return s;
}