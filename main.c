#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal res = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal decimal_check = {{0x22D9F0, 0x0, 0x0, 0x190000}};

  float f = 2.28401628E-19;
  s21_from_float_to_decimal(f, &res);

  printf(
      "Бит[0]: %d\n\
Бит[1]: %d\n\
Бит[2]: %d\n\
Бит[3] aka степень: %x\n\n",
      decimal_check.bits[0], decimal_check.bits[1], decimal_check.bits[2],
      decimal_check.bits[3]);

  printf(
      "Бит[0]: %d\n\
Бит[1]: %d\n\
Бит[2]: %d\n\
Бит[3] aka степень: %x\n",
      res.bits[0], res.bits[1], res.bits[2], res.bits[3]);

  return 0;
}