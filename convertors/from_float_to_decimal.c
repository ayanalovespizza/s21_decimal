#include "../s21_decimal.h"
#include <math.h>
#include <stdio.h>
/**
 * @brief преобразователь из floar в decimal
 *
 * @warning Если числа слишком малы, то вернуть ошибку 1 и значение, равное 0;
 *          Если числа слишком велики или равны бесконечности, вернуть ошибку;
 *          При обработке числа с типом float преобразовывать все содеражищиеся
 *            в нем значимые десятичные цифры.Если таких цифр больше 7, то
 *            значение округляется к ближайшему, у которого не больше 7 значимых
 *            цифр
 *
 * @return 0 - OK
 *         1 - ошибка конвертации
 */
// преобразователь из float в decimal

int get_scale(char *str, int pos);

int s21_from_float_to_decimal(float src, s21_decimal *dst) {

    char str[100];
    int sign_for_scale = 0; // 0 означает + по умолчанию
    int pos = 0;
    int is_exp = 0;
    float res = 0;
    int arr[32] ={0};

    int i = 0 ;

    if(src <0){
        dst->bits[3] |= (1<< 31);
        src*=-1;
    }

    float  test = src;

    sprintf(str,"%.7e",src);

    for(int i= 2; str[i]!='\0';i++){
        if(str[i] == 'E' || str[i] == 'e'){
            is_exp = 1;
        }
        if(str[i] == '-' && is_exp ==1){
            sign_for_scale = 1;
        }
        if((str[i] >= '0' && str[i] <='9') && is_exp == 1){
            pos = i;
            break;
        }

    }

    int scale = get_scale(str,pos);

    if(sign_for_scale == 0) {
        res = src * pow(10, scale);
//        res *= pow(10,(7-scale));
    }else{
        scale*=-1;
        res = src * pow(10, scale);
        res *= pow(10,(7-scale));
        scale *= -1;
    }




    dst->bits[0] = (int)res;

    if(scale != 0 ) {
        while (scale > 0) {
            arr[i++] = scale % 2;
            scale /= 2;
        }


        for (int j = 0; j < i; j++) {
            dst->bits[3] &= ~(1 << (16 + j));
            dst->bits[3] |= (arr[j] << (16 + j));
        }
    }

    return 0;

}

int get_scale(char *str, int pos){
    int num = 0;
    for(int i = pos; str[i] != '\0' ;i++){
        if(str[i] >='0' && str[i] <= '9'){
            num = num *10 + (str[i] - '0');
        }
    }
    return num;
}