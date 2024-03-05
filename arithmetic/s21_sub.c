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
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {

    int err = 0;

    if (!s21_correct_decimal(value_1) || !s21_correct_decimal(value_2) ||result == NULL){
        err =1 ;
    }else{

    }

}