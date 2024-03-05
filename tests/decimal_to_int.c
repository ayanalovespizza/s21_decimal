#include <check.h>
#include "s21_tests.h"
#include <limits.h>

START_TEST(test_NULL) {
    s21_decimal result = {0};
    int success = s21_from_decimal_to_int(result,NULL);
    ck_assert_int_eq(success, 1);
} END_TEST


START_TEST(test_MAX_INT) {
    s21_decimal result = {0};
    result.bits[0]=0x7fffffff;
    int res = 0;
    int success = s21_from_decimal_to_int(result,&res);
    ck_assert_int_eq(success, 0);
    ck_assert_int_eq(res, INT_MAX);

} END_TEST

START_TEST(test_MIN_INT) {
    s21_decimal result = {0};
    result.bits[0] = 0x80000000;
    result.bits[3] = 0x80000000;
    int res = 0;
    int success = s21_from_decimal_to_int(result,&res);
    ck_assert_int_eq(success, 0);
    ck_assert_int_eq(res, INT_MIN);

} END_TEST



START_TEST(test_OVERFLOW) {
    s21_decimal result = {0};
    result.bits[0] = 0XFFFFFFFF;
    int res = 0;
    int success = s21_from_decimal_to_int(result,&res);
    ck_assert_int_eq(success, 1);


} END_TEST




Suite *decimal_to_int(void) {
    Suite *s = suite_create("\033[35m== IS DECIMAL_TO_INT TESTS\033[0m");
    TCase *from_decimal_to_int = tcase_create("IS_EQUAL");
    suite_add_tcase(s, from_decimal_to_int);
    tcase_add_test(from_decimal_to_int, test_NULL);
    tcase_add_test(from_decimal_to_int, test_MAX_INT);
    tcase_add_test(from_decimal_to_int, test_MIN_INT);
    tcase_add_test(from_decimal_to_int, test_OVERFLOW);

    return s;
}