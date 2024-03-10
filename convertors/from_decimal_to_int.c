#include "../s21_decimal.h"

/**
 * @brief Преобразователь из decimal в int
 *
 * @warning Если в числе типа decimal есть дробная часть, то ее следует
 *          отбросить (0,9 => 0)
 *
 * @return 0 - OK
 *         1 - ошибка конвертации
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;

  // Проверка на NULL указатель dst
  if (dst == NULL || !is_correct_decimal(src)) {
    error = 1;  // Вернуть ошибку, если указатель NULL
  } else {
    s21_decimal src_trunc;
    s21_truncate(src, &src_trunc);
    int sign = (src_trunc.bits[3] & MINUS) ? -1 : 1;

    if ((src_trunc.bits[2] == 0) && (src_trunc.bits[1] == 0) &&
        (src_trunc.bits[0] < 2147483648 ||
         (sign == -1 && src_trunc.bits[0] == 2147483648))) {
      *dst = src_trunc.bits[0];
      if (sign == -1) {
        (*dst) *= -1;
      }
    } else {
      // Значение src выходит за пределы допустимого диапазона для int
      error = 1;
    }
  }
  return error;
}