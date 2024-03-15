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

  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
  ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
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

START_TEST(is_less_test17) {
  // 79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // 79228162514264337593543950335
  s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test18) {
  // 79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // -79228162514264337593543950335
  s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test19) {
  // 10
  s21_decimal val1 = {{0xA, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // 100
  s21_decimal val2 = {{0x64, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test20) {
  s21_decimal val1 = {{0, 0, 0, MINUS}};
  s21_decimal val2 = {{0, 0, 0, MINUS}};

  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test21) {
  s21_decimal val1 = {{0, 0, 0, MINUS}};
  s21_decimal val2 = {{0, 0, 0, MINUS}};

  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}
END_TEST

// different scale
START_TEST(is_less_test22) {
  s21_decimal src1, src2;
  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100000000000000000000;

  ck_assert_int_eq(FALSE, s21_is_less(src1, src2));
}
END_TEST

START_TEST(is_less_test23) {
  s21_decimal src1, src2;
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b10000000000011000000000000000000;

  src2.bits[0] = 0b01100101111100100100110110101100;
  src2.bits[1] = 0b00000000000001111010100110101011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000001100000000000000000;

  ck_assert_int_eq(TRUE, s21_is_less(src1, src2));
}
END_TEST

START_TEST(is_less_test24) {
  s21_decimal src1, src2;
  // src1 = -9798956154578676.797564534156;
  // src2 = 9798956154578676.797564534156;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b10000000000011000000000000000000;

  src2.bits[0] = 0b01010100010000000011110110001100;
  src2.bits[1] = 0b10001011010100100000010101011001;
  src2.bits[2] = 0b00011111101010011000000110101101;
  src2.bits[3] = 0b00000000000011000000000000000000;

  ck_assert_int_eq(TRUE, s21_is_less(src1, src2));
}
END_TEST

START_TEST(is_less_test25) {
  s21_decimal src1, src2;
  // src1 = 9798956154578676.797564534156;
  // src2 = 9798956154578676.797564534156;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b00000000000011000000000000000000;

  src2.bits[0] = 0b01010100010000000011110110001100;
  src2.bits[1] = 0b10001011010100100000010101011001;
  src2.bits[2] = 0b00011111101010011000000110101101;
  src2.bits[3] = 0b00000000000011000000000000000000;

  ck_assert_int_eq(FALSE, s21_is_less(src1, src2));
}
END_TEST

START_TEST(is_less_test26) {
  // 5678932
  s21_decimal val1 = {{0x56A754, 0, 0, 0}};
  // -5678932
  s21_decimal val2 = {{0x56A754, 0, 0, 0x80000000}};
  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test27) {
  // 5678932
  s21_decimal val1 = {{0x56A754, 0, 0, 0}};
  // 5678932
  s21_decimal val2 = {{0x56A754, 0, 0, 0}};
  ck_assert_int_eq(FALSE, s21_is_less(val2, val1));
}
END_TEST

START_TEST(is_less_test28) {
  // -1431655765
  s21_decimal val1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 1431655764.999999999999999999
  s21_decimal val2 = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x120000}};
  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test29) {
  // -1431655765
  s21_decimal val1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 1431655764.999999999999999999
  s21_decimal val2 = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x120000}};
  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test30) {
  // -1431655765
  s21_decimal val1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -1431655765
  s21_decimal val2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test31) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.0
  s21_decimal val2 = {{0xA, 0x0, 0x0, 0x10000}};
  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test32) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.22
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x20000}};
  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test33) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.22
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x20000}};
  ck_assert_int_eq(FALSE, s21_is_less(val2, val1));
}
END_TEST

START_TEST(is_less_test34) {
  // -10
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -122
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test35) {
  // -10
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -122
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(TRUE, s21_is_less(val2, val1));
}
END_TEST

START_TEST(is_less_test36) {
  // 10
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x00000000}};
  // 122
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x00000000}};
  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test37) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x00010000}};
  // 12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x00010000}};
  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test38) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x00010000}};
  // 12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x00010000}};
  ck_assert_int_eq(FALSE, s21_is_less(val2, val1));
}
END_TEST

START_TEST(is_less_test39) {
  // -1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80010000}};
  ck_assert_int_eq(TRUE, s21_is_less(val2, val1));
}
END_TEST

START_TEST(is_less_test40) {
  // -1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80010000}};
  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test41) {
  // -100.3
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x80010000}};
  // -100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x80020000}};
  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test42) {
  // -100.3
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x80010000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test43) {
  // -100.3
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x80010000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(FALSE, s21_is_less(val2, val1));
}
END_TEST

START_TEST(is_less_test44) {
  // 10.03
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x00020000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test45) {
  // 10.03
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x00020000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(FALSE, s21_is_less(val2, val1));
}
END_TEST

START_TEST(is_less_test46) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test47) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(FALSE, s21_is_less(val2, val1));
}
END_TEST

START_TEST(is_less_test48) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -10030
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(FALSE, s21_is_less(val2, val1));
}
END_TEST

START_TEST(is_less_test49) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -10030
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test50) {
  // 52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test51) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}
END_TEST

START_TEST(is_less_test52) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(FALSE, s21_is_less(val2, val1));
}
END_TEST

START_TEST(is_less_test53) {
  // 52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}

START_TEST(is_less_test54) {
  // 52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(TRUE, s21_is_less(val2, val1));
}

START_TEST(is_less_test55) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(FALSE, s21_is_less(val2, val1));
}

START_TEST(is_less_test56) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}

START_TEST(is_less_test57) {
  // 1.2297829382473034410
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}

START_TEST(is_less_test58) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}

START_TEST(is_less_test59) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // -0
  s21_decimal val2 = {{0x0, 0x0, 0x0, 0x80000000}};

  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}

START_TEST(is_less_test60) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 52818775009509558395695966891
  s21_decimal val2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}

START_TEST(is_less_test61) {
  // 52818775009509558395695966891
  s21_decimal val1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // -0
  s21_decimal val2 = {{0x0, 0x0, 0x0, 0x80000000}};

  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}

START_TEST(is_less_test62) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -52818775009509558395695966891
  s21_decimal val2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  ck_assert_int_eq(FALSE, s21_is_less(val1, val2));
}

START_TEST(is_less_test63) {
  // -52818775009509558395695966891
  s21_decimal val1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // -0
  s21_decimal val2 = {{0x0, 0x0, 0x0, 0x80000000}};

  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}

START_TEST(is_less_test64) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 5.281877500950955839569596690
  s21_decimal val2 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};

  ck_assert_int_eq(TRUE, s21_is_less(val1, val2));
}

Suite *is_less_suite() {
  Suite *s = suite_create("\033[35m< IS LESS TESTS\033[0m");

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
  tcase_add_test(is_less_tests, is_less_test17);
  tcase_add_test(is_less_tests, is_less_test18);
  tcase_add_test(is_less_tests, is_less_test19);
  tcase_add_test(is_less_tests, is_less_test20);
  tcase_add_test(is_less_tests, is_less_test21);
  tcase_add_test(is_less_tests, is_less_test22);
  tcase_add_test(is_less_tests, is_less_test23);
  tcase_add_test(is_less_tests, is_less_test24);
  tcase_add_test(is_less_tests, is_less_test25);
  tcase_add_test(is_less_tests, is_less_test26);
  tcase_add_test(is_less_tests, is_less_test27);
  tcase_add_test(is_less_tests, is_less_test28);
  tcase_add_test(is_less_tests, is_less_test29);
  tcase_add_test(is_less_tests, is_less_test30);
  tcase_add_test(is_less_tests, is_less_test31);
  tcase_add_test(is_less_tests, is_less_test32);
  tcase_add_test(is_less_tests, is_less_test33);
  tcase_add_test(is_less_tests, is_less_test34);
  tcase_add_test(is_less_tests, is_less_test35);
  tcase_add_test(is_less_tests, is_less_test36);
  tcase_add_test(is_less_tests, is_less_test37);
  tcase_add_test(is_less_tests, is_less_test38);
  tcase_add_test(is_less_tests, is_less_test39);
  tcase_add_test(is_less_tests, is_less_test40);
  tcase_add_test(is_less_tests, is_less_test41);
  tcase_add_test(is_less_tests, is_less_test42);
  tcase_add_test(is_less_tests, is_less_test43);
  tcase_add_test(is_less_tests, is_less_test44);
  tcase_add_test(is_less_tests, is_less_test45);
  tcase_add_test(is_less_tests, is_less_test46);
  tcase_add_test(is_less_tests, is_less_test47);
  tcase_add_test(is_less_tests, is_less_test48);
  tcase_add_test(is_less_tests, is_less_test49);
  tcase_add_test(is_less_tests, is_less_test50);
  tcase_add_test(is_less_tests, is_less_test51);
  tcase_add_test(is_less_tests, is_less_test52);
  tcase_add_test(is_less_tests, is_less_test53);
  tcase_add_test(is_less_tests, is_less_test54);
  tcase_add_test(is_less_tests, is_less_test55);
  tcase_add_test(is_less_tests, is_less_test56);
  tcase_add_test(is_less_tests, is_less_test57);
  tcase_add_test(is_less_tests, is_less_test58);
  tcase_add_test(is_less_tests, is_less_test59);
  tcase_add_test(is_less_tests, is_less_test60);
  tcase_add_test(is_less_tests, is_less_test61);
  tcase_add_test(is_less_tests, is_less_test62);
  tcase_add_test(is_less_tests, is_less_test63);
  tcase_add_test(is_less_tests, is_less_test64);

  return s;
}