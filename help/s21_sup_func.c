#include "../s21_decimal.h"

#define BIT_IS_NULL 0x000000000
#define INCORRECT 0b01111111000000001111111111111111



int s21_correct_decimal(s21_decimal dst){
    int err = 1;
    int scale = (dst.bits[3] & SCALE) >> 16;

    if(BIT_IS_NULL != (dst.bits[3] &= INCORRECT )){
        err = 0;
    }

    if(scale < 0 || scale > 28){
        err = 0;
    }


    return  err;
}

//
//void s21_normalize_scale(s21_decimal *a, s21_decimal *b, int overflow){
//
//
//}

s21_work_decimal s21_init_work_decimal(s21_decimal decimal){
    s21_work_decimal new_decimal = {0};

    new_decimal.bits[0] = decimal.bits[0];
    new_decimal.bits[1] = decimal.bits[1];
    new_decimal.bits[2] = decimal.bits[2];
    new_decimal.bits[3] =0;
    new_decimal.bits[4] =0;
    new_decimal.bits[4] =0;

    new_decimal.scale = (decimal.bits[3] & SCALE ) >> 16;
    new_decimal.sign = (decimal.bits[3] & MINUS ? 1 : 0);
}