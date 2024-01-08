#include "s21_decimal.h"

// перевод из исходного decimal в рабочий
s21_work_decimal inital_to_work(s21_decimal decimal) {
  s21_work_decimal result;
  result.bits[0] = decimal.bits[0] & MAX4BITE;
  result.bits[1] = decimal.bits[1] & MAX4BITE;
  result.bits[2] = decimal.bits[2] & MAX4BITE;
  result.bits[3] = 0;
  result.bits[4] = 0;
  result.bits[5] = 0;
  result.bits[6] = 0;
  result.scale = (decimal.bits[3] & SC) >> 16;

  return result;
}

// перевод из рабочего decimala в исходный
s21_decimal work_to_initial(s21_work_decimal decimal) {
  s21_decimal result;
  result.bits[0] = decimal.bits[0] & MAX4BITE;
  result.bits[1] = decimal.bits[1] & MAX4BITE;
  result.bits[2] = decimal.bits[2] & MAX4BITE;
  result.bits[3] = 0;
  result.bits[3] |= (decimal.scale << 16);

  return result;
}

// работа с переполнением
int is_overflow(s21_work_decimal *value) {
  int overflow = 0;
  int result;

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
int normalize(s21_work_decimal, const int summ, const int sign) {}

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