#include "../s21_decimal.h"

/**
 * @brief Округляет decimal до ближайшего целого числа
 *
 * @return 0 - OK
 *         1 - ошибка вычисления
 */
int s21_round(s21_decimal value, s21_decimal* result) {
  if (!is_correct_decimal(value) || result == NULL) return 1;

  int last_digit = 0, full_remainder = 0;
  s21_work_decimal value_work = initial_to_work(value);

  // с помощью pointright убираем всю дробную часть, сохраняем общий
  // остаток, а также последнюю (первую после точки цифру)
  for (int i = 6; i >= 0; i--) {
    while (value_work.scale > 0 && value_work.bits[i] != 0) {
      last_digit = pointright(&value_work);
      full_remainder += last_digit;
    }
  }

  /* банковское округление
  - если последняя цифра > 5, то отбрасываем и плюс один
  - если последняя цифра < 5, то отбрасываем дробь
  - если последняя цифра == 5, то:
    - если в  остатке еще что-то есть (> 5), то отбрасываем и плюс один
    - если в остатке нет еще чего-то (== 5), то
      - до 5 четная цифра, то отбрасываем
      - до 5 нечетная цифра, то увечиливаем
  */
  if (last_digit != 5) {
    if (last_digit > 5) {
      value_work.bits[0]++;
      is_overflow(&value_work);
    }
  } else {
    if (full_remainder > 5) {
      value_work.bits[0]++;
      is_overflow(&value_work);
    } else {
      if (value_work.bits[0] % 2 == 1) {
        value_work.bits[0]++;
        is_overflow(&value_work);
      }
    }
  }

  *result = work_to_initial(value_work);
  result->bits[3] = value.bits[3] & MINUS;

  return 0;
}
