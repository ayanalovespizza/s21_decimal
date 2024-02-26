#include "s21_tests.h"

// все нули
START_TEST(is_equal_test1) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);  // correct 1
}
END_TEST

// с неиспользуемыми битами
START_TEST(is_equal_test2) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x10000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);  // correct 1
}
END_TEST

// все нули, но разные знаки (+0 и -0)
START_TEST(is_equal_test3) {
  s21_decimal value_1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, MINUS};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);  // correct 1
}
END_TEST

// отличается один бит
START_TEST(is_equal_test4) {
  s21_decimal value_1 = {0x00000001, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);  // correct 0
}
END_TEST

// отличаются несколько бит
START_TEST(is_equal_test5) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);  // correct 0
}
END_TEST

// несколько битов равны
START_TEST(is_equal_test6) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal value_2 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);  // correct 1
}
END_TEST

// несколько битов равны, но знаки разные
START_TEST(is_equal_test7) {
  s21_decimal value_1 = {0x11111111, 0x00000000, 0x00000000, MINUS};
  s21_decimal value_2 = {0x11111111, 0x00000000, 0x00000000, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);  // correct 0
}
END_TEST

// максимальное целое число
START_TEST(is_equal_test8) {
  s21_decimal value_1 = {0x11111111, 0x11111111, 0x11111111, 0x00000000};
  s21_decimal value_2 = {0x11111111, 0x11111111, 0x11111111, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);  // correct 1
}
END_TEST

// максимальное целое число и max -1
START_TEST(is_equal_test9) {
  s21_decimal value_1 = {0x11111110, 0x11111111, 0x11111111, 0x00000000};
  s21_decimal value_2 = {0x11111111, 0x11111111, 0x11111111, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);  // correct 0
}
END_TEST

// максимальные целые, но у первого степень -1
START_TEST(is_equal_test10) {
  s21_decimal value_1 = {0x11111111, 0x11111111, 0x11111111, 0x00010000};
  s21_decimal value_2 = {0x11111111, 0x11111111, 0x11111111, 0x00000000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);  // correct 0
}
END_TEST

// разные степени, но биты одинаковые
START_TEST(is_equal_test11) {
  s21_decimal value_1, value_2;  // v1 = 1,5 v2 = 15
  value_1.bits[3] = 0b00000000000000010000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[0] = 0b00000000000000000000000000001111;

  value_2.bits[3] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[0] = 0b00000000000000000000000000001111;

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);  // correct 0
}
END_TEST

// some random shit 1
START_TEST(is_equal_test12) {
  s21_decimal value_1, value_2;
  value_1.bits[3] = 0b10000000000000000000000000000000;
  value_1.bits[2] = 0b11111100001011001011101100101010;
  value_1.bits[1] = 0b10101110101000101010101101001011;
  value_1.bits[0] = 0b10101010100011111010101110101110;

  value_2.bits[3] = 0b10000000000000000000000000000000;
  value_2.bits[2] = 0b11111100001011001011101100101010;
  value_2.bits[1] = 0b10101110101000101010101101001011;
  value_2.bits[0] = 0b10101010100011111010101110101110;

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);  // correct 1
}
END_TEST

// some random shit 2
START_TEST(is_equal_test13) {
  s21_decimal value_1 = {0x01010100, 0x10011010, 0x10101010, 0x001a0000};
  s21_decimal value_2 = {0x10101010, 0x11010101, 0x11110001, 0x001f0000};

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);  // correct 0
}
END_TEST

// еще раз с неиспользуемыми битами
START_TEST(is_equal_test14) {
  s21_decimal value_1, value_2;
  value_1.bits[3] = 0b01010101000000000000000000000000;
  value_1.bits[2] = 0b11111100001011001011101100101010;
  value_1.bits[1] = 0b10101110101000101010101101001011;
  value_1.bits[0] = 0b10101010100011111010101110101110;

  value_2.bits[3] = 0b00101010000000000000000000000000;
  value_2.bits[2] = 0b11111100001011001011101100101010;
  value_2.bits[1] = 0b10101110101000101010101101001011;
  value_2.bits[0] = 0b10101010100011111010101110101110;

  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);  // correct 1
}
END_TEST

Suite *is_equal_suite() {
  Suite *s = suite_create("\033[35m== IS EQUAL TESTS\033[0m");
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
  tcase_add_test(is_equal_tests, is_equal_test9);
  tcase_add_test(is_equal_tests, is_equal_test10);
  tcase_add_test(is_equal_tests, is_equal_test11);
  tcase_add_test(is_equal_tests, is_equal_test12);
  tcase_add_test(is_equal_tests, is_equal_test13);
  tcase_add_test(is_equal_tests, is_equal_test14);

  return s;
}
