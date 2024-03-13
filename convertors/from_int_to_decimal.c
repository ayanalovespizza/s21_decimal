//#include "../s21_decimal.h"
//#include <stdio.h>
//#include <limits.h>
//#include <math.h>
//
///**
// * @brief Преобразователь из int в decimal
// *
// * @return 0 - OK
// *         1 - ошибка конвертации
// */
//
//int s21_from_int_to_decimal(int src, s21_decimal *dst) {
//    int flag = 0;
//    if(src <0){
//        s21_set_sign(dst);
//        src*=-1;
//    }
//    dst->bits[0] = dst->bits[0] | src;
//    if(dst->bits[0] != src){
//        flag=1;
//    }
//    return flag;
//}
