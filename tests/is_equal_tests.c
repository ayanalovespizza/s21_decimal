#include "s21_tests.h"

#define TRUE 1
#define FALSE 0

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

START_TEST(is_equal_test15) {
  // 0
  s21_decimal val1 = {{0, 0, 0, 0}};
  // 0
  s21_decimal val2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(TRUE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test16) {
  // 0
  s21_decimal val1 = {{0, 0, 0, 0}};
  // -0
  s21_decimal val2 = {{0, 0, 0, MINUS}};
  ck_assert_int_eq(TRUE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test17) {
  // 79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // 79228162514264337593543950335
  s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(TRUE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test18) {
  // 79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // -79228162514264337593543950335
  s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test19) {
  // 10
  s21_decimal val1 = {{0xA, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // 100
  s21_decimal val2 = {{0x64, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test20) {
  s21_decimal val1 = {{0, 0, 0, MINUS}};
  s21_decimal val2 = {{0, 0, 0, MINUS}};

  ck_assert_int_eq(TRUE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test21) {
  s21_decimal val1 = {{0, 0, 0, MINUS}};
  s21_decimal val2 = {{0, 0, 0, MINUS}};

  ck_assert_int_eq(TRUE, s21_is_equal(val1, val2));
}
END_TEST

// different scale
START_TEST(is_equal_test22) {
  s21_decimal src1, src2;
  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100000000000000000000;

  ck_assert_int_eq(FALSE, s21_is_equal(src1, src2));
}
END_TEST

START_TEST(is_equal_test23) {
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

  ck_assert_int_eq(FALSE, s21_is_equal(src1, src2));
}
END_TEST

START_TEST(is_equal_test24) {
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

  ck_assert_int_eq(FALSE, s21_is_equal(src1, src2));
}
END_TEST

START_TEST(is_equal_test25) {
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

  ck_assert_int_eq(TRUE, s21_is_equal(src1, src2));
}
END_TEST

START_TEST(is_equal_test26) {
  // 5678932
  s21_decimal val1 = {{0x56A754, 0, 0, 0}};
  // -5678932
  s21_decimal val2 = {{0x56A754, 0, 0, 0x80000000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test27) {
  // 5678932
  s21_decimal val1 = {{0x56A754, 0, 0, 0}};
  // 5678932
  s21_decimal val2 = {{0x56A754, 0, 0, 0}};
  ck_assert_int_eq(TRUE, s21_is_equal(val2, val1));
}
END_TEST

START_TEST(is_equal_test28) {
  // -1431655765
  s21_decimal val1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 1431655764.999999999999999999
  s21_decimal val2 = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x120000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test29) {
  // -1431655765
  s21_decimal val1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 1431655764.999999999999999999
  s21_decimal val2 = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x120000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test30) {
  // -1431655765
  s21_decimal val1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -1431655765
  s21_decimal val2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(TRUE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test31) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.0
  s21_decimal val2 = {{0xA, 0x0, 0x0, 0x10000}};
  ck_assert_int_eq(TRUE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test32) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.22
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x20000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test33) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.22
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x20000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val2, val1));
}
END_TEST

START_TEST(is_equal_test34) {
  // -10
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -122
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test35) {
  // -10
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -122
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val2, val1));
}
END_TEST

START_TEST(is_equal_test36) {
  // 10
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x00000000}};
  // 122
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x00000000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test37) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x00010000}};
  // 12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x00010000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test38) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x00010000}};
  // 12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x00010000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val2, val1));
}
END_TEST

START_TEST(is_equal_test39) {
  // -1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80010000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val2, val1));
}
END_TEST

START_TEST(is_equal_test40) {
  // -1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80010000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test41) {
  // -100.3
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x80010000}};
  // -100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x80020000}};
  ck_assert_int_eq(TRUE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test42) {
  // -100.3
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x80010000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test43) {
  // -100.3
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x80010000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val2, val1));
}
END_TEST

START_TEST(is_equal_test44) {
  // 10.03
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x00020000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test45) {
  // 10.03
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x00020000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val2, val1));
}
END_TEST

START_TEST(is_equal_test46) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test47) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val2, val1));
}
END_TEST

START_TEST(is_equal_test48) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -10030
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val2, val1));
}
END_TEST

START_TEST(is_equal_test49) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -10030
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test50) {
  // 52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(TRUE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test51) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_test52) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(FALSE, s21_is_equal(val2, val1));
}
END_TEST

START_TEST(is_equal_test53) {
  // 52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}

START_TEST(is_equal_test54) {
  // 52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(FALSE, s21_is_equal(val2, val1));
}

START_TEST(is_equal_test55) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(FALSE, s21_is_equal(val2, val1));
}

START_TEST(is_equal_test56) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}

START_TEST(is_equal_test57) {
  // 1.2297829382473034410
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(TRUE, s21_is_equal(val1, val2));
}

START_TEST(is_equal_test58) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}

START_TEST(is_equal_test59) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // -0
  s21_decimal val2 = {{0x0, 0x0, 0x0, 0x80000000}};

  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}

START_TEST(is_equal_test60) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 52818775009509558395695966891
  s21_decimal val2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}

START_TEST(is_equal_test61) {
  // 52818775009509558395695966891
  s21_decimal val1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // -0
  s21_decimal val2 = {{0x0, 0x0, 0x0, 0x80000000}};

  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}

START_TEST(is_equal_test62) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -52818775009509558395695966891
  s21_decimal val2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}

START_TEST(is_equal_test63) {
  // -52818775009509558395695966891
  s21_decimal val1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // -0
  s21_decimal val2 = {{0x0, 0x0, 0x0, 0x80000000}};

  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}

START_TEST(is_equal_test64) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 5.281877500950955839569596690
  s21_decimal val2 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};

  ck_assert_int_eq(FALSE, s21_is_equal(val1, val2));
}

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
  tcase_add_test(is_equal_tests, is_equal_test15);
  tcase_add_test(is_equal_tests, is_equal_test16);
  tcase_add_test(is_equal_tests, is_equal_test17);
  tcase_add_test(is_equal_tests, is_equal_test18);
  tcase_add_test(is_equal_tests, is_equal_test19);
  tcase_add_test(is_equal_tests, is_equal_test20);
  tcase_add_test(is_equal_tests, is_equal_test21);
  tcase_add_test(is_equal_tests, is_equal_test22);
  tcase_add_test(is_equal_tests, is_equal_test23);
  tcase_add_test(is_equal_tests, is_equal_test24);
  tcase_add_test(is_equal_tests, is_equal_test25);
  tcase_add_test(is_equal_tests, is_equal_test26);
  tcase_add_test(is_equal_tests, is_equal_test27);
  tcase_add_test(is_equal_tests, is_equal_test28);
  tcase_add_test(is_equal_tests, is_equal_test29);
  tcase_add_test(is_equal_tests, is_equal_test30);
  tcase_add_test(is_equal_tests, is_equal_test31);
  tcase_add_test(is_equal_tests, is_equal_test32);
  tcase_add_test(is_equal_tests, is_equal_test33);
  tcase_add_test(is_equal_tests, is_equal_test34);
  tcase_add_test(is_equal_tests, is_equal_test35);
  tcase_add_test(is_equal_tests, is_equal_test36);
  tcase_add_test(is_equal_tests, is_equal_test37);
  tcase_add_test(is_equal_tests, is_equal_test38);
  tcase_add_test(is_equal_tests, is_equal_test39);
  tcase_add_test(is_equal_tests, is_equal_test40);
  tcase_add_test(is_equal_tests, is_equal_test41);
  tcase_add_test(is_equal_tests, is_equal_test42);
  tcase_add_test(is_equal_tests, is_equal_test43);
  tcase_add_test(is_equal_tests, is_equal_test44);
  tcase_add_test(is_equal_tests, is_equal_test45);
  tcase_add_test(is_equal_tests, is_equal_test46);
  tcase_add_test(is_equal_tests, is_equal_test47);
  tcase_add_test(is_equal_tests, is_equal_test48);
  tcase_add_test(is_equal_tests, is_equal_test49);
  tcase_add_test(is_equal_tests, is_equal_test50);
  tcase_add_test(is_equal_tests, is_equal_test51);
  tcase_add_test(is_equal_tests, is_equal_test52);
  tcase_add_test(is_equal_tests, is_equal_test53);
  tcase_add_test(is_equal_tests, is_equal_test54);
  tcase_add_test(is_equal_tests, is_equal_test55);
  tcase_add_test(is_equal_tests, is_equal_test56);
  tcase_add_test(is_equal_tests, is_equal_test57);
  tcase_add_test(is_equal_tests, is_equal_test58);
  tcase_add_test(is_equal_tests, is_equal_test59);
  tcase_add_test(is_equal_tests, is_equal_test60);
  tcase_add_test(is_equal_tests, is_equal_test61);
  tcase_add_test(is_equal_tests, is_equal_test62);
  tcase_add_test(is_equal_tests, is_equal_test63);
  tcase_add_test(is_equal_tests, is_equal_test64);

  return s;
}
