#include "../s21_decimal.h"

void s21_set_sign(s21_decimal* value){
    value->bits[3]|=MINUS;
}

