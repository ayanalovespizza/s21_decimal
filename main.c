#include <stdio.h>
#include <string.h>
#include "s21_decimal.h"

int main() {
  s21_decimal result;


    // -8
    s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x80000000}};
    // -7922816251426433759354395035
    s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
    // 7922816251426433759354395027
    s21_decimal check = {{0x99999993, 0x99999999, 0x19999999, 0x0}};

  s21_sub(decimal1, decimal2, &result);
for(int i =0;i<4;i++){
    printf("%x\n",result.bits[i]);
}
  return 0;
}
