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
<<<<<<< HEAD

Suite *negate_suite();  // done
Suite *floor_suite();   // done
=======
Suite *add_suite();   
Suite *negate_suite();
>>>>>>> 4c4fcf395e7cbfa439ee4bc731b36bc244ba7f56

#endif