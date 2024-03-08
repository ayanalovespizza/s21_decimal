#include <stdio.h>

#include "../s21_decimal.h"

int s21_big_div_ten(s21_work_decimal* value) {
  int error = 0;
  unsigned long long residue = 0;  // остаток от деления
  unsigned long long x = 0;
  for (int i = 6; i >= 0; --i) {
    x = value->bits[i];
    x += (residue << 32);  // сдвигаем остаток на 64 бита
    residue = x % 10;
    x /= 10;
    value->bits[i] = x;
  }
  return error;
}

int s21_overflow(s21_work_decimal c) {
  return c.bits[3] || c.bits[4] || c.bits[5] || c.bits[6];
}

int big_shift_left(s21_work_decimal* number) {
  int is_overflow = s21_big_get_bit(*number, (32 * 6) - 1);
  for (int i = (32 * 6) - 1; i >= 0; i--) {
    if (i != 0) {
      s21_big_set_bit(number, i, s21_big_get_bit(*number, i - 1));
    } else {
      s21_big_set_bit(number, i, 0);
    }
  }
  return is_overflow;
}

void bitwise_add(s21_work_decimal value_1, s21_work_decimal value_2,
                 s21_work_decimal* result) {
  unsigned memo = 0;
  for (int i = 0; i < 32 * 6; i++) {
    unsigned result_bit =
        s21_big_get_bit(value_1, i) + s21_big_get_bit(value_2, i) + memo;
    memo = result_bit / 2;
    result_bit = result_bit % 2;
    s21_big_set_bit(result, i, result_bit);
  }
}

void big_mul(s21_work_decimal value_1, s21_work_decimal value_2,
             s21_work_decimal* result) {
  s21_work_decimal temp_value = {{0, 0, 0, 0, 0, 0}, 0};
  s21_work_decimal temp_result = {{0, 0, 0, 0, 0, 0}, 0};

  unsigned int bit = 0;

  for (int i = 0; i < (32 * 6); i++) {
    temp_value = value_1;
    bit = s21_big_get_bit(value_2, i);
    if (bit == 1) {
      for (int j = i; j > 0; j--) {
        big_shift_left(&temp_value);
      }
      bitwise_add(temp_result, temp_value, &temp_result);
    }
  }
  *result = temp_result;
}

/**
 * @brief Умножение
 *
 * @warning При получении чисел, не вмещающихся в мантису
 * (bits[0], bits[1], bits[2]), использовать банковское округеление
 *
 * @return 0 - OK
 *         1 - число слишком велико или равно бесконечности
 *         2 - число слишком мало или равно отрицательной бесконечности
 */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int status = 0;

  // проверка на нули
  s21_decimal dec_null = {0, 0, 0, 0};
  if (s21_is_equal(value_1, dec_null) || s21_is_equal(value_2, dec_null)) {
    *result = dec_null;

  } else {
    // проверка на знаки
    int sign = 0;
    if ((value_1.bits[3] & MINUS) != (value_2.bits[3] & MINUS)) {
      sign = 1;
    } else {
      sign = 0;
    }
    // перевод в рабочий децимал
    s21_work_decimal value_1_work = initial_to_work(value_1);
    s21_work_decimal value_2_work = initial_to_work(value_2);

    s21_work_decimal result_work = {{0, 0, 0, 0, 0, 0, 0}, 0};

    // вычисление битов рабочего результата по мега-формуле
    big_mul(value_1_work, value_2_work, &result_work);

    // result_work.bits[0] = value_2_work.bits[0] * value_1_work.bits[0];
    // result_work.bits[1] = value_2_work.bits[0] * value_1_work.bits[1] +
    //                       value_2_work.bits[1] * value_1_work.bits[0];
    // result_work.bits[2] = value_2_work.bits[0] * value_1_work.bits[2] +
    //                       value_2_work.bits[1] * value_1_work.bits[1] +
    //                       value_2_work.bits[2] * value_1_work.bits[0];
    // result_work.bits[3] = value_2_work.bits[1] * value_1_work.bits[2] +
    //                       value_2_work.bits[2] * value_1_work.bits[1];
    // result_work.bits[4] = value_2_work.bits[2] * value_1_work.bits[2];

    result_work.scale = ((value_1.bits[3] & SCALE) >> 16) +
                        ((value_2.bits[3] & SCALE) >> 16);  // суммируем скейлы

    // printf("\n\nПосле умножения\n");

    is_overflow(&result_work);

    // printf("bits[0]: %llx\n", result_work.bits[0]);
    // printf("bits[1]: %llx\n", result_work.bits[1]);
    // printf("bits[2]: %llx\n", result_work.bits[2]);
    // printf("bits[3]: %llx\n", result_work.bits[3]);
    // printf("bits[4]: %llx\n", result_work.bits[4]);
    // printf("bits[5]: %llx\n", result_work.bits[5]);
    // printf("bits[6]: %llx\n", result_work.bits[6]);
    // printf("scale: %x\n\n", result_work.scale);

    // int zalupa = 0;
    // int last_digit = 0, full_remainder = 0;
    // for (int i = 6; i > 2; i--) {
    //   while (result_work.bits[i] != 0) {
    //     last_digit = pointright(&result_work);
    //     full_remainder += last_digit;
    //     zalupa++;
    //   }
    // }
    // printf("\n\n zalupa: %d\n\n", zalupa);

    // if (zalupa > 0) {
    //   if (last_digit != 5) {
    //     if (last_digit > 5) {
    //       result_work.bits[0]++;
    //       is_overflow(&result_work);
    //     }
    //   } else {
    //     if (full_remainder > 5) {
    //       result_work.bits[0]++;
    //       is_overflow(&result_work);
    //     } else {
    //       if (result_work.bits[0] % 2 == 1) {
    //         result_work.bits[0]++;
    //         is_overflow(&result_work);
    //       }
    //     }
    //   }
    // }

    tidy_work_decimal(&result_work);

    *result = work_to_initial(result_work);
    if (sign) {
      result->bits[3] |= MINUS;
    }
  }

  return status;
}