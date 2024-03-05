#include "s21_tests.h"
#include <check.h>
#include <float.h>
#include <math.h>


START_TEST(test_from_float_to_decimal) {
    // -2.28401628E-19
    float f = -2.28401628E-19;
    // -0.0000000000000000002284016
    s21_decimal decimal_check = {{0x22D9F0, 0x0, 0x0, 0x80190000}};
    s21_decimal  result ={0};

    int ret = s21_from_float_to_decimal(f,&result);

    ck_assert_int_eq(ret,0);

    ck_assert_int_eq(s21_is_equal(result,decimal_check),1);

}
END_TEST


START_TEST(test_Overflow) {
    // -2.28401628E-19
    float f = FLT_MAX;
    // -0.0000000000000000002284016

    s21_decimal  result ={0};

    int ret = s21_from_float_to_decimal(f,&result);

    ck_assert_int_eq(ret,1);


}
END_TEST


START_TEST(test_nan_or_inf) {
    // -2.28401628E-19
    float f = INFINITY;

    s21_decimal  result ={0};
    int ret = s21_from_float_to_decimal(f,&result);
    ck_assert_int_eq(ret,1);
}
END_TEST


START_TEST(test_1) {
    // -2.28401628E-19
    float f = 536870880.0e+90;

    s21_decimal  result ={0};
    int ret = s21_from_float_to_decimal(f,&result);
    ck_assert_int_eq(ret,1);
}
END_TEST


Suite *float_to_decimal(void) {
    Suite *s = suite_create("\033[35m== IS FLOAT_TO_DECIMAL TESTS\033[0m");
    TCase *float_to_decimal = tcase_create("IS_EQUAL");
    suite_add_tcase(s, float_to_decimal);
    tcase_add_test(float_to_decimal, test_from_float_to_decimal);
    tcase_add_test(float_to_decimal, test_Overflow);
    tcase_add_test(float_to_decimal, test_nan_or_inf);
    tcase_add_test(float_to_decimal, test_1);
    return s;
}