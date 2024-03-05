#include <stdio.h>

#include "s21_decimal.h"

int main() {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7.8228162514264337593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0x1C0000}};
  // 61.978735728724164262422454727
  s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x1B0000}};
  s21_decimal result = {0, 0, 0, 0};

  //   printf(
  //       "Бит[0]: %d\n\
// Бит[1]: %d\n\
// Бит[2]: %d\n\
// Бит[3] aka степень: %x\n\n",
  //       decimal_check.bits[0], decimal_check.bits[1], decimal_check.bits[2],
  //       decimal_check.bits[3]);

  int status = s21_mul(decimal1, decimal2, &result);

  printf(
      "Мой результат: \n\
Бит[0]: %x\n\
Бит[1]: %x\n\
Бит[2]: %x\n\
Бит[3] aka степень: %x\n",
      result.bits[0], result.bits[1], result.bits[2], result.bits[3]);

  printf(
      "\n\nОжидаемый результат: \n\
Бит[0]: %x\n\
Бит[1]: %x\n\
Бит[2]: %x\n\
Бит[3] aka степень: %x\n",
      check.bits[0], check.bits[1], check.bits[2], check.bits[3]);

  printf("Результат сравнения: %d status %d", s21_is_equal(result, check),
         status);

  return 0;
}