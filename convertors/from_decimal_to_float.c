#include "../s21_decimal.h"

/**
 * @brief Преобразователь из decimal в float
 *
 * @return 0 - OK
 *         1 - ошибка конвертации
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL || !is_correct_decimal(src)) {
    return 1;
  }

  int minus = (src.bits[3] & MINUS) ? -1 : 1;

  int exp = (src.bits[3] & SCALE) >> 16;
  long double res = 0;
  *dst = 0;

  for (int k = 0; k < 96; k++) {
    int tmp = (src.bits[k / 32] >> (k % 32)) & 1;
    if (tmp == 1) {
      res += powf(2, k);
    }
  }
  for (int i = 0; i < exp; i++) {
    res /= 10;
  }
  *dst = minus * res;

  return 0;
}