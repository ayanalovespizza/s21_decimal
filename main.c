#include <stdio.h>
#include <string.h>
#include "s21_decimal.h"

int main() {
  s21_decimal result;
    // 7055.820576069728775806815669
    s21_decimal decimal1 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x00180000}};
    // -792281625142643.37593543950335
    s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    // -5590196992723426894.7708082476
    s21_decimal decimal_check = {
            {0x2DC7792C, 0x10FB6E4E, 0xB4A10696, 0x800A0000}};

  s21_mul(decimal1, decimal2, &result);
for(int i =0;i<4;i++){
    printf("%x\n",result.bits[i]);
}
  return 0;
}
