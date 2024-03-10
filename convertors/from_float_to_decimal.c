#include "../s21_decimal.h"

#define s21_MAXDEC pow(2, 96) - 1
#define MAX_SCALE 28

typedef union {
  float f;
  uint32_t i;
} FloatIntUnion;

void s21_scale_adjust(double *temp_number, int *scale, int *scale_diff,
                      FloatIntUnion mantissa);
void s21_round_for_float(double *temp_number);
void s21_float_to_bin(double *temp_number, FloatIntUnion mantissa,
                      s21_decimal *dst);

/**
 * @brief преобразователь из floar в decimal
 *
 * @warning Если числа слишком малы, то вернуть ошибку 1 и значение, равное 0;
 *          Если числа слишком велики или равны бесконечности, вернуть ошибку;
 *          При обработке числа с типом float преобразовывать все содеражищиеся
 *            в нем значимые десятичные цифры.Если таких цифр больше 7, то
 *            значение округляется к ближайшему, у которого не больше 7 значимых
 *            цифр
 *
 * @return 0 - OK
 *         1 - ошибка конвертации
 */
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  FloatIntUnion u;
  int scale = 0;

  if (dst == NULL || (fabs(src) > s21_MAXDEC) || (fabs(src) == INFINITY) ||
      isnan(fabs(src))) {
    return 1;
  } else if (fabs(src) > 0 && fabs(src) < 1e-28) {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
    return 1;
  }

  if (src == 0.0) {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
    return 0;
  }

  if (src < 0) {
    dst->bits[3] |= MINUS;
    src *= -1;
  }
  u.f = src;

  int exp = ((u.i >> 23) & 0XFF) - 127;

  double temp_num = (double)u.f;

  if (exp < -94 || exp > 96) {
    return 1;
  }

  int scale_diff = 0;

  s21_scale_adjust(&temp_num, &scale, &scale_diff, u);
  s21_round_for_float(&temp_num);
  s21_float_to_bin(&temp_num, u, dst);
  dst->bits[3] |= (scale << 16);

  if (scale_diff > 0) {
    s21_decimal ten = {{0xA, 0x0, 0x0, 0x0}};
    for (int i = scale_diff; i > 0; i--) {
      s21_mul(*dst, ten, dst);
    }
  }

  return 0;
}

void s21_scale_adjust(double *temp_number, int *scale, int *scale_diff,
                      FloatIntUnion mantissa) {
  int scale_whole_part = 0;
  double temp_whole_part = *temp_number;

  while ((*scale < 28) && (((*temp_number < 999999) && (mantissa.f >= 1)) ||
                           ((*temp_number < 1000000) && (mantissa.f < 1)))) {
    *temp_number *= 10;
    (*scale)++;
  }  // переводит дробное в целое

  if (*scale == 0) {
    while (temp_whole_part > 1) {
      temp_whole_part /= 10;
      scale_whole_part++;
    }  // считает значемые числа, если число пришло с 7 или более знаками и не
       // было изменено в цикле
  }

  while (scale_whole_part > 7) {
    *temp_number /= 10;
    scale_whole_part--;
    (*scale_diff)++;
  }  // изменяет число оставляя только 7 чисел

  while (((int)fmod(*temp_number, 10) == 0) && (*scale > 0) &&
         ((int)fmod(*temp_number * 10, 10) <= 5)) {
    *temp_number /= 10;
    (*scale)--;
  }  // берет остаток от числа , например 150 :10 = 0, дальше умножает этот
     // остаток на 10, если он <= 5,
  // то точность не теряется, 159 % 10 = 15.9 , 15.9 * 10 = 159. 159 % 10 = 9 !
  // <= 5
}

void s21_round_for_float(double *temp_number) {
  double mantissa_double_temp = *temp_number;
  long int whole_part = *temp_number;

  whole_part *= 100000000;
  mantissa_double_temp *= 100000000;

  long int fraction_part = mantissa_double_temp;
  fraction_part -= whole_part;

  if (fraction_part == 50000000) {
    long int digit = whole_part / 100000000;

    digit -= (whole_part / 1000000000) * 10;

    if ((digit % 2) == 1) {
      *temp_number += 1.0;
    }
  }
  if (fraction_part != 50000000) {
    *temp_number = roundl(*temp_number);
  }
}

void s21_float_to_bin(double *temp_number, FloatIntUnion mantissa,
                      s21_decimal *dst) {
  mantissa.f = *temp_number;

  int exp = ((mantissa.i & ~(1u << 31)) >> 23) - 127;

  dst->bits[exp / 32] |= (1u << (exp % 32));

  for (int i = exp - 1, j = 22; i >= 0 && j >= 0; i--, j--) {
    if ((mantissa.i & (1 << j)) != 0) {
      dst->bits[i / 32] |= (1u << (i % 32));
    }
  }
}