#include <stdio.h>
#include <string.h>
#include "s21_decimal.h"

int main() {
  s21_decimal result;
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    s21_div(decimal1, decimal2, &result);


  printf("%x\n",result.bits[0]);
  printf("%x\n",result.bits[1]);
  printf("%x\n",result.bits[2]);
  printf("%x\n",result.bits[3]);

  return 0;
}
