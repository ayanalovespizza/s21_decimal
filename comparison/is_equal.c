#include "../s21_decimal.h"

void s21_normalized_scales_decimal(s21_work_decimal *a, s21_work_decimal *b,
                                   int overflow);
void s21_increase_scale_with_check(s21_work_decimal *c, int diff,
                                   int check_overflow);
int s21_big_div_ten(s21_work_decimal *value);
int s21_overflow(s21_work_decimal c);

/**
 * @brief Функция "равно"
 *
 * @return 0 - FALSE
 *         1 - TRUE
 */
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;

  // если все биты в целом числе равны = 0, но знаки разные, то все равно числа
  // равные
  if ((value_1.bits[3] & MINUS) != (value_2.bits[3] & MINUS) &&
      ((value_1.bits[0] == value_2.bits[0]) &&
       (value_1.bits[1] == value_2.bits[1]) &&
       (value_1.bits[2] == value_2.bits[2]) && (value_1.bits[0] == 0) &&
       (value_1.bits[1] == 0) && (value_1.bits[2] == 0)))
    result = 1;

  // если знаки разные, то числа сразу не равны
  else if ((value_1.bits[3] & MINUS) != (value_2.bits[3] & MINUS))
    result = 0;

  // если прошлые проверки прошли, то начинаем сравнить биты
  else {
    s21_work_decimal value_1_work, value_2_work;

    value_1_work = initial_to_work(value_1);
    value_2_work = initial_to_work(value_2);

    point_to_normal(&value_1_work, &value_2_work);

    for (int i = 6; i >= 0; i--)
      if (value_1_work.bits[i] != value_2_work.bits[i]) result = 0;
  }

  return result;
}