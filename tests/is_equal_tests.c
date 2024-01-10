#include "s21_tests.h"

// all nulls
START_TEST(is_equal_test1) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

// with not used bits in bits[3]
START_TEST(is_equal_test2) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x10000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

// all null and different signs
START_TEST(is_equal_test3) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, MINUS};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

// different one bit
START_TEST(is_equal_test4) {
  s21_decimal value_1 = {0x00000001, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

// different some bits
START_TEST(is_equal_test5) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

// some bits are equal
START_TEST(is_equal_test6) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

// some bits are equal but signs are different
START_TEST(is_equal_test7) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, MINUS};
  s21_decimal value_2 = {0x11111111, 0x00000000, 0x00000000, !(MINUS)};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

// different scales but equals bits
START_TEST(is_equal_test8) {
  s21_decimal value_1, value_2;
  value_1.bits[3] = 0b00000000000000010000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[0] = 0b00000000000000000000000000001111;

  value_2.bits[3] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[0] = 0b00000000000000000000000000001111;

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

Suite *is_equal_suite() {
  Suite *s = suite_create("\033[35mIS EQUAL TESTS\033[0m");
  TCase *is_equal_tests = tcase_create("IS_EQUAL");
  suite_add_tcase(s, is_equal_tests);
  tcase_add_test(is_equal_tests, is_equal_test1);
  tcase_add_test(is_equal_tests, is_equal_test2);
  tcase_add_test(is_equal_tests, is_equal_test3);
  tcase_add_test(is_equal_tests, is_equal_test4);
  tcase_add_test(is_equal_tests, is_equal_test5);
  tcase_add_test(is_equal_tests, is_equal_test6);
  tcase_add_test(is_equal_tests, is_equal_test7);
  tcase_add_test(is_equal_tests, is_equal_test8);

  return s;
}
