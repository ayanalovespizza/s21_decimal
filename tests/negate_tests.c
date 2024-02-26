#include "s21_tests.h"

// все нули 0 -> 1
START_TEST(negate_test1) {
  s21_decimal value1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal expected_res = {0x00000000, 0x00000000, 0x00000000, 0x80000000};

  s21_negate(value1, &result);

  ck_assert_int_eq(s21_is_equal(result, expected_res), 1);
}
END_TEST

// все нули и отрицательный знак 1 -> 0
START_TEST(negate_test2) {
  s21_decimal value1 = {0x00000000, 0x00000000, 0x00000000, 0x80000000};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal expected_res = {0x00000000, 0x00000000, 0x00000000, 0x80000000};

  s21_negate(value1, &result);

  ck_assert_int_eq(s21_is_equal(result, expected_res), 1);
}
END_TEST

// максимальное число (все единички) с отрицательным знаком 1 -> 0
START_TEST(negate_test3) {
  s21_decimal value1 = {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal expected_res = {0xffffffff, 0xffffffff, 0xffffffff, 0x7fffffff};

  s21_negate(value1, &result);

  ck_assert_int_eq(s21_is_equal(result, expected_res), 1);
}
END_TEST

// максимальное число (все единички) 0 -> 1
START_TEST(negate_test4) {
  s21_decimal value1 = {0xffffffff, 0xffffffff, 0xffffffff, 0x7fffffff};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal expected_res = {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};

  s21_negate(value1, &result);

  ck_assert_int_eq(s21_is_equal(result, expected_res), 1);
}
END_TEST

// random
START_TEST(negate_test5) {
  s21_decimal value1 = {0x10afcd01, 0x1010101a, 0xabcdef10, 0x00110000};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal expected_res = {0x10afcd01, 0x1010101a, 0xabcdef10, 0x80110000};

  s21_negate(value1, &result);

  // printf("value1: %x %x %x %x\n", value1.bits[3], value1.bits[2],
  //        value1.bits[1], value1.bits[0]);
  // printf("result: %x %x %x %x\n", result.bits[3], result.bits[2],
  //        result.bits[1], result.bits[0]);
  // printf("expected_res: %x %x %x %x\n", expected_res.bits[3],
  //        expected_res.bits[2], expected_res.bits[1], expected_res.bits[0]);

  ck_assert_int_eq(s21_is_equal(result, expected_res), 1);
}
END_TEST

Suite *negate_suite() {
  Suite *s = suite_create("\033[35mNEGATE TESTS\033[0m");

  TCase *negate_tests = tcase_create("NEGATE");
  suite_add_tcase(s, negate_tests);
  tcase_add_test(negate_tests, negate_test1);
  tcase_add_test(negate_tests, negate_test2);
  tcase_add_test(negate_tests, negate_test3);
  tcase_add_test(negate_tests, negate_test4);
  tcase_add_test(negate_tests, negate_test5);

  return s;
}