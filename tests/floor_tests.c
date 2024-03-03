#include "s21_tests.h"

void testing_floor(s21_decimal decimal, s21_decimal decimal_check) {
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(floor_test1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033
  s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395034
  s21_decimal decimal_check = {
      {0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test5) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // 792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test6) {
  // -792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  // -792281625142643375935439504
  s21_decimal decimal_check = {{0x28F5C290, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test7) {
  // 79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
  // 79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test8) {
  // -79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
  // -79228162514264337593543951
  s21_decimal decimal_check = {{0x9DB22D0F, 0x4BC6A7EF, 0x418937, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test9) {
  // 7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
  // 7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test10) {
  // -7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
  // -7922816251426433759354396
  s21_decimal decimal_check = {{0x295E9E1C, 0xBAC710CB, 0x68DB8, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test11) {
  // 79228162514264337593543.950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
  // 79228162514264337593543
  s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test12) {
  // -79228162514264337593543.950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
  // -79228162514264337593544
  s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test13) {
  // 5.2818774997211729016086244010
  s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x1C0000}};
  // 5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test14) {
  // -5.2818774997211729016086244010
  s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x801C0000}};
  // -6
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test15) {
  // 1.2297829382473034410
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test16) {
  // -1.2297829382473034410
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};
  // -2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test17) {
  // 4294967.296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x30000}};
  // 4294967
  s21_decimal decimal_check = {{0x418937, 0x0, 0x0, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test18) {
  // -4294967.296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80030000}};
  // -4294968
  s21_decimal decimal_check = {{0x418938, 0x0, 0x0, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test19) {
  // 4.294967296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x90000}};
  // 4
  s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test20) {
  // -4.294967296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80090000}};
  // -5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test21) {
  // 1.00
  s21_decimal decimal = {{0x64, 0x0, 0x0, 0x20000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test22) {
  // -1.00
  s21_decimal decimal = {{0x64, 0x0, 0x0, 0x80020000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test23) {
  // 1.0000000000
  s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0xA0000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test24) {
  // -1.0000000000
  s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0x800A0000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test25) {
  // 9.9
  s21_decimal decimal = {{0x63, 0x0, 0x0, 0x10000}};
  // 9
  s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test26) {
  // -9.9
  s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80010000}};
  // -10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test27) {
  // -0.99999
  s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x80050000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test28) {
  // 0.999999
  s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x60000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test29) {
  // -0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test30) {
  // 0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test31) {
  // -0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test32) {
  // 0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test33) {
  // 0.9999999999999999999999999999
  s21_decimal decimal = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  testing_floor(decimal, decimal_check);
}

START_TEST(floor_test34) {
  // -0.9999999999999999999999999999
  s21_decimal decimal = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  testing_floor(decimal, decimal_check);
}

START_TEST(tests_floor_fail1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_floor(decimal, NULL);

  ck_assert_int_eq(code, 1);
}

START_TEST(tests_floor_fail2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_floor_fail3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_floor_fail4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_floor_fail5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_floor_fail6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_floor_fail7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_floor_fail8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(tests_floor_fail9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *floor_suite() {
  Suite *s = suite_create("\033[35mFLOOR TESTS\033[0m");
  TCase *floor_tests = tcase_create("FLOOR");
  suite_add_tcase(s, floor_tests);
  tcase_add_test(floor_tests, floor_test1);
  tcase_add_test(floor_tests, floor_test2);
  tcase_add_test(floor_tests, floor_test3);
  tcase_add_test(floor_tests, floor_test4);
  tcase_add_test(floor_tests, floor_test5);
  tcase_add_test(floor_tests, floor_test6);
  tcase_add_test(floor_tests, floor_test7);
  tcase_add_test(floor_tests, floor_test8);
  tcase_add_test(floor_tests, floor_test9);
  tcase_add_test(floor_tests, floor_test10);
  tcase_add_test(floor_tests, floor_test11);
  tcase_add_test(floor_tests, floor_test12);
  tcase_add_test(floor_tests, floor_test13);
  tcase_add_test(floor_tests, floor_test14);
  tcase_add_test(floor_tests, floor_test15);
  tcase_add_test(floor_tests, floor_test16);
  tcase_add_test(floor_tests, floor_test17);
  tcase_add_test(floor_tests, floor_test18);
  tcase_add_test(floor_tests, floor_test19);
  tcase_add_test(floor_tests, floor_test20);
  tcase_add_test(floor_tests, floor_test21);
  tcase_add_test(floor_tests, floor_test22);
  tcase_add_test(floor_tests, floor_test23);
  tcase_add_test(floor_tests, floor_test24);
  tcase_add_test(floor_tests, floor_test25);
  tcase_add_test(floor_tests, floor_test26);
  tcase_add_test(floor_tests, floor_test27);
  tcase_add_test(floor_tests, floor_test28);
  tcase_add_test(floor_tests, floor_test29);
  tcase_add_test(floor_tests, floor_test30);
  tcase_add_test(floor_tests, floor_test31);
  tcase_add_test(floor_tests, floor_test32);
  tcase_add_test(floor_tests, floor_test33);
  tcase_add_test(floor_tests, floor_test34);

  tcase_add_test(floor_tests, tests_floor_fail1);
  tcase_add_test(floor_tests, tests_floor_fail2);
  tcase_add_test(floor_tests, tests_floor_fail3);
  tcase_add_test(floor_tests, tests_floor_fail4);
  tcase_add_test(floor_tests, tests_floor_fail5);
  tcase_add_test(floor_tests, tests_floor_fail6);
  tcase_add_test(floor_tests, tests_floor_fail7);
  tcase_add_test(floor_tests, tests_floor_fail8);
  tcase_add_test(floor_tests, tests_floor_fail9);

  return s;
}