#include "../s21_decimal.h"

/**
 * @brief Сложение
 *
 * @warning При получении чисел, не вмещающихся в мантису
 * (bits[0], bits[1], bits[2]), использовать банковское округеление
 *
 * @return 0 - OK
 *         1 - число слишком велико или равно бесконечности
 *         2 - число слишком мало или равно отрицательной бесконечности
 */

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
 //Конвертация из decimal в work_decimal
  int status = 0; 
  s21_work_decimal extand_decimal_1 = initial_to_work(value_1);
  s21_work_decimal extand_decimal_2 = initial_to_work(value_2);
  s21_work_decimal extand_result;
  unsigned int value_1_sign = 0;
  unsigned int value_2_sign = 0;
  //Зануление расширенного результуруемого децимала
  for(int i = 0; i<7;i++){
    extand_result.bits[i] = 0;
  }
  //Cохранение знаков
  value_1_sign = extand_decimal_1.sign;
  value_2_sign = extand_decimal_2.sign;
  //Cохранение результирующего масштаба
  if(extand_decimal_1.scale - extand_decimal_2.scale <= 0){
    extand_result.scale = extand_decimal_2.scale;
  }else{
    extand_result.scale = extand_decimal_1.scale;
  }
  //Нормализация чисел для арифметики
   point_to_normal(&extand_decimal_1,&extand_decimal_2);
  //Арифметика в зависмости от знаков
   if(value_1_sign == value_2_sign){
    bitwise_add(extand_decimal_1,extand_decimal_2,&extand_result);
    extand_result.sign = value_1_sign;
   }//Сравниваем мантисы
   else if(is_less_mantiss(extand_decimal_1, extand_decimal_2)){
    bitwise_sub(extand_decimal_2,extand_decimal_1,&extand_result);
    extand_result.sign = value_2_sign;
   }
   else{
    bitwise_sub(extand_decimal_1,extand_decimal_2,&extand_result);
    extand_result.sign = value_1_sign;
   }
  //Перевод результата арифметики расширенного децимала и проверка ошибок
   *result = work_to_initial(extand_result);
    return status;
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
