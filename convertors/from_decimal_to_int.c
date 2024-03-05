#include "../s21_decimal.h"

/**
 * @brief Преобразователь из decimal в int
 *
 * @warning Если в числе типа decimal есть дробная часть, то ее следует
 *          отбросить (0,9 => 0)
 *
 * @return 0 - OK
 *         1 - ошибка конвертации
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst) {

    int err = 0;

    if(dst == NULL){
        err =  1;
    }else{
        s21_decimal  dec_trunk={0};
        s21_truncate(src, &dec_trunk);

        int sign = (dec_trunk.bits[3] & MINUS) != 0 ? -1 : 1;


        if ((dec_trunk.bits[2] == 0) && (dec_trunk.bits[1] == 0) &&
            (dec_trunk.bits[0] < 2147483648 || (sign == -1  && dec_trunk.bits[0] == 2147483648))) {
            *dst = dec_trunk.bits[0];
            if (sign == -1) {
                (*dst) *= -1;
            }
        } else {
            err = 1;
        }
    }

    return  err;
}