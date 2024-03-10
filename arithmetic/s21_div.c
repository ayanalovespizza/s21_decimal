#include "../s21_decimal.h"

/**
 * @brief Деление
 *
 * @warning При получении чисел, не вмещающихся в мантису
 * (bits[0], bits[1], bits[2]), использовать банковское округеление
 *
 * @return 0 - OK
 *         1 - число слишком велико или равно бесконечности
 *         2 - число слишком мало или равно отрицательной бесконечности
 *         3 - деление на 0
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = 0;

    s21_decimal dec_null = {0, 0, 0, 0};

    // если делитель = 0, то возвращаем ошибку 3
    if (s21_is_equal(value_2, dec_null)) {
        status = 3;

    } else {
        int sign_res = 0;
        int sign_1 = value_1.bits[3] & MINUS;
        int sign_2 = value_2.bits[3] & MINUS;

        // если у делителя и делимого разные знаки, то у результата знак минус
        if (sign_1 != sign_2) {
            sign_res = 1;
        }

        // перевод в рабочий децимал
        s21_work_decimal value_1_work = initial_to_work(value_1);
        s21_work_decimal value_2_work = initial_to_work(value_2);
        s21_work_decimal result_work = {{0, 0, 0, 0, 0, 0}, 0};

        s21_decimal whole_1_decimal_part;
        s21_decimal fraction_1_decimal_part;
        s21_decimal whole_2_decimal_part;
        s21_decimal fraction_2_decimal_part;

        initial_make_null(&whole_1_decimal_part);
        initial_make_null(&fraction_1_decimal_part);
        // порядок у результата = разность порядков
        int result_scale = value_2_work.scale - value_1_work.scale;

//        s21_truncate(value_1,&whole_1_decimal_part);
//        s21_truncate(value_2,&whole_2_decimal_part);


        // выравниваем порядки
        //point_to_normal(&value_1_work, &value_2_work);

        value_1 = work_to_initial(value_1_work);
        //value_2 = work_to_initial(value_2_work);


        // Начало функции получения дробной и целой части
        s21_truncate(value_1,&whole_1_decimal_part);
        s21_truncate(value_2,&whole_2_decimal_part);


        s21_sub(value_1,whole_1_decimal_part,&fraction_1_decimal_part);


        fraction_1_decimal_part.bits[3]=0;

       for(int i = 0; i<4;i++) {
           printf("wh1:%d\n", whole_1_decimal_part.bits[i]);
       }

        for(int i = 0; i<4;i++) {
            printf("fr1%d\n", fraction_1_decimal_part.bits[i]);
        }





        int whore1 = -500;
        int fraction1 = -300;

        int whore2 = -500;
        int fraction2 = -300;

        s21_from_decimal_to_int(whole_1_decimal_part, &whore1);
        s21_from_decimal_to_int(fraction_1_decimal_part, &fraction1);


        printf("wh1_int %d\n",whore1);
        printf("fr1_int %d\n",fraction1);
        // Начало функции получения дробной и целой части


        // далее работаем только с интами (отдельно с целой и отдельно с дробной)

        /* ЦЕЛАЯ ЧАСТЬ по циклу
        - сдвигаем делимое от максимума до 0
        - вычитаем если можно
        */

        /* ДРОБНАЯ ЧАСТЬ
        - делитель домножаем на 10
        */

        is_overflow(&result_work);
        status = tidy_work_decimal(&result_work);

        *result = work_to_initial(result_work);
    }

    return status;
}