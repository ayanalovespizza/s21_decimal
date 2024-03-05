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
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int err = 0;
    if(s21_correct_decimal(value_1) && s21_correct_decimal(value_2) && result != NULL){
        int scale_1 = (value_1.bits[3] & SCALE) >> 16;
        int scale_2 = (value_2.bits[3] & SCALE) >> 16;
        int sign_1 = (value_1.bits[3] & MINUS ? 1 : 0);
        int sign_2 = (value_2.bits[3] & MINUS ? 1 : 0);

//        int s21_mul_main


    }else{
        err = 1;
    }
    return err;
}


int s21_mul_main(s21_decimal value_1, s21_decimal value_2,s21_decimal *result) {

    int err = 0;

}


int s21_mul_overflow_check(s21_decimal value_1, s21_decimal value_2){
    int overflow = 0;

    s21_decimal truncated_1 = {0}, truncated_2 = {0};  // Целая часть
    s21_truncate(value_1, &truncated_1);
    s21_truncate(value_2, &truncated_2);

    s21_decimal fractional_1 = {0}, fractional_2 = {0};  // Дробная часть
    s21_sub(value_1, truncated_1, &fractional_1);
    s21_sub(value_2, truncated_2, &fractional_2);


    return overflow;
}