#include "../s21_decimal.h"

/**
 * @brief Округляет указанное decimal число до ближайшего целого числа в сторону
 * отрицательной бесконечности
 *
 * @return 0 - OK
 *         1 - ошибка вычисления
 */
int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!is_correct_decimal(value) || result == NULL) return 1;

  // перевод в расширенный децимал
  s21_work_decimal work_decimal = initial_to_work(value);

  // переменные для сохранения значения степени и дробной части
  int scale = 0, remainder = 0;
  scale = work_decimal.scale;

  // уменьшаем scale, сохраняем остаток
  for (int i = 0; i < scale; i++) remainder += pointright(&work_decimal);

  // если число отрицательное, то увеличиваем, его на 1 (-1,5 => -1 => -2)
  if (remainder != 0 && value.bits[3] & MINUS) {
    work_decimal.bits[0]++;
    // если в младших битах образовалось переполнение, то перекидываем его в
    // старшие биты
    is_overflow(&work_decimal);
  }

  // переводим в обычный децимал и восстанавливаем знак
  *result = work_to_initial(work_decimal);
  result->bits[3] = value.bits[3] & MINUS;

  return 0;
}