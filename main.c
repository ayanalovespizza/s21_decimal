#include <stdio.h>

#include "s21_decimal.h"
#include <limits.h>

int main() {

  s21_decimal decimal ={0};
  int a = INT_MIN;
  int res = s21_from_int_to_decimal(a,&decimal);
  
  // printf("%d\n",decimal.bits[0]);
  // printf("%x\n",decimal.bits[3]);
  printf("%d\n",res);

  return 0;
}