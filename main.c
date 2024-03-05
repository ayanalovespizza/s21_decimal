#include <stdio.h>
#include "s21_decimal.h"
#include <stdint.h>
#include "limits.h"


int main() {

    s21_decimal decimal = {0};

    float f = 5.92141241E+23;
    // 592141200000000000000000
    s21_decimal decimal_check = {{0xBF280000, 0x9ED0576, 0x7D64, 0x0}};

    int code = s21_from_float_to_decimal(f,&decimal);

    int eq = s21_is_equal(decimal,decimal_check);


    printf("qe - %d\ncode- %d\n",eq,code);


    printf("%d\n",decimal.bits[0]);
    printf("%d\n",decimal.bits[1]);
    printf("%d\n",decimal.bits[2]);
    printf("%d\n",decimal.bits[3]);


    return 0;
}

