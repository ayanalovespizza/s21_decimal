#include "../s21_decimal.h"

int normalize(s21_work_decimal *dec);

/**
 * @brief Умножение
 *
 * @warning При получении чисел, не вмещающихся в мантису
 * (bits[0], bits[1], bits[2]), использовать банковское округеление
 *
 * @return 0 - OK
 *         1 - число слишком велико или равно бесконечности
 *         2 - число слишком мало или равно отрицательной бесконечности
 */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;

  s21_work_decimal value_1_work = initial_to_work(value_1);
  s21_work_decimal value_2_work = initial_to_work(value_2);

  s21_work_decimal result_work = {{0, 0, 0, 0, 0, 0, 0}, 0};

  result_work.bits[0] = value_2_work.bits[0] * value_1_work.bits[0];
  result_work.bits[1] = value_2_work.bits[0] * value_1_work.bits[1] +
                        value_2_work.bits[1] * value_1_work.bits[0];
  result_work.bits[2] = value_2_work.bits[0] * value_1_work.bits[2] +
                        value_2_work.bits[1] * value_1_work.bits[1] +
                        value_2_work.bits[2] * value_1_work.bits[0];
  result_work.bits[3] = value_2_work.bits[1] * value_1_work.bits[2] +
                        value_2_work.bits[2] * value_1_work.bits[1];
  result_work.bits[4] = value_2_work.bits[2] * value_1_work.bits[2];

  is_overflow(&result_work);

  int sign = 0;
  if ((value_1.bits[3] & MINUS) != (value_2.bits[3] & MINUS)) {
    sign = 1;
  } else {
    sign = 0;
  }

  tidy_work_decimal(&result_work);

  *result = work_to_initial(result_work);
  if (sign) {
    result->bits[3] |= MINUS;
  }
  result->bits[3] |= (value_1.bits[3] & SCALE) +
                     (value_2.bits[3] & SCALE);  // суммируем скейлы

  return status;
}
