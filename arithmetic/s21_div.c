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
        s21_decimal result_whole;

        initial_make_null(&whole_1_decimal_part);
        initial_make_null(&result_whole);
        initial_make_null(&fraction_1_decimal_part);
        // порядок у результата = разность порядков
        int result_scale = value_2_work.scale - value_1_work.scale;

        // выравниваем порядки
        point_to_normal(&value_1_work, &value_2_work);

        value_1 = work_to_initial(value_1_work);

        give_whole_and_fraction_part(value_1,&whole_1_decimal_part,&fraction_1_decimal_part);
        give_whole_and_fraction_part(value_2,&whole_2_decimal_part,&fraction_2_decimal_part);
        divide_whole_parts(whole_1_decimal_part, whole_2_decimal_part, &result_whole);
        // далее работаем только с интами (отдельно с целой и отдельно с дробной)

        /* ЦЕЛАЯ ЧАСТЬ по циклу
        - сдвигаем делимое от максимума до 0
        - вычитаем если можно
        */

        /* ДРОБНАЯ ЧАСТЬ
        - делитель домножаем на 10
        */

////        is_overflow(&result_work);
////        status = tidy_work_decimal(&result_work);
//
//        *result = work_to_initial(result_work);
          *result = result_whole;
    }

    return status;
}
void give_whole_and_fraction_part(s21_decimal value,s21_decimal* whole,s21_decimal* fraction){

    s21_truncate(value,whole);
    whole->bits[3]=whole->bits[3]&(~MINUS);
    value.bits[3]=value.bits[3]&(~MINUS);
    s21_sub(value,*whole,fraction);
    whole->bits[3]=0;
    fraction->bits[3]=0;
}

void divide_whole_parts(s21_decimal whole1, s21_decimal whole2, s21_decimal* result_whole) {
    // Инициализация результата деления
    s21_decimal zero = {0};
    *result_whole = zero;

    // Деление целых чисел путем вычитания
    while (s21_is_greater_or_equal(whole1, whole2)) {
        s21_decimal  one = {1};
        s21_add(*result_whole, one, result_whole);
        s21_sub(whole1, whole2, &whole1);
    }
}