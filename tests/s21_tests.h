#ifndef S21_TESTS_H
#define S21_TESTS_H

#include <check.h>
#include <stdio.h>

#include "../s21_decimal.h"

Suite *is_equal_suite();             // done
Suite *is_not_equal_suite();         // done
Suite *is_less_suite();              // done
Suite *is_less_or_equal_suite();     // test 9 is sus
Suite *is_greater_suite();           // done
Suite *is_greater_or_equal_suite();  // test 9 is sus

Suite *negate_suite();

#endif