#include "../s21_decimal.h"

/**
 * @brief Функция "меньше"
 *
 * @return 0 - FALSE
 *         1 - TRUE
 */
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;

  // если v1 положительное (первый бит 0), а у v2 отрицательное (первый бит 1)
  // или выполнятся равенство, то первое не меньше второго
  if ((value_1.bits[3] & MINUS) < (value_2.bits[3] & MINUS) ||
      s21_is_equal(value_1, value_2))
    result = 0;

  // наоборот: v1 отрицательное, а v2 положительное, то первое меньше второго
  else if ((value_1.bits[3] & MINUS) > (value_2.bits[3] & MINUS))
    result = 1;

  // если прошлые проверки прошли, то сравниваем биты
  else {
    s21_work_decimal value_1_work, value_2_work;

    value_1_work = initial_to_work(value_1);
    value_2_work = initial_to_work(value_2);

    point_to_normal(&value_1_work, &value_2_work);

    for (int i = 2; i >= 0; i--) {
      // если в верхнем int первый децимал меньше то
      // значит и весь первый децимал меньше второго
      if (value_1_work.bits[i] < value_2_work.bits[i]) {
        result = 1;
        i = -1;

        // если в верхнем int первый децимал больше то
        // значит и весь первый децимал больше второго
      } else if (value_1_work.bits[i] > value_2_work.bits[i]) {
        result = 0;
        i = -1;
      }
    }

    // если оба числа отрицательные, то инверсируем результат
    if (value_1.bits[3] & MINUS) {
      if (result == 1)
        result = 0;
      else if (result == 0)
        result = 1;
    }
  }

  return result;
}