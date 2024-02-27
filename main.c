#include <stdio.h>
#include <string.h>
#include "s21_decimal.h"

int main() {
  s21_decimal result; 
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // 11.556482279746587359354395034
  s21_decimal check = {{0xA759999A, 0xB3174C4F, 0x25574C4F, 0x1B0000}};
  s21_add(decimal1, decimal2, &result);
  for(int i=0;i<4;i++){
  printf("%x\n",result.bits[i]);
  }
  return 0;
}

// void bitwise_sub(s21_work_decimal value_1,s21_work_decimal value_2,s21_work_decimal* result){
//   unsigned memo = 0;
//     for(int i = 0; i <32*6;i++){
//      int result_bit = s21_big_get_bit(value_1,i)-s21_big_get_bit(value_2,i)-memo;
//      if(result_bit<0){
//       memo = 1;
//      }
//      else{
//       memo = 0;
//      }
//      if(result_bit == -1||result_bit==1){
//       result_bit = 1;
//      }
//      s21_big_set_bit(result,i,result_bit);
//     }
// }

// s21_work_decimal initial_to_work(s21_decimal decimal) {
//   s21_work_decimal result;
//   result.bits[0] = decimal.bits[0] & MAX4BITE;// Объеденить в цикл, 
//   result.bits[1] = decimal.bits[1] & MAX4BITE;
//   result.bits[2] = decimal.bits[2] & MAX4BITE;
//   result.bits[3] = 0;
//   result.bits[4] = 0;
//   result.bits[5] = 0;
//   result.bits[6] = 0;
//   result.scale = (decimal.bits[3] & SCALE) >> 16;
//   result.sign = (decimal.bits[3] & MINUS) >> 16;
//   return result;
// }

// int s21_from_int_to_decimal(int src, s21_decimal *dst) {
//     int flag = 0;
//     if(src <0){
//         s21_set_sign(dst);
//         src*=-1;
//     }
//     dst->bits[0] = dst->bits[0] | src;
//     if(dst->bits[0] != src){
//         flag=1;
//     }
//     return flag;
// }

// int s21_big_get_bit(s21_work_decimal value, int position_bit){
//     int result = -1;
//     int value_bit = 1;
//     int array_position = 0;
//         array_position = position_bit / 32;
//         position_bit = (position_bit % 32);
//         value_bit = value_bit<<position_bit;
//         value_bit = value_bit&(value.bits[array_position]);
//         result = value_bit>>position_bit;
//     return result;
// }
// void s21_set_sign(s21_decimal* value){
//     value->bits[3]|=MINUS;
// }

// void s21_big_set_bit(s21_work_decimal* value,int position_bit,unsigned value_bit){
//         int array_position = 0;
//         int temp = value_bit;
//         array_position = position_bit / 32;
//         position_bit = (position_bit % 32);
//         value_bit = value_bit << position_bit;
//         if(temp == 1){
//           value->bits[array_position] = value->bits[array_position] | value_bit;
//         }
//         else{
//           value->bits[array_position] = (value->bits[array_position])&(~value_bit);
//         }    
// }

// void bitwise_add(s21_work_decimal value_1,s21_work_decimal value_2,s21_work_decimal* result){
//     unsigned memo = 0;
//     for(int i = 0; i <32*6;i++){
//      unsigned  result_bit = s21_big_get_bit(value_1,i)+s21_big_get_bit(value_2,i)+memo;
//      memo = result_bit /2;
//      result_bit = result_bit % 2;
//      s21_big_set_bit(result,i,result_bit);
//     }
// }