#include "../s21_decimal.h"

/**
 * @brief Сложение
 *
 * @warning При получении чисел, не вмещающихся в мантису
 * (bits[0], bits[1], bits[2]), использовать банковское округеление
 *
 * @return 0 - OK
 *         1 - число слишком велико или равно бесконечности
 *         2 - число слишком мало или равно отрицательной бесконечности
 */

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//Конвертировать из decimal в work_decimal
  s21_work_decimal extand_decimal_1 = initial_to_work(value_1);
  s21_work_decimal extand_decimal_2 = initial_to_work(value_2);

}

void bitwise_add(s21_work_decimal value_1,s21_work_decimal value_2,s21_work_decimal* result){
    
}