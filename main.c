#include <stdio.h>
#include "s21_decimal.h"
#include <stdint.h>





int main() {
    s21_decimal decimal={0};

    float a =0.13242342;

    s21_from_float_to_decimal(a,&decimal);
    printf("%d\n",decimal.bits[0]);
    printf("%x\n",decimal.bits[1]);
    printf("%x\n",decimal.bits[2]);
    printf("%x\n",decimal.bits[3]);

    return 0;
}
