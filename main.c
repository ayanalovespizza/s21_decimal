#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal decimal1 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
  s21_decimal decimal2 = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

  printf("Результат теста 1 (должно быть 0): %d\n\n",
         s21_is_equal(decimal1, decimal2));

  printf(
      "Бит[0]: %d\n\
Бит[1]: %d\n\
Бит[2]: %d\n\
Бит[3] aka степень: %d\n\n",
      decimal1.bits[0], decimal1.bits[1], decimal1.bits[2], decimal1.bits[3]);

  printf(
      "Бит[0]: %d\n\
Бит[1]: %d\n\
Бит[2]: %d\n\
Бит[3] aka степень: %d\n",
      decimal2.bits[0], decimal2.bits[1], decimal2.bits[2], decimal2.bits[3]);

  return 0;
}