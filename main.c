#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal decimal1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal decimal2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result = {{7}};
  for(int i=0;i<10;i++){
  printf("%d\n",result.bits[i]);
  }
  return 0;
}