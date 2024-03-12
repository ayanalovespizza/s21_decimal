#include "s21_tests.h"

int main() {
  int fail = 0;

  Suite *decimal_suite[] = {is_equal_suite(),
                            is_not_equal_suite(),
                            is_less_suite(),
                            is_less_or_equal_suite(),
                            is_greater_suite(),
                            is_greater_or_equal_suite(),
                            negate_suite(),
                            floor_suite(),
                            truncate_suite(),
                            round_suite(),
                            decimal_to_float_suite(),
                            decimal_to_int_suite(),
                            float_to_decimal_suite(),
                            int_to_decimal_suite(),
                            add_suite(),
                            sub_suite(),
                            mul_suite(),
                            div_suite(),
                            NULL};

  for (int i = 0; decimal_suite[i] != NULL; i++) {  // (&& failed == 0)
    SRunner *decimal_runner = srunner_create(decimal_suite[i]);

    srunner_set_fork_status(decimal_runner, CK_NOFORK);
    srunner_run_all(decimal_runner, CK_NORMAL);

    fail += srunner_ntests_failed(decimal_runner);
    srunner_free(decimal_runner);
  }
  printf("\033[35m\n~~~~~~~~~ FAILED: %d ~~~~~~~~~\n\033[0m", fail);

  return fail == 0 ? 0 : 1;
}