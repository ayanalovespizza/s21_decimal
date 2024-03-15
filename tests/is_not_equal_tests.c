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

START_TEST(is_not_equal_test8) {
  // 79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // 79228162514264337593543950335
  s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(FALSE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test9) {
  // 79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // -79228162514264337593543950335
  s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test10) {
  // 10
  s21_decimal val1 = {{0xA, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // 100
  s21_decimal val2 = {{0x64, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test11) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_set_bit(&val1, 32, 1);
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_set_bit(&val2, 28, 1);

  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test12) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_set_bit(&val1, 32, 1);
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_set_bit(&val2, 32, 1);

  ck_assert_int_eq(FALSE, s21_is_not_equal(val1, val2));
}
END_TEST

// different scale
START_TEST(is_not_equal_test13) {
  s21_decimal src1, src2;
  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100000000000000000000;

  ck_assert_int_eq(TRUE, s21_is_not_equal(src1, src2));
}
END_TEST

START_TEST(is_not_equal_test14) {
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

  ck_assert_int_eq(TRUE, s21_is_not_equal(src1, src2));
}
END_TEST

START_TEST(is_not_equal_test15) {
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

  ck_assert_int_eq(TRUE, s21_is_not_equal(src1, src2));
}
END_TEST

START_TEST(is_not_equal_test16) {
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

  ck_assert_int_eq(FALSE, s21_is_not_equal(src1, src2));
}
END_TEST

START_TEST(is_not_equal_test17) {
  // 5678932
  s21_decimal val1 = {{0x56A754, 0, 0, 0}};
  // -5678932
  s21_decimal val2 = {{0x56A754, 0, 0, 0x80000000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test18) {
  // 5678932
  s21_decimal val1 = {{0x56A754, 0, 0, 0}};
  // 5678932
  s21_decimal val2 = {{0x56A754, 0, 0, 0}};
  ck_assert_int_eq(FALSE, s21_is_not_equal(val2, val1));
}
END_TEST

START_TEST(is_not_equal_test19) {
  // -1431655765
  s21_decimal val1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 1431655764.999999999999999999
  s21_decimal val2 = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x120000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test20) {
  // -1431655765
  s21_decimal val1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 1431655764.999999999999999999
  s21_decimal val2 = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x120000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test21) {
  // -1431655765
  s21_decimal val1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -1431655765
  s21_decimal val2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(FALSE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test22) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.0
  s21_decimal val2 = {{0xA, 0x0, 0x0, 0x10000}};
  ck_assert_int_eq(FALSE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test23) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.22
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x20000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test24) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.22
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x20000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val2, val1));
}
END_TEST

START_TEST(is_not_equal_test25) {
  // -10
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -122
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test26) {
  // -10
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -122
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val2, val1));
}
END_TEST

START_TEST(is_not_equal_test27) {
  // 10
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x00000000}};
  // 122
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x00000000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test28) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x00010000}};
  // 12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x00010000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test29) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x00010000}};
  // 12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x00010000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val2, val1));
}
END_TEST

START_TEST(is_not_equal_test30) {
  // -1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80010000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val2, val1));
}
END_TEST

START_TEST(is_not_equal_test31) {
  // -1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80010000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test32) {
  // -100.3
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x80010000}};
  // -100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x80020000}};
  ck_assert_int_eq(FALSE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test33) {
  // -100.3
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x80010000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test34) {
  // -100.3
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x80010000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val2, val1));
}
END_TEST

START_TEST(is_not_equal_test35) {
  // 10.03
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x00020000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test36) {
  // 10.03
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x00020000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val2, val1));
}
END_TEST

START_TEST(is_not_equal_test37) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test38) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val2, val1));
}
END_TEST

START_TEST(is_not_equal_test39) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -10030
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val2, val1));
}
END_TEST

START_TEST(is_not_equal_test40) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -10030
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test41) {
  // 52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(FALSE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test42) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(is_not_equal_test43) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(TRUE, s21_is_not_equal(val2, val1));
}
END_TEST

START_TEST(is_not_equal_test44) {
  // 52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}

START_TEST(is_not_equal_test45) {
  // 52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(TRUE, s21_is_not_equal(val2, val1));
}

START_TEST(is_not_equal_test46) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(TRUE, s21_is_not_equal(val2, val1));
}

START_TEST(is_not_equal_test47) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}

START_TEST(is_not_equal_test48) {
  // 1.2297829382473034410
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(FALSE, s21_is_not_equal(val1, val2));
}

START_TEST(is_not_equal_test49) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}

START_TEST(is_not_equal_test50) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // -0
  s21_decimal val2 = {{0x0, 0x0, 0x0, 0x80000000}};

  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}

START_TEST(is_not_equal_test51) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 52818775009509558395695966891
  s21_decimal val2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}

START_TEST(is_not_equal_test52) {
  // 52818775009509558395695966891
  s21_decimal val1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // -0
  s21_decimal val2 = {{0x0, 0x0, 0x0, 0x80000000}};

  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}

START_TEST(is_not_equal_test53) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -52818775009509558395695966891
  s21_decimal val2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}

START_TEST(is_not_equal_test54) {
  // -52818775009509558395695966891
  s21_decimal val1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // -0
  s21_decimal val2 = {{0x0, 0x0, 0x0, 0x80000000}};

  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}

START_TEST(is_not_equal_test55) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 5.281877500950955839569596690
  s21_decimal val2 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};

  ck_assert_int_eq(TRUE, s21_is_not_equal(val1, val2));
}

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
  tcase_add_test(is_not_equal_tests, is_not_equal_test8);
  tcase_add_test(is_not_equal_tests, is_not_equal_test9);
  tcase_add_test(is_not_equal_tests, is_not_equal_test10);
  tcase_add_test(is_not_equal_tests, is_not_equal_test11);
  tcase_add_test(is_not_equal_tests, is_not_equal_test12);
  tcase_add_test(is_not_equal_tests, is_not_equal_test13);
  tcase_add_test(is_not_equal_tests, is_not_equal_test14);
  tcase_add_test(is_not_equal_tests, is_not_equal_test15);
  tcase_add_test(is_not_equal_tests, is_not_equal_test16);
  tcase_add_test(is_not_equal_tests, is_not_equal_test17);
  tcase_add_test(is_not_equal_tests, is_not_equal_test18);
  tcase_add_test(is_not_equal_tests, is_not_equal_test19);
  tcase_add_test(is_not_equal_tests, is_not_equal_test20);
  tcase_add_test(is_not_equal_tests, is_not_equal_test21);
  tcase_add_test(is_not_equal_tests, is_not_equal_test22);
  tcase_add_test(is_not_equal_tests, is_not_equal_test23);
  tcase_add_test(is_not_equal_tests, is_not_equal_test24);
  tcase_add_test(is_not_equal_tests, is_not_equal_test25);
  tcase_add_test(is_not_equal_tests, is_not_equal_test26);
  tcase_add_test(is_not_equal_tests, is_not_equal_test27);
  tcase_add_test(is_not_equal_tests, is_not_equal_test28);
  tcase_add_test(is_not_equal_tests, is_not_equal_test29);
  tcase_add_test(is_not_equal_tests, is_not_equal_test30);
  tcase_add_test(is_not_equal_tests, is_not_equal_test31);
  tcase_add_test(is_not_equal_tests, is_not_equal_test32);
  tcase_add_test(is_not_equal_tests, is_not_equal_test33);
  tcase_add_test(is_not_equal_tests, is_not_equal_test34);
  tcase_add_test(is_not_equal_tests, is_not_equal_test35);
  tcase_add_test(is_not_equal_tests, is_not_equal_test36);
  tcase_add_test(is_not_equal_tests, is_not_equal_test37);
  tcase_add_test(is_not_equal_tests, is_not_equal_test38);
  tcase_add_test(is_not_equal_tests, is_not_equal_test39);
  tcase_add_test(is_not_equal_tests, is_not_equal_test40);
  tcase_add_test(is_not_equal_tests, is_not_equal_test41);
  tcase_add_test(is_not_equal_tests, is_not_equal_test42);
  tcase_add_test(is_not_equal_tests, is_not_equal_test43);
  tcase_add_test(is_not_equal_tests, is_not_equal_test44);
  tcase_add_test(is_not_equal_tests, is_not_equal_test45);
  tcase_add_test(is_not_equal_tests, is_not_equal_test46);
  tcase_add_test(is_not_equal_tests, is_not_equal_test47);
  tcase_add_test(is_not_equal_tests, is_not_equal_test48);
  tcase_add_test(is_not_equal_tests, is_not_equal_test49);
  tcase_add_test(is_not_equal_tests, is_not_equal_test50);
  tcase_add_test(is_not_equal_tests, is_not_equal_test51);
  tcase_add_test(is_not_equal_tests, is_not_equal_test52);
  tcase_add_test(is_not_equal_tests, is_not_equal_test53);
  tcase_add_test(is_not_equal_tests, is_not_equal_test54);
  tcase_add_test(is_not_equal_tests, is_not_equal_test55);

  return s;
}