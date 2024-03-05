#include "../s21_decimal.h"
#include <math.h>
#include <stdio.h>
#include "stdint.h"

#define MAX_SCALE 28

/**
 * @brief преобразователь из floar в decimal
 *
 * @warning Если числа слишком малы, то вернуть ошибку 1 и значение, равное 0;
 *          Если числа слишком велики или равны бесконечности, вернуть ошибку;
 *          При обработке числа с типом float преобразовывать все содеражищиеся
 *            в нем значимые десятичные цифры.Если таких цифр больше 7, то
 *            значение округляется к ближайшему, у которого не больше 7 значимых
 *            цифр
 *
 * @return 0 - OK
 *         1 - ошибка конвертации
 */



int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    s21_decimal temp = {{0, 0, 0, 0}};
    *dst = temp;

    if(src == 0){
        dst->bits[0]  = src;
        return 0;
    }

    if(isinf(src) || isnan(src)){
        return 1;
    }

    if(src<0){
        temp.bits[3] |= MINUS;
        src*= -1;
    }

    *dst  = temp;

    union {
        float f;
        uint32_t u;
    }fu = {fu.f = src};

    // берем uint число и переводим в 2, после берем последние 8 бит
    // конвертируем 8 бит в 10 и из полученого числа вычитаем 127
    // все числа больше чем 95, являются больше чем e+28
    int exp = ((fu.u & ~MINUS)>>23)-127;

    if(exp > 95 || exp < -94){
        return 1;
    }

    int scale = 0;
    for(int i = 0; !(int)src; i++){
        src *= 10;
        scale++;
    }

    while(src < 10000000){
        src *= 10;
        scale++;
    }

    fu.f = src;

    exp = ((fu.u & ~MINUS)>>23)-127;

    if(exp < -94 || scale > 28){
        return 1;
    }

    uint32_t mask = 0x400000;

    if(exp <0){
        exp *=-1;
    }

    temp.bits[exp/32] |= 1 << exp %32;
    exp--;


    while(exp>0){
        temp.bits[exp / 32] |= (fu.u & mask) ? 1 << exp % 32 : 0;
        mask >>= 1;
        exp--;
    }

    temp.bits[3] |= scale << 16;
    *dst = temp;

    return 0;
}