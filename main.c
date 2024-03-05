#include <stdio.h>
#include "s21_decimal.h"
#include <stdint.h>
#include "limits.h"


int main() {
    s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    float test;

    int a = s21_from_decimal_to_float(decimal1,&test);

    printf("%f\n",test);


    printf("%x\n",decimal1.bits[0]);
    printf("%x\n",decimal1.bits[1]);
    printf("%x\n",decimal1.bits[2]);
    printf("%x\n",decimal1.bits[3]);



    return 0;
}
