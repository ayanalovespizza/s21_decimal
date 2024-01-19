#include "../s21_decimal.h"

void s21_big_set_sign(s21_work_decimal* value){
    value->bits[7]|=MINUS;
}

