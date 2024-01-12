#include "s21_tests.h"

// all nulls
START_TEST(is_not_equal_test1) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

// with not used bits in bits[3]
START_TEST(is_not_equal_test2) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x10000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

// all nulls and different signs
START_TEST(is_not_equal_test3) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, MINUS};

  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

// one bit difference
START_TEST(is_not_equal_test4) {
  s21_decimal value_1 = {0x00000001, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
}
END_TEST

// some bits difference
START_TEST(is_not_equal_test5) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
}
END_TEST

// some bits equal
START_TEST(is_not_equal_test6) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

// some bits equal but difference signs
START_TEST(is_not_equal_test7) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, MINUS};
  s21_decimal value_2 = {0x11111111, 0x00000000, 0x00000000, !(MINUS)};

  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
}
END_TEST

Suite *is_not_equal_suite() {
  Suite *s = suite_create("\033[35m!= IS NOT EQUAL TESTS\033[0m");

  TCase *is_not_equal_tests = tcase_create("IS_NOT_EQUAL");
  suite_add_tcase(s, is_not_equal_tests);
  tcase_add_test(is_not_equal_tests, is_not_equal_test1);
  tcase_add_test(is_not_equal_tests, is_not_equal_test2);
  tcase_add_test(is_not_equal_tests, is_not_equal_test3);
  tcase_add_test(is_not_equal_tests, is_not_equal_test4);
  tcase_add_test(is_not_equal_tests, is_not_equal_test5);
  tcase_add_test(is_not_equal_tests, is_not_equal_test6);
  tcase_add_test(is_not_equal_tests, is_not_equal_test7);

  return s;
}