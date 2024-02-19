#include "../s21_decimal.h"
#include "limits.h"

/**
 * @brief Преобразователь из int в decimal
 *
 * @return 0 - OK
 *         1 - ошибка конвертации
 */


int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int temp_arr[32] = {0}; // массив для хранения 2 представления int
    int ost;
    int i = 0;
    int flag = 0;

    if(src <0 && src!= INT_MIN){
        dst->bits[3] |=  (1<< 31);
        src*=-1;
    }else if( src == INT_MIN){
        dst->bits[0] = 1 << 31;
        dst->bits[3] = 1 << 31;
        return 0;
    }

    int temp = src;

    while(temp > 0){ // конвертируем 10 в 2
        ost = temp % 2;
        temp_arr[i] = ost;
        i++;
        temp = temp / 2;
    }

    for(int j = 0; j<i; j++){

        temp_arr[j] = temp_arr[j]<<j;
        dst->bits[0] |= temp_arr[j];
    }


    if(dst->bits[0] != src){
        flag=1;
    }


    return flag;
}



