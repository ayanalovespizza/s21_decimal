#include "s21_decimal.h"
#include <math.h>
// перевод из исходного decimal в рабочий
s21_work_decimal initial_to_work(s21_decimal decimal) {
  s21_work_decimal result;
  work_make_null(&result);
  result.bits[0] = decimal.bits[0] & MAX4BITE;// Объеденить в цикл
  result.bits[1] = decimal.bits[1] & MAX4BITE;
  result.bits[2] = decimal.bits[2] & MAX4BITE;
  result.scale = (decimal.bits[3] & SCALE) >> 16;
  result.sign = (decimal.bits[3] & MINUS) >> 31;
  return result;
}

// перевод из рабочего decimala в исходный
s21_decimal work_to_initial(s21_work_decimal decimal) {
  s21_decimal result;
  initial_make_null(&result);
  result.bits[0] = decimal.bits[0] & MAX4BITE;// Объеденить в цикл
  result.bits[1] = decimal.bits[1] & MAX4BITE;
  result.bits[2] = decimal.bits[2] & MAX4BITE;
  result.bits[3] |= (decimal.scale << 16);
  result.bits[3] |= (decimal.sign << 16);
  return result;
}

// работа с переполнением
int is_overflow(s21_work_decimal *value) {
  int overflow = 0;
  int result = 0;

  for (int i = 0; i < 7; i++) {
    value->bits[i] += overflow;
    overflow = (value->bits[i] >> 32);
    value->bits[i] &= MAX4BITE;
  }

  if (overflow) result = 1;

  return result;
}

// увеличивание scale
int pointleft(s21_work_decimal *value) {
  s21_work_decimal temp_value = *value;
  for (int i = 0; i < 7; i++) {
    temp_value.bits[i] *= 10;
  }
  temp_value.scale++;
  int overflowed = 0;

  if (is_overflow(&temp_value)) {
    overflowed = 1;
  } else {
    *value = temp_value;
  }
  return overflowed;
}

// уменьшение scale
long int pointright(s21_work_decimal *value) {
  long int remainder = 0;
  for (int i = 6; i >= 0; i--) {
    value->bits[i] += remainder << 32;
    remainder = value->bits[i] % 10;
    value->bits[i] /= 10;
  }

  value->scale -= 1;

  return remainder;
}


// приравнивание scale
void point_to_normal(s21_work_decimal *value_1, s21_work_decimal *value_2) {
  if (value_1->scale < value_2->scale) {
    while (value_1->scale != value_2->scale && !pointleft(value_1))
      ;
  } else if (value_1->scale > value_2->scale) {
    while (value_1->scale != value_2->scale && !pointleft(value_2))
      ;
  }
}

//Сравнение мантис расширенного децимала
//Если res = 0, то мантиса первого числа не меньше 
//Если res = 1, то мантиса первого меньше 
int is_less_mantis(s21_work_decimal value_1, s21_work_decimal value_2){
int res = 0; 
for(int i = 6; i >= 0;i--){
  if(value_1.bits[i]<value_2.bits[i]){
    res = 1;
    break;
  }
}
return res;
}

//функция обнуления расширенного децимала
void work_make_null(s21_work_decimal* value){
 for(int i = 0; i<7;i++){
    value->bits[i] = 0;
  }
}
//функция обнуления обычного децимала
void initial_make_null(s21_decimal* value){
 for(int i = 0; i<4;i++){
    value->bits[i] = 0;
  }
} 



void tidy_work_decimal(s21_work_decimal* value){
    int last_digit = 0, full_remainder = 0;
    int mantis_longer = check_mantis(*value) ;
    if(mantis_longer&&value->scale>0){
        last_digit = pointright(value);
        full_remainder += last_digit;
        mantis_longer = check_mantis(*value);
    }
    work_bank_round(value,last_digit,full_remainder);
}

int check_mantis(s21_work_decimal value){
    int result = 0;
    if(value.bits[3]!=0||value.bits[4]!=0||value.bits[5]!=0||value.bits[6]!=0){
        result=1;
    }
    return result;
}

void work_bank_round(s21_work_decimal* value,int last_digit, int full_remainder){
    if (last_digit != 5) {
        if (last_digit > 5) {
            value->bits[0]++;
            is_overflow(value);
        }
    } else {
        if (full_remainder > 5) {
            value->bits[0]++;
            is_overflow(value);
        } else {
            if (value->bits[0] % 2 == 1) {
                value->bits[0]++;
                is_overflow(value);
            }
        }
    }
}

