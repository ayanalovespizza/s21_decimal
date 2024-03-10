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

Suite *negate_suite();    // done
Suite *floor_suite();     // done
Suite *truncate_suite();  // done
Suite *round_suite();     // done

Suite *decimal_to_float_suite();
Suite *decimal_to_int_suite();
Suite *float_to_decimal_suite();
Suite *int_to_decimal_suite();

Suite *add_suite();
Suite *sub_suite();

Suite *mul_suite();
Suite *div_suite();

#endif