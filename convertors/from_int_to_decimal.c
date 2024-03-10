#include "../s21_decimal.h"

/**
 * @brief Преобразователь из int в decimal
 *
 * @return 0 - OK
 *         1 - ошибка конвертации
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) {
    return 1;
  }

  // Обнуление всех битов в dst
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;

  if (src < 0) {
    dst->bits[3] |= 1u << 31;
    if (src == INT_MIN) {
      dst->bits[0] = 1u << 31;
      return 0;
    }
    src = -src;
  }

  dst->bits[0] = src;

  return 0;
}