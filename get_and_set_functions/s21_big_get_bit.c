#include <stdio.h>
#include "../s21_decimal.h"

int s21_big_get_bit(s21_work_decimal* value, int position_bit){
    int result = -1;
    int value_bit = 1;
    int array_position = 0;
        array_position = position_bit / 32;
        position_bit = (position_bit % 32);
        value_bit = value_bit<<position_bit;
        value_bit = value_bit&(value->bits[array_position]);
        result = value_bit>>position_bit;
    return result;
}

