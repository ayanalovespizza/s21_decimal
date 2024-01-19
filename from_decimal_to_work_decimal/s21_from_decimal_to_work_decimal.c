#include <stdio.h>
#include "../s21_decimal.h"
void s21_from_decimal_to_work_decimal(s21_decimal value, s21_work_decimal* result_value){
for(int i = 0;i<3;i++){
result_value->bits[i] = result_value->bits[i]|value.bits[i];
}
result_value->bits[7] = result_value->bits[7]|value.bits[3]; 
}