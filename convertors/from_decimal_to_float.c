#include "../s21_decimal.h"
#define SCALE 0x00ff0000
#include <stdio.h>
#include <string.h>
#include <math.h>
/**
 * @brief Преобразователь из decimal в float
 *
 * @return 0 - OK
 *         1 - ошибка конвертации
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst){
    int scale =  (src.bits[3] & SCALE) >> 16;
    char str[100];
    sprintf(str,"%d",src.bits[0]);
    int len = strlen(str);

    if(len == 7){
        *dst = src.bits[0] / pow(10,7-scale);
    }else{
        *dst = src.bits[0] / pow(10, scale);
    }

    return 0;

}
