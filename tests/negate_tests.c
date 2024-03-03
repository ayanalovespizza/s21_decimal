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
  s21_decimal value1 = {0xffffffff, 0xffffffff, 0xffffffff, 0x80000000};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal expected_res = {0xffffffff, 0xffffffff, 0xffffffff, 0x00000000};

  s21_negate(value1, &result);

  ck_assert_int_eq(s21_is_equal(result, expected_res), 1);
}
END_TEST

// максимальное число (все единички) 0 -> 1
START_TEST(negate_test4) {
  s21_decimal value1 = {0xffffffff, 0xffffffff, 0xffffffff, 0x00000000};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal expected_res = {0xffffffff, 0xffffffff, 0xffffffff, 0x80000000};

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

START_TEST(negate_test6) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test7) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test8) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // -7922816251426433759354395033.5
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test9) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // 7922816251426433759354395033.5
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test10) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // -792281625142643375935439503.35
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test11) {
  // -792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // 792281625142643375935439503.35
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test12) {
  // 79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // -79228162514264337593543950.335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test13) {
  // -79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // 79228162514264337593543950.335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test14) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // -7.9228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test15) {
  // -7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // 7.9228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test16) {
  // 52818775009509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // -52818775009509558392832655360
  s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test17) {
  // -52818775009509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // 52818775009509558392832655360
  s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test18) {
  // 52818774997211729016086244010
  s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // -52818774997211729016086244010
  s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test19) {
  // -52818774997211729016086244010
  s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // 52818774997211729016086244010
  s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test20) {
  // 52818774997211729013222932480
  s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // -52818774997211729013222932480
  s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test21) {
  // -52818774997211729013222932480
  s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // 52818774997211729013222932480
  s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test22) {
  // 1229782938247303441.0
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x10000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // -1229782938247303441.0
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80010000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test23) {
  // -1229782938247303441.0
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80010000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // 1229782938247303441.0
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x10000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test24) {
  // 1844674407800451891.3
  s21_decimal decimal = {{0x1, 0x1, 0x1, 0x10000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // -1844674407800451891.3
  s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x80010000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(negate_test25) {
  // -1844674407800451891.3
  s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80010000}};
  s21_decimal result = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  // 1844674407800451891.3
  s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x10000}};

  s21_negate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(fail_negate_test1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_negate(decimal, NULL);

  ck_assert_int_eq(code, 1);
}

START_TEST(fail_negate_test2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(fail_negate_test3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(fail_negate_test4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(fail_negate_test5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(fail_negate_test6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(fail_negate_test7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(fail_negate_test8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(fail_negate_test9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
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
  tcase_add_test(negate_tests, negate_test6);
  tcase_add_test(negate_tests, negate_test7);
  tcase_add_test(negate_tests, negate_test8);
  tcase_add_test(negate_tests, negate_test9);
  tcase_add_test(negate_tests, negate_test10);
  tcase_add_test(negate_tests, negate_test11);
  tcase_add_test(negate_tests, negate_test12);
  tcase_add_test(negate_tests, negate_test13);
  tcase_add_test(negate_tests, negate_test14);
  tcase_add_test(negate_tests, negate_test15);
  tcase_add_test(negate_tests, negate_test16);
  tcase_add_test(negate_tests, negate_test17);
  tcase_add_test(negate_tests, negate_test18);
  tcase_add_test(negate_tests, negate_test19);
  tcase_add_test(negate_tests, negate_test20);
  tcase_add_test(negate_tests, negate_test21);
  tcase_add_test(negate_tests, negate_test22);
  tcase_add_test(negate_tests, negate_test23);
  tcase_add_test(negate_tests, negate_test24);
  tcase_add_test(negate_tests, negate_test25);

  tcase_add_test(negate_tests, fail_negate_test1);
  tcase_add_test(negate_tests, fail_negate_test2);
  tcase_add_test(negate_tests, fail_negate_test3);
  tcase_add_test(negate_tests, fail_negate_test4);
  tcase_add_test(negate_tests, fail_negate_test5);
  tcase_add_test(negate_tests, fail_negate_test6);
  tcase_add_test(negate_tests, fail_negate_test7);
  tcase_add_test(negate_tests, fail_negate_test8);
  tcase_add_test(negate_tests, fail_negate_test9);

  return s;
}