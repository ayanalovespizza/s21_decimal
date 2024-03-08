#include "../s21_decimal.h"

/**
 * @brief Деление
 *
 * @warning При получении чисел, не вмещающихся в мантису
 * (bits[0], bits[1], bits[2]), использовать банковское округеление
 *
 * @return 0 - OK
 *         1 - число слишком велико или равно бесконечности
 *         2 - число слишком мало или равно отрицательной бесконечности
 *         3 - деление на 0
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {

}