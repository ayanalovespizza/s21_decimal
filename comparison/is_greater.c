#include "../s21_decimal.h"

/**
 * @brief Функция "больше"
 *
 * @return 0 - FALSE
 *         1 - TRUE
 */
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;

  if (!(s21_is_less_or_equal(value_1, value_2))) result = 1;

  return result;
}