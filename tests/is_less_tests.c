#include "s21_tests.h"

// all nulls v1 = v2
START_TEST(is_less_test1) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

// with not used bits in bits[3] v1 = v2
START_TEST(is_less_test2) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x10000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

// all null and different signs v1 = v2
START_TEST(is_less_test3) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, MINUS};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

// all null and different signs v1 = v2
START_TEST(is_less_test4) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, MINUS};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

// one bit difference v1 < v2
START_TEST(is_less_test5) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000001, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

// some bits difference v1 > v2
START_TEST(is_less_test6) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

// some bits equal v1 = v2
START_TEST(is_less_test7) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

// some bits equal but different signs v1 < v2
START_TEST(is_less_test8) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, MINUS};
  s21_decimal value_2 = {0x11111111, 0x00000000, 0x00000000, !(MINUS)};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

// two "-" signs, result inversed
START_TEST(is_less_test9) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, MINUS};
  s21_decimal value_2 = {0x00000000, 0x11111111, 0x00000000, MINUS};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);  // по сути должно быть 0
}
END_TEST

START_TEST(is_less_test10) {
  s21_decimal value_1 = {0x00000000, 0x11111111, 0x00000000, MINUS};
  s21_decimal value_2 = {0x11111111, 0x00000000, 0x00000000, MINUS};

  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);  // по сути должно быть 1
}
END_TEST

START_TEST(is_less_test11) {
  s21_decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}};  // -1.2
  ck_assert_int_eq(s21_is_less(dec5, dec6), 0);
  ck_assert_int_eq(s21_is_less(dec6, dec5), 1);
}
END_TEST

START_TEST(is_less_test12) {
  s21_decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(s21_is_less(dec7, dec8), 1);
  ck_assert_int_eq(s21_is_less(dec8, dec7), 0);
}
END_TEST

START_TEST(is_less_test13) {
  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(s21_is_less(dec1, dec2), 0);
  ck_assert_int_eq(s21_is_less(dec2, dec1), 1);
}
END_TEST

START_TEST(is_less_test14) {
  s21_decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal dec4 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //  -1.2;
  ck_assert_int_eq(s21_is_less(dec3, dec4), 1);
  ck_assert_int_eq(s21_is_less(dec4, dec3), 0);
}

START_TEST(is_less_test15) {
  s21_decimal dec9 = {{12345, 0, 0, 0}};
  s21_decimal dec10 = {{12345, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(dec9, dec10), 0);
  ck_assert_int_eq(s21_is_less(dec10, dec9), 0);
}
END_TEST

START_TEST(is_less_test16) {
  s21_decimal dec11 = {{0, 0, 0, 0}};
  s21_decimal dec12 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(dec11, dec12), 0);
  ck_assert_int_eq(s21_is_less(dec12, dec11), 0);
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