#include "s21_decimal.h"

// функция обнуления расширенного децимала
void work_make_null(s21_work_decimal *value) {
  for (int i = 0; i < 7; i++) {
    value->bits[i] = 0;
  }
}
// функция обнуления обычного децимала
void initial_make_null(s21_decimal *value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}

// перевод из исходного decimal в рабочий
s21_work_decimal initial_to_work(s21_decimal decimal) {
  s21_work_decimal result;
  work_make_null(&result);

  result.bits[0] = decimal.bits[0] & MAX4BITE;
  result.bits[1] = decimal.bits[1] & MAX4BITE;
  result.bits[2] = decimal.bits[2] & MAX4BITE;
  result.scale = (decimal.bits[3] & SCALE) >> 16;
  result.sign = (decimal.bits[3] & MINUS) >> 31;

  return result;
}

// перевод из рабочего decimal в исходный
s21_decimal work_to_initial(s21_work_decimal decimal) {
  s21_decimal result;
  initial_make_null(&result);

  result.bits[0] = decimal.bits[0] & MAX4BITE;
  result.bits[1] = decimal.bits[1] & MAX4BITE;
  result.bits[2] = decimal.bits[2] & MAX4BITE;
  result.bits[3] |= (decimal.scale << 16);
  result.bits[3] = result.bits[3] | (decimal.sign << 31);

  return result;
}

// работа с переполнением
int is_overflow(s21_work_decimal *value) {
  uint32_t overflow = 0;
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

/*
Сравнение мантис расширенного децимала
- если res = 0, то мантиса первого числа не меньше
- если res = 1, то мантиса первого меньше
*/
int is_less_mantis(s21_work_decimal value_1, s21_work_decimal value_2) {
  int res = 0;
  for (int i = 6; i >= 0; i--) {
    if (value_1.bits[i] < value_2.bits[i]) {
      res = 1;
    } else if (value_1.bits[i] > value_2.bits[i] && !res) {
      res = 0;
      break;
    }
  }
  return res;
}

int tidy_work_decimal(s21_work_decimal *value) {
  int last_digit = 0, full_remainder = 0;
  int mantis_longer = check_mantis(*value);
  int status = 0;
  while ((mantis_longer && (value->scale > 0)) || value->scale > 28) {
    last_digit = pointright(value);
    full_remainder += last_digit;
    mantis_longer = check_mantis(*value);
  }
  work_bank_round(value, last_digit, full_remainder);

  if (is_infinity(*value)) {
    if (value->sign) {
      status = 2;
    } else {
      status = 1;
    }
  } else if (is_too_small(*value)) {
    status = 2;  // Слишком маленькое число
  }

  return status;
}

int check_mantis(s21_work_decimal value) {
  int result = 0;
  if (value.bits[3] != 0 || value.bits[4] != 0 || value.bits[5] != 0 ||
      value.bits[6] != 0) {
    result = 1;
  }
  return result;
}

void work_bank_round(s21_work_decimal *value, int last_digit,
                     int full_remainder) {
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

int s21_big_get_bit(s21_work_decimal value, int position_bit) {
  int result = -1;
  unsigned value_bit = 1;
  int array_position = 0;
  array_position = position_bit / 32;
  position_bit = (position_bit % 32);
  value_bit = value_bit << position_bit;
  value_bit = value_bit & (value.bits[array_position]);
  result = value_bit >> position_bit;
  return result;
}

void s21_big_set_bit(s21_work_decimal *value, int position_bit,
                     unsigned value_bit) {
  int array_position = 0;
  int temp = value_bit;
  array_position = position_bit / 32;
  position_bit = (position_bit % 32);
  value_bit = value_bit << position_bit;
  if (temp == 1) {
    value->bits[array_position] = value->bits[array_position] | value_bit;
  } else {
    value->bits[array_position] = (value->bits[array_position]) & (~value_bit);
  }
}

void s21_set_sign(s21_decimal *value) { value->bits[3] |= MINUS; }

void bitwise_add(s21_work_decimal value_1, s21_work_decimal value_2,
                 s21_work_decimal *result) {
  unsigned memo = 0;
  for (int i = 0; i < 32 * 6; i++) {
    unsigned result_bit =
        s21_big_get_bit(value_1, i) + s21_big_get_bit(value_2, i) + memo;
    memo = result_bit / 2;
    result_bit = result_bit % 2;
    s21_big_set_bit(result, i, result_bit);
  }
}

void bitwise_sub(s21_work_decimal value_1, s21_work_decimal value_2,
                 s21_work_decimal *result) {
  unsigned memo = 0;
  for (int i = 0; i < 32 * 6; i++) {
    int result_bit =
        s21_big_get_bit(value_1, i) - s21_big_get_bit(value_2, i) - memo;
    if (result_bit < 0) {
      memo = 1;
    } else {
      memo = 0;
    }
    if (result_bit == -1 || result_bit == 1) {
      result_bit = 1;
    }
    s21_big_set_bit(result, i, result_bit);
  }
}

int mantis_is_null(s21_work_decimal value) {
  int res = 1;
  for (int i = 0; i < 7; i++) {
    if (value.bits[i] != 0) {
      res = 0;
      break;
    }
  }
  return res;
}

int is_correct_decimal(s21_decimal value) {
  int res = 1;
  int scale = (value.bits[3] & SCALE) >> 16;

  if (scale < 0 || scale > 28) {
    res = 0;
  } else if (BIT_IS_NULL != (value.bits[3] &= INCORRECT)) {
    res = 0;
  }

  return res;
}

int is_infinity(s21_work_decimal value) {
  int result = 0;
  if (value.scale <= 0 && check_mantis(value)) {
    result = 1;
  }
  return result;
}

int is_too_small(s21_work_decimal value) {
  int result = 0;
  if (value.scale > 28) {
    result = 1;
  }
  return result;
}

void s21_set_bit(s21_decimal *num, int index, int bit) {
  if (bit == 1)
    num->bits[index / 32] |= (1u << (index % 32));  // установить 1
  else
    num->bits[index / 32] &= ~(1u << (index % 32));  // установить 0
}