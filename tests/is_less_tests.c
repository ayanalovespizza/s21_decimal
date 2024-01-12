#include "s21_tests.h"

// все нули v1 = v2
START_TEST(is_less_test1) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);  // correct 0
  ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
}
END_TEST

// c неиспользуемыми битами в bits[3] и v1 = v2
START_TEST(is_less_test2) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x10000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);  // correct 0
  ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
}
END_TEST

// все нули, но разные знаки v1 = v2
START_TEST(is_less_test3) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};  // 0
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, MINUS};       // -0

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);  // correct 0
  ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
}
END_TEST

// все нули, но разные знаки v1 = v2
START_TEST(is_less_test4) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, MINUS};       // -0
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};  // 0

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);  // correct 0
  ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
}
END_TEST

// разница в один бит v1 < v2
START_TEST(is_less_test5) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};  // 0
  s21_decimal value_2 = {0x00000001, 0x00000000, 0x00000000, 0x00000000};  // 1

  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);  // correct 1
  ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
}
END_TEST

// разница в некоторых битах v1 > v2
START_TEST(is_less_test6) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);  // correct 0
  ck_assert_int_eq(s21_is_less(value_2, value_1), 1);
}
END_TEST

// несколько одинаковых битов v1 = v2
START_TEST(is_less_test7) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);  // correct 0
  ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
}
END_TEST

// несколько одинаковых битов, но знаки разные v1 < v2
START_TEST(is_less_test8) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, MINUS};
  s21_decimal value_2 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);  // correct 1
  ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
}
END_TEST

// два отрицательных числа, результат инверсируется
START_TEST(is_less_test9) {
  s21_decimal value_1 = {0x11111110, 0x00000000, 0x00000000, MINUS};
  s21_decimal value_2 = {0x11111111, 0x00000000, 0x00000000, MINUS};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
  ck_assert_int_eq(s21_is_less(value_2, value_1), 1);
}
END_TEST

// маленькое отрицательное число и большое отрицательное v2 < v1
START_TEST(is_less_test10) {
  s21_decimal value_1 = {0x00000000, 1, 0x00000000, MINUS};
  s21_decimal value_2 = {1, 0x00000000, 0x00000000, MINUS};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
  ck_assert_int_eq(s21_is_less(value_2, value_1), 1);
}
END_TEST

START_TEST(is_less_test11) {
  s21_decimal value_1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal value_2 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  // -1.2
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
  ck_assert_int_eq(s21_is_less(value_2, value_1), 1);
}
END_TEST

START_TEST(is_less_test12) {
  s21_decimal value_1 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal value_2 = {
      {12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
  ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
}
END_TEST

START_TEST(is_less_test13) {
  s21_decimal value_1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal value_2 = {
      {12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
  ck_assert_int_eq(s21_is_less(value_2, value_1), 1);
}
END_TEST

START_TEST(is_less_test14) {
  s21_decimal value_1 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal value_2 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //  -1.2;
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
  ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
}

START_TEST(is_less_test15) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  s21_decimal value_2 = {{12345, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
  ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
}
END_TEST

START_TEST(is_less_test16) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
  ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
}
END_TEST

Suite *is_less_suite() {
  Suite *s = suite_create("\033[35mIS LESS TESTS\033[0m");

  TCase *is_less_tests = tcase_create("IS_LESS");
  suite_add_tcase(s, is_less_tests);
  tcase_add_test(is_less_tests, is_less_test1);
  tcase_add_test(is_less_tests, is_less_test2);
  tcase_add_test(is_less_tests, is_less_test3);
  tcase_add_test(is_less_tests, is_less_test4);
  tcase_add_test(is_less_tests, is_less_test5);
  tcase_add_test(is_less_tests, is_less_test6);
  tcase_add_test(is_less_tests, is_less_test7);
  tcase_add_test(is_less_tests, is_less_test8);
  tcase_add_test(is_less_tests, is_less_test9);
  tcase_add_test(is_less_tests, is_less_test10);
  tcase_add_test(is_less_tests, is_less_test11);
  tcase_add_test(is_less_tests, is_less_test12);
  tcase_add_test(is_less_tests, is_less_test13);
  tcase_add_test(is_less_tests, is_less_test14);
  tcase_add_test(is_less_tests, is_less_test15);
  tcase_add_test(is_less_tests, is_less_test16);

  return s;
}