#include "s21_tests.h"

int main() {
    int fail = 0;

    Suite *decimal_suite[] = {int_to_decimal(),
                              decimal_to_int(),
                              float_to_decimal(),
                              decimal_to_float(),
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