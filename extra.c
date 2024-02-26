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

  if (overflow == 0) result = 1;

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
int pointright(s21_work_decimal *value) {
  long int remainder = 0;
  for (int i = 6; i >= 0; i--) {
    value->bits[i] += remainder << 32;
    remainder = value->bits[i] % 10;
    value->bits[i] /= 10;
  }

  value->scale -= 1;

  return remainder;
}

// нормализация расширенного decimal к исходному
// int normalize(s21_work_decimal, const int summ, const int sign) {}

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
int is_less_mantiss(s21_work_decimal value_1, s21_work_decimal value_2){
int res = 0; 
for(int i = 6; i<=0;i--){
  if((unsigned)value_1.bits[i]<(unsigned)value_2.bits[i]){
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


// Функции Ирины для фулл работы нормализация чисел для арифметики
void s21_normalized_scales_decimal(s21_work_decimal *a, s21_work_decimal *b,
                                   int overflow) {
  int scale_diff = (int)a->scale - (int)b->scale;
  s21_work_decimal *rescalable = scale_diff > 0 ? b : a;
  s21_increase_scale_with_check(rescalable, abs(scale_diff), overflow);
}

void s21_increase_scale(s21_work_decimal *c, int diff) {
  c->scale += diff;
  while (diff > 0) {
    uint64_t carry = 0;
    for (int i = 0; i < 6; i++) {
      uint64_t sum = c->bits[i] * 10 + carry;
      c->bits[i] = sum & MAX4BITE;
      carry = sum >> 32;
    }
    diff--;
  }
}

void s21_increase_scale_with_check(s21_work_decimal *c, int diff,
                                   int check_overflow) {
  c->scale += diff;
  int local_diff = diff;

  while (diff > 0) {
    uint64_t carry = 0;
    for (int i = 0; i < 6; i++) {
      uint64_t sum = c->bits[i] * 10 + carry;
      c->bits[i] = sum & MAX4BITE;
      carry = sum >> 32;
    }
    diff--;
    local_diff--;

    if (check_overflow && s21_overflow(*c)) {
      diff = 0;
      s21_big_div_ten(c);
      local_diff++;
    }
  }
  if (check_overflow) c->scale -= local_diff;
}

int s21_overflow(s21_work_decimal c) { return c.bits[3] || c.bits[4] || c.bits[5]; }


int s21_big_div_ten(s21_work_decimal *value) {
  int error = 0;
  unsigned long long residue = 0;  // остаток от деления
  unsigned long long x = 0;
  for (int i = 5; i >= 0; --i) {
    x = value->bits[i];
    x += (residue << 32);  // сдвигаем остаток на 64 бита
    residue = x % 10;
    x /= 10;
    value->bits[i] = x;
  }
  return error;
}

int s21_is_even(s21_decimal num) {
  int res = 0;

  if ((num.bits[0] & 1) == 0) res = 1;

  return res;
}