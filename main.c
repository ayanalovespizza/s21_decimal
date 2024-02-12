#include <stdio.h>
#include <string.h>
#include "s21_decimal.h"

int main() {
  s21_decimal decimal1;
  s21_decimal decimal2 ;
  s21_work_decimal work_1;
  s21_work_decimal work_2;
  s21_work_decimal result_arithmetic;
  memset(&decimal1, 0, sizeof(s21_decimal));
  memset(&decimal2, 0, sizeof(s21_decimal));
  memset(&work_1,0, sizeof(s21_work_decimal));
  memset(&work_2,0, sizeof(s21_work_decimal));
  memset(&result_arithmetic,0, sizeof(s21_work_decimal));
  int src_1 = 500000000;
  int src_2 = 300;
  s21_from_int_to_decimal(src_1,&decimal1);
  s21_from_int_to_decimal(src_2,&decimal2);
  work_1 = initial_to_work(decimal1);
  work_2 = initial_to_work(decimal2);
  printf("work1_1\n__________________________\n");
  for(int i=0;i<7;i++){
  printf("%d\n",work_1.bits[i]);
  }
  printf("work1_2\n__________________________\n");
  for(int i=0;i<7;i++){
  printf("%d\n",work_2.bits[i]);
  }
  bitwise_sub(work_1,work_2,&result_arithmetic);
  printf("result_arithmetic\n__________________________\n");
  for(int i=0;i<7;i++){
  printf("%d\n",result_arithmetic.bits[i]);
  }
  printf("result_arithmetic\n__________________________\n");
  memset(&result_arithmetic,0, sizeof(s21_work_decimal));
  bitwise_add(work_1,work_2,&result_arithmetic);
  for(int i=0;i<7;i++){
  printf("%d\n",result_arithmetic.bits[i]);
  }
  return 0;
}

void bitwise_sub(s21_work_decimal value_1,s21_work_decimal value_2,s21_work_decimal* result){
  unsigned memo = 0;
    for(int i = 0; i <32*6;i++){
     int result_bit = s21_big_get_bit(value_1,i)-s21_big_get_bit(value_2,i)-memo;
     if(result_bit<0){
      memo = 1;
     }
     else{
      memo = 0;
     }
     if(result_bit == -1||result_bit==1){
      result_bit = 1;
     }
     s21_big_set_bit(result,i,result_bit);
    }
}

s21_work_decimal initial_to_work(s21_decimal decimal) {
  s21_work_decimal result;
  result.bits[0] = decimal.bits[0] & MAX4BITE;// Объеденить в цикл, 
  result.bits[1] = decimal.bits[1] & MAX4BITE;
  result.bits[2] = decimal.bits[2] & MAX4BITE;
  result.bits[3] = 0;
  result.bits[4] = 0;
  result.bits[5] = 0;
  result.bits[6] = 0;
  result.scale = (decimal.bits[3] & SCALE) >> 16;
  result.sign = (decimal.bits[3] & MINUS) >> 16;
  return result;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int flag = 0;
    if(src <0){
        s21_set_sign(dst);
        src*=-1;
    }
    dst->bits[0] = dst->bits[0] | src;
    if(dst->bits[0] != src){
        flag=1;
    }
    return flag;
}

int s21_big_get_bit(s21_work_decimal value, int position_bit){
    int result = -1;
    int value_bit = 1;
    int array_position = 0;
        array_position = position_bit / 32;
        position_bit = (position_bit % 32);
        value_bit = value_bit<<position_bit;
        value_bit = value_bit&(value.bits[array_position]);
        result = value_bit>>position_bit;
    return result;
}
void s21_set_sign(s21_decimal* value){
    value->bits[3]|=MINUS;
}

void s21_big_set_bit(s21_work_decimal* value,int position_bit,unsigned value_bit){
        int array_position = 0;
        int temp = value_bit;
        array_position = position_bit / 32;
        position_bit = (position_bit % 32);
        value_bit = value_bit << position_bit;
        if(temp == 1){
          value->bits[array_position] = value->bits[array_position] | value_bit;
        }
        else{
          value->bits[array_position] = (value->bits[array_position])&(~value_bit);
        }    
}

void bitwise_add(s21_work_decimal value_1,s21_work_decimal value_2,s21_work_decimal* result){
    unsigned memo = 0;
    for(int i = 0; i <32*6;i++){
     unsigned  result_bit = s21_big_get_bit(value_1,i)+s21_big_get_bit(value_2,i)+memo;
     memo = result_bit /2;
     result_bit = result_bit % 2;
     s21_big_set_bit(result,i,result_bit);
    }
}