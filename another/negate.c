#include "../s21_decimal.h"

/**
 * @brief Возвращает результат умножения указанного decimal на -1
 *
 * @return 0 - OK
 *         1 - ошибка вычисления
 */
int s21_negate(s21_decimal value, s21_decimal *res) {
  if (!is_correct_decimal(value) || res == NULL) return 1;

  // используем исключающее ИЛИ с маской MINUS
  // 1 ^ 1 = 0       0 ^ 1 = 1
  // 0 ^ 0 = 0       1 ^ 0 = 1
  value.bits[3] ^= MINUS;
  *res = value;

  return 0;
}