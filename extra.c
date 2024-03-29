#include "s21_decimal.h"

void work_make_null(s21_work_decimal *value) {
  for (int i = 0; i < 7; i++) {
    value->bits[i] = 0;
  }
}

// перевод из исходного decimal в рабочий
s21_work_decimal initial_to_work(s21_decimal decimal) {
  s21_work_decimal result = {{0, 0, 0, 0, 0, 0, 0}, 0};
  result.bits[0] = decimal.bits[0] & MAX4BITE;
  result.bits[1] = decimal.bits[1] & MAX4BITE;
  result.bits[2] = decimal.bits[2] & MAX4BITE;
  result.bits[3] = 0;
  result.bits[4] = 0;
  result.bits[5] = 0;
  result.bits[6] = 0;
  result.scale = (decimal.bits[3] & SCALE) >> 16;

  return result;
}

// перевод из рабочего decimala в исходный
s21_decimal work_to_initial(s21_work_decimal decimal) {
  s21_decimal result = {0, 0, 0, 0};
  result.bits[0] = decimal.bits[0] & MAX4BITE;
  result.bits[1] = decimal.bits[1] & MAX4BITE;
  result.bits[2] = decimal.bits[2] & MAX4BITE;
  result.bits[3] = 0;
  result.bits[3] |= (decimal.scale << 16);

  return result;
}

// работа с переполнением
int is_overflow(s21_work_decimal *value) {
  uint32_t overflow = 0;
  int result = 0;

  for (int i = 0; i < 7; i++) {
    value->bits[i] += overflow;
    overflow = (value->bits[i] >> 32);
    // printf("overflow bits[%d]= %x\n", i, overflow);
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

int s21_correct_decimal(s21_decimal dst) {
  int flag_error = 1;
  int scale = (dst.bits[3] & SCALE) >> 16;

  if (BIT_IS_NULL != (dst.bits[3] &= INCORRECT)) {
    flag_error = 0;
  }

  if (scale < 0 || scale > 28) {
    flag_error = 0;
  }

  return flag_error;
}

void tidy_work_decimal(s21_work_decimal *value) {
  int last_digit = 0, full_remainder = 0;
  int mantis_longer = check_mantis(*value);
  while (mantis_longer && (value->scale > 0)) {
    last_digit = pointright(value);
    full_remainder += last_digit;
    mantis_longer = check_mantis(*value);
  }
  work_bank_round(value, last_digit, full_remainder);
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