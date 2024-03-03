#include <stdio.h>
#include <string.h>
#include "s21_decimal.h"

int main() {
  s21_decimal result;
    // 79228162514264337593543950335
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -7922816251426433759354395033.5
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // 71305346262837903834189555302
    s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};
  s21_add(decimal1, decimal2, &result);
for(int i =0;i<4;i++){
    printf("%x\n",result.bits[i]);
}
  return 0;
}
