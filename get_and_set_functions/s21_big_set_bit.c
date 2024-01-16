#include <stdio.h>
#include "../s21_decimal.h"

     
void s21_big_set_bit(s21_work_decimal* value,int position_bit,unsigned value_bit){
        int array_position = 0;
        int temp = value_bit;
        array_position = position_bit / 32;
        position_bit = (position_bit % 32) - 1;
        value_bit = value_bit << position_bit;
        if(temp == 1){
          value->bits[array_position] = value->bits[array_position] | value_bit;
        }
        else{
          value->bits[array_position] = (value->bits[array_position])&(~value_bit);
        }    
}
