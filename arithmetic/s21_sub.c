#include "../s21_decimal.h"

/**
 * @brief Вычитание
 *
 * @warning При получении чисел, не вмещающихся в мантису
 * (bits[0], bits[1], bits[2]), использовать банковское округеление
 *
 * @return 0 - OK
 *         1 - число слишком велико или равно бесконечности
 *         2 - число слишком мало или равно отрицательной бесконечности
 */
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  // Конвертация из decimal в work_decimal
  int status = 0;
  if (is_correct_decimal(value_1) && is_correct_decimal(value_2) &&
      result != NULL) {
    s21_work_decimal extand_decimal_1 = initial_to_work(value_1);
    s21_work_decimal extand_decimal_2 = initial_to_work(value_2);
    s21_work_decimal extand_result;
    unsigned int value_1_sign = 0;
    unsigned int value_2_sign = 0;
    // s21_decimal result_before; // unused
    // Зануление расширенного результуруемого децимала
    work_make_null(&extand_result);
    // Зануление обычного результуруемого децимала
    initial_make_null(result);
    // Cохранение знаков
    value_1_sign = extand_decimal_1.sign;
    value_2_sign = extand_decimal_2.sign;
    // Cохранение результирующего масштаба
    if (extand_decimal_1.scale - extand_decimal_2.scale <= 0) {
      extand_result.scale = extand_decimal_2.scale;
    } else {
      extand_result.scale = extand_decimal_1.scale;
    }
    // Наша нормализация чисел для арифметики
    point_to_normal(&extand_decimal_1, &extand_decimal_2);
    // //Арифметика в зависмости от знаков
    if ((value_1_sign == value_2_sign) && value_1_sign) {
      if (is_less_mantis(extand_decimal_1, extand_decimal_2)) {
        bitwise_sub(extand_decimal_2, extand_decimal_1, &extand_result);
        extand_result.sign = 0;
      } else {
        bitwise_sub(extand_decimal_1, extand_decimal_2, &extand_result);
        extand_result.sign = value_1_sign;
      }
    } else if ((value_1_sign == value_2_sign) && !value_1_sign) {
      if (is_less_mantis(extand_decimal_1, extand_decimal_2)) {
        bitwise_sub(extand_decimal_2, extand_decimal_1, &extand_result);
        extand_result.sign = 1;
      } else {
        bitwise_sub(extand_decimal_1, extand_decimal_2, &extand_result);
        extand_result.sign = 0;
      }
    } else {
      bitwise_add(extand_decimal_1, extand_decimal_2, &extand_result);
      extand_result.sign = value_1_sign;
    }

    status = tidy_work_decimal(&extand_result);
    // Перевод результата арифметики расширенного децимала и проверка ошибок
    *result = work_to_initial(extand_result);
  } else {
    status = 1;
  }
  return status;
}