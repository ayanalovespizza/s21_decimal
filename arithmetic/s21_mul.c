#include <stdio.h>

#include "../s21_decimal.h"

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
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int status = 0;
  if (is_correct_decimal(value_1) && is_correct_decimal(value_2) &&
      result != NULL) {
    // проверка на нули

    unsigned int value_1_sign = 0;
    unsigned int value_2_sign = 0;
    // перевод в рабочий децимал
    s21_work_decimal value_1_work = initial_to_work(value_1);
    s21_work_decimal value_2_work = initial_to_work(value_2);
    value_1_sign = value_1_work.sign;
    value_2_sign = value_2_work.sign;
    s21_work_decimal result_work = {{0, 0, 0, 0, 0, 0, 0}, 0, 0};
    // сохраняем результирующий знак
    if (value_1_sign != value_2_sign) {
      result_work.sign = 1;
    } else {
      result_work.sign = 0;
    }

    result_work.scale = value_1_work.scale + value_2_work.scale;

    //            printf("scale %x\n",result_work.scale);
    result_work.bits[0] = value_2_work.bits[0] * value_1_work.bits[0];
    result_work.bits[1] = value_2_work.bits[0] * value_1_work.bits[1] +
                          value_2_work.bits[1] * value_1_work.bits[0];
    result_work.bits[2] = value_2_work.bits[0] * value_1_work.bits[2] +
                          value_2_work.bits[1] * value_1_work.bits[1] +
                          value_2_work.bits[2] * value_1_work.bits[0];
    result_work.bits[3] = value_2_work.bits[1] * value_1_work.bits[2] +
                          value_2_work.bits[2] * value_1_work.bits[1];
    result_work.bits[4] = value_2_work.bits[2] * value_1_work.bits[2];

    //            result_work.scale = ((value_1.bits[3] & SCALE) >> 16) +
    //                                ((value_2.bits[3] & SCALE) >> 16);

    is_overflow(&result_work);
    status = tidy_work_decimal(&result_work);

    *result = work_to_initial(result_work);
  } else {
    status = 1;
  }

  return status;
}