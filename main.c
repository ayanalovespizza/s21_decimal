#include <stdio.h>
#include <string.h>
#include "s21_decimal.h"

int main() {
  s21_decimal result;
  //-7,5
    s21_decimal decimal1 = {{0x4B, 0x0, 0x0, 0x80010000}};

    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};

    s21_div(decimal1, decimal2, &result);


//  printf("%x\n",result.bits[0]);
//  printf("%x\n",result.bits[1]);
//  printf("%x\n",result.bits[2]);
//  printf("%x\n",result.bits[3]);

  return 0;
}
