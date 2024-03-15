#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MINUS 0x80000000     // 10000000 00000000 00000000 00000000
#define SCALE 0x00ff0000     // 00000000 11111111 00000000 00000000
#define MAX4BITE 0xffffffff  // 11111111 11111111 11111111 11111111
#define BIT_IS_NULL 0x000000000
#define INCORRECT 0b01111111000000001111111111111111

#define FALSE 0
#define TRUE 1

/*
bits[0], bits[1], и bits[2] содержат младшие, средние и старшие 32 бита
96-разрядного целого числа соответственно bits[3] содержит коэффициент
масштабирования и знак, и состоит из следующих частей:

- биты от 0 до 15, младшее слово, не используются и должны быть равны нулю
- биты с 16 по 23 должны содержать показатель степени от 0 до 28, который
указывает степень 10 для разделения целого числа
- биты с 24 по 30 не используются и должны быть равны нулю
- бит 31 содержит знак: 0 означает положительный, 1 означает отрицательный
*/
typedef struct {
  unsigned bits[4];
} s21_decimal;

// реализуем decimal через расширенный decimal
typedef struct {
  uint64_t bits[7];
  uint16_t scale;
  uint32_t sign;
} s21_work_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// helpers
void work_make_null(s21_work_decimal *value);
void initial_make_null(s21_decimal *value);

s21_work_decimal initial_to_work(s21_decimal decimal);
s21_decimal work_to_initial(s21_work_decimal decimal);

int is_overflow(s21_work_decimal *value);
int pointleft(s21_work_decimal *value);
int pointright(s21_work_decimal *value);
void point_to_normal(s21_work_decimal *value_1, s21_work_decimal *value_2);

int is_less_mantis(s21_work_decimal value_1, s21_work_decimal value_2);
int tidy_work_decimal(s21_work_decimal *value);
int check_mantis(s21_work_decimal value);
void work_bank_round(s21_work_decimal *value, int last_digit,
                     int full_remainder);

int s21_big_get_bit(s21_work_decimal value, int position_bit);
void s21_big_set_bit(s21_work_decimal *value, int position_bit,
                     unsigned value_bit);
void s21_set_sign(s21_decimal *value);
void s21_set_bit(s21_decimal *num, int index, int bit);

void bitwise_add(s21_work_decimal value_1, s21_work_decimal value_2,
                 s21_work_decimal *result);
void bitwise_sub(s21_work_decimal value_1, s21_work_decimal value_2,
                 s21_work_decimal *result);
int mantis_is_null(s21_work_decimal value);
int is_correct_decimal(s21_decimal value);
int is_infinity(s21_work_decimal value);
int is_too_small(s21_work_decimal value);
#endif