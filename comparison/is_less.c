#include "../s21_decimal.h"

// <
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;

  if ((value_1.bits[3] & MINUS) < (value_2.bits[3] & MINUS) ||
      s21_is_equal(value_1, value_2))
    result = 0;

  else if ((value_1.bits[3] & MINUS) > (value_2.bits[3] & MINUS))
    result = 1;

  else {
    s21_work_decimal value_1_work, value_2_work;

    value_1_work = initial_to_work(value_1);
    value_2_work = initial_to_work(value_2);

    point_to_normal(&value_1_work, &value_2_work);

    for (int i = 2; i >= 0; i--) {
      if (value_1_work.bits[i] < value_2_work.bits[i])
        result = 1;
      else if (value_1_work.bits[i] > value_2_work.bits[i])
        result = 0;
    }

    if ((value_1.bits[3] & MINUS) && (value_2.bits[3] & MINUS)) {
      if (result == 1)
        result = 0;
      else
        result = 1;
    }
  }

  return result;
}