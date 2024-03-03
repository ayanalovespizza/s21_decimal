#include "s21_tests.h"

void tests_round(s21_decimal decimal, s21_decimal decimal_check) {
  s21_decimal result;

  int code = s21_round(decimal, &result);
  // int sign_check = s21_get_sign(decimal_check);
  // int sign_result = s21_get_sign(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
  // ck_assert_int_eq(sign_check, sign_result);
}

START_TEST(round_test1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395034
  s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395034
  s21_decimal decimal_check = {
      {0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test5) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // 792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test6) {
  // -792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  // -792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test7) {
  // 79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
  // 79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test8) {
  // -79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
  // -79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test9) {
  // 7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
  // 7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test10) {
  // -7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
  // -7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test11) {
  // 79228162514264337593543.950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
  // 79228162514264337593544
  s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test12) {
  // -79228162514264337593543.950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
  // -79228162514264337593544
  s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test13) {
  // 79228162514264337593.543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
  // 79228162514264337594
  s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test14) {
  // -79228162514264337593.543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
  // -79228162514264337594
  s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test15) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 8
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test16) {
  // -7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -8
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test17) {
  // 5.2818775009509558395695966890
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
  // 5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test18) {
  // -5.2818775009509558395695966890
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
  // -5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test19) {
  // 1.8446744069414584320
  s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x130000}};
  // 2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test20) {
  // -1.8446744069414584320
  s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80130000}};
  // -2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test21) {
  // 4294967295
  s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};
  // 4294967295
  s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test22) {
  // -4294967295
  s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};
  // -4294967295
  s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test23) {
  // 429496729.5
  s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};
  // 429496730
  s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test24) {
  // -429496729.5
  s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80010000}};
  // -429496730
  s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test25) {
  // 42949672.95
  s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x20000}};
  // 42949673
  s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test26) {
  // -42949672.95
  s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80020000}};
  // -42949673
  s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test27) {
  // 1.0
  s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test28) {
  // -1.0
  s21_decimal decimal = {{0xA, 0x0, 0x0, 0x80010000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test29) {
  // 1.00
  s21_decimal decimal = {{0x64, 0x0, 0x0, 0x20000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test30) {
  // -1.00
  s21_decimal decimal = {{0x64, 0x0, 0x0, 0x80020000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test31) {
  // 1.0000000000000000000000000000
  s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test32) {
  // -1.0000000000000000000000000000
  s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test33) {
  // 1.1
  s21_decimal decimal = {{0xB, 0x0, 0x0, 0x10000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test34) {
  // -1.1
  s21_decimal decimal = {{0xB, 0x0, 0x0, 0x80010000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test35) {
  // 9.9
  s21_decimal decimal = {{0x63, 0x0, 0x0, 0x10000}};
  // 10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test36) {
  // -9.9
  s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80010000}};
  // -10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test37) {
  // 99.99
  s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x20000}};
  // 100
  s21_decimal decimal_check = {{0x64, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test38) {
  // -99.99
  s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80020000}};
  // -100
  s21_decimal decimal_check = {{0x64, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test39) {
  // 0.99
  s21_decimal decimal = {{0x63, 0x0, 0x0, 0x20000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test40) {
  // -0.99
  s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80020000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test41) {
  // -0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test42) {
  // 0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test43) {
  // -0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test44) {
  // 0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test45) {
  // 0.5
  s21_decimal decimal = {{0x5, 0x0, 0x0, 0x10000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test46) {
  // -0.5
  s21_decimal decimal = {{0x5, 0x0, 0x0, 0x80010000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test47) {
  // 0.49
  s21_decimal decimal = {{0x31, 0x0, 0x0, 0x20000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test48) {
  // -0.49
  s21_decimal decimal = {{0x31, 0x0, 0x0, 0x80020000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test49) {
  // 0.51
  s21_decimal decimal = {{0x33, 0x0, 0x0, 0x20000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test50) {
  // -0.51
  s21_decimal decimal = {{0x33, 0x0, 0x0, 0x80020000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test51) {
  // 0.4999999999999999999999999999
  s21_decimal decimal = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test52) {
  // -0.4999999999999999999999999999
  s21_decimal decimal = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test53) {
  // 0.5000000000000000000000000001
  s21_decimal decimal = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test54) {
  // -0.5000000000000000000000000001
  s21_decimal decimal = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test55) {
  // 0.5000000000000000000000000000
  s21_decimal decimal = {{0x88000000, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(round_test56) {
  // -0.5000000000000000000000000000
  s21_decimal decimal = {{0x88000000, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_fail1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_round(decimal, NULL);

  ck_assert_int_eq(code, 1);
}

START_TEST(tests_round_fail2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_round_fail3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_round_fail4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_round_fail5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_round_fail6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_round_fail7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_round_fail8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_round_fail9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *round_suite() {
  Suite *s = suite_create("\033[35mROUND TESTS\033[0m");
  TCase *round_tests = tcase_create("ROUND");
  suite_add_tcase(s, round_tests);
  tcase_add_test(round_tests, round_test1);
  tcase_add_test(round_tests, round_test2);
  tcase_add_test(round_tests, round_test3);
  tcase_add_test(round_tests, round_test4);
  tcase_add_test(round_tests, round_test5);
  tcase_add_test(round_tests, round_test6);
  tcase_add_test(round_tests, round_test7);
  tcase_add_test(round_tests, round_test8);
  tcase_add_test(round_tests, round_test9);
  tcase_add_test(round_tests, round_test10);
  tcase_add_test(round_tests, round_test11);
  tcase_add_test(round_tests, round_test12);
  tcase_add_test(round_tests, round_test13);
  tcase_add_test(round_tests, round_test14);
  tcase_add_test(round_tests, round_test15);
  tcase_add_test(round_tests, round_test16);
  tcase_add_test(round_tests, round_test17);
  tcase_add_test(round_tests, round_test18);
  tcase_add_test(round_tests, round_test19);
  tcase_add_test(round_tests, round_test20);
  tcase_add_test(round_tests, round_test21);
  tcase_add_test(round_tests, round_test22);
  tcase_add_test(round_tests, round_test23);
  tcase_add_test(round_tests, round_test24);
  tcase_add_test(round_tests, round_test25);
  tcase_add_test(round_tests, round_test26);
  tcase_add_test(round_tests, round_test27);
  tcase_add_test(round_tests, round_test28);
  tcase_add_test(round_tests, round_test29);
  tcase_add_test(round_tests, round_test30);
  tcase_add_test(round_tests, round_test31);
  tcase_add_test(round_tests, round_test32);
  tcase_add_test(round_tests, round_test33);
  tcase_add_test(round_tests, round_test34);
  tcase_add_test(round_tests, round_test35);
  tcase_add_test(round_tests, round_test36);
  tcase_add_test(round_tests, round_test37);
  tcase_add_test(round_tests, round_test38);
  tcase_add_test(round_tests, round_test39);
  tcase_add_test(round_tests, round_test40);
  tcase_add_test(round_tests, round_test41);
  tcase_add_test(round_tests, round_test42);
  tcase_add_test(round_tests, round_test43);
  tcase_add_test(round_tests, round_test44);
  tcase_add_test(round_tests, round_test45);
  tcase_add_test(round_tests, round_test46);
  tcase_add_test(round_tests, round_test47);
  tcase_add_test(round_tests, round_test48);
  tcase_add_test(round_tests, round_test49);
  tcase_add_test(round_tests, round_test50);
  tcase_add_test(round_tests, round_test51);
  tcase_add_test(round_tests, round_test52);
  tcase_add_test(round_tests, round_test53);
  tcase_add_test(round_tests, round_test54);
  tcase_add_test(round_tests, round_test55);
  tcase_add_test(round_tests, round_test56);

  tcase_add_test(round_tests, tests_round_fail1);
  tcase_add_test(round_tests, tests_round_fail2);
  tcase_add_test(round_tests, tests_round_fail3);
  tcase_add_test(round_tests, tests_round_fail4);
  tcase_add_test(round_tests, tests_round_fail5);
  tcase_add_test(round_tests, tests_round_fail6);
  tcase_add_test(round_tests, tests_round_fail7);
  tcase_add_test(round_tests, tests_round_fail8);
  tcase_add_test(round_tests, tests_round_fail9);

  return s;
}
