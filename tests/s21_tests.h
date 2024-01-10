#ifndef S21_TESTS_H
#define S21_TESTS_H

#include <check.h>
#include <stdio.h>

#include "../s21_decimal.h"

Suite *is_equal_suite();
Suite *is_not_equal_suite();
Suite *is_less_suite();

#endif