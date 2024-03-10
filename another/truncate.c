#include "../s21_decimal.h"

/**
 * @brief Возвращает целые цифры указанного Decimal числа; любые дробные цифры
 * отбрасываются, включая конечные нули
 *
 * @return 0 - OK
 *         1 - ошибка вычисления
 */
int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!is_correct_decimal(value) || result == NULL) return 1;

  // сохраняем знак децимал числа
  int sign = value.bits[3] & MINUS;
  // установка 0 на позицию знака в bits[3]
  value.bits[3] = value.bits[3] & (~MINUS);

  // убираем дробную часть
  s21_floor(value, result);

  // возвращаем знак результату
  result->bits[3] |= sign;

  return 0;
}