#include "../s21_decimal.h"

int s21_bitwise_division(s21_work_decimal value_1_divisible,
                         s21_work_decimal value_2_divider,
                         s21_work_decimal *bitwise_int,
                         s21_work_decimal *bitwise_remainder);
int get_max_bit(s21_work_decimal value_1);
void sub_shift_left(s21_work_decimal *num, const int shift_value);
void shift_left(s21_work_decimal *num, const int shift_value);
void sub_shift_right(s21_work_decimal *num, const int shift_value);
void shift_right(s21_work_decimal *num, const int shift_value);
int get_fractional_part(s21_work_decimal* result, s21_work_decimal* remainder,
                        s21_work_decimal divider);

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
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
    s21_decimal dec_null = {0, 0, 0, 0};

    // if (s21_is_equal(value_2, dec_null)) {
    //     return 3;
    // }

    // if (s21_is_equal(value_1, dec_null)) {
    //     initial_make_null(result);
    //     return 0;
    // }

    unsigned int value_1_divisible_sign = 0;
    unsigned int value_2_divider_sign = 0;
    int status = 0;
    int frac_true = 0;
    int frac_scale = 0;
    s21_work_decimal value_1_divisible =
            initial_to_work(value_1);  // первое число - делимое
    s21_work_decimal value_2_divider =
            initial_to_work(value_2);  // второе число - делитель

    s21_work_decimal bitwise_int = {{0, 0, 0, 0, 0, 0},
                                    0};  // для сохранения целой части деления
    s21_work_decimal bitwise_remainder = {
            {0, 0, 0, 0, 0, 0}, 0};  // для сохранения дробной части деления
    s21_work_decimal ten = {{10, 0, 0, 0, 0, 0}, 0};

    value_1_divisible_sign = value_1_divisible.sign;
    value_2_divider_sign = value_2_divider.sign;




  int scale = value_1_divisible.scale - value_2_divider.scale;
    //point_to_normal(&value_1_divisible, &value_2_divider);
    // побитовое деление (отдельно получаем целое и остаток от деления)
    frac_true = s21_bitwise_division(value_1_divisible, value_2_divider, &bitwise_int,
                                     &bitwise_remainder);


    // теперь осталось собрать воедино целое частное и остаток от деления...
if(frac_true){
   frac_scale = get_fractional_part(&bitwise_int, &bitwise_remainder, value_2_divider);
}


if(scale<0) {
    while (scale != 0) {
        pointleft(&bitwise_int);
        scale++;
    }
}

scale = scale + frac_scale;

bitwise_int.scale = scale;

    is_overflow(&bitwise_int);

//
    status = tidy_work_decimal(&bitwise_int);
//

    if (value_1_divisible_sign!= value_2_divider_sign) {
        bitwise_int.sign = 1;
    } else  {
        bitwise_int.sign = 0;
    }

    if(!status) {
        *result = work_to_initial(bitwise_int);
    }

    if (s21_is_equal(value_2, dec_null)) {
        status = 3;
    }

    if (s21_is_equal(value_1, dec_null)) {
        initial_make_null(result);
        status = 0;
    }

    return status;
}

// пример №1: 15 / 2 = целое 7 и остаток 1
// пример №2: 11 / 3 = целое 3 и остаток 2
int s21_bitwise_division(s21_work_decimal value_1_divisible,
                         s21_work_decimal value_2_divider,
                         s21_work_decimal *bitwise_int,
                         s21_work_decimal *bitwise_remainder) {
    // не вставила еще одну проверку на нули, так как она была в основной функции
    int res = 0;
    // обнуляем результаты
    work_make_null(bitwise_int);
    work_make_null(bitwise_remainder);

    /* забираем разряд старшего (значимого) бита в числе
    например, в числе 011111 порядок старшего бита = 4 */
    int max_bit_divisible = get_max_bit(value_1_divisible);
    int max_bit_divider = get_max_bit(value_2_divider);

    // разница в этих значениях = количество сдвигов
    int count_shifts = max_bit_divisible - max_bit_divider;

    // изначально сдвигаем делитель на вычисленную разницу
    shift_left(&value_2_divider, count_shifts);

    // теперь циклом проходимся по каждому сдвигу
    s21_work_decimal temp = {{0, 0, 0, 0, 0, 0}, 0};
    for (int i = 0; i < count_shifts+1; i++) {
//            bitwise_sub(value_1_divisible, value_2_divider, &temp);
//        // сдвигаем целое на 1, чтобы записать в самый младший бит другой результат
//        // если результат вычитания положительный, то вычитать можно
//         shift_left(bitwise_int, 1);
//        if (sub_result == 1) {
//            // cтавим 1 в самый младший бит
//            //shift_left(bitwise_int, 1);
//            s21_big_set_bit(bitwise_int, 0, 1);
//            // делимым теперь становится остаток от вычитания
//            value_1_divisible = temp;
//            // если результат вычитания отрицательный, то вычитать нельзя
//        } else if (sub_result == 0) {
//            //shift_left(bitwise_int, 1);
//            // cтавим 0 в самый младший бит, делимое остается прежним
//            s21_big_set_bit(bitwise_int, 0, 0);
//        }
//        // сдвигаем делитель на 1 вправо
//      bitwise_sub(value_1_divisible, value_2_divider, &temp);
//            shift_left(bitwise_int, 1);
        if(is_greater_or_eq(value_1_divisible,value_2_divider))
        {
            bitwise_sub(value_1_divisible, value_2_divider, &temp);
            shift_left(bitwise_int, 1);
            s21_big_set_bit(bitwise_int, 0, 1);
            // делимым теперь становится остаток от вычитания
            value_1_divisible = temp;
        }
        else {
            printf("fdsfa\n");
            shift_left(bitwise_int, 1);
            s21_big_set_bit(bitwise_int, 0, 0);
        }
        // сдвигаем делитель на 1 вправо
        shift_right(&value_2_divider, 1);
    }

    // после всех сдвигов из цикла у нас есть остаток в делимом, записываем его в
    // остаток
    if(!(mantis_is_null(value_1_divisible))) {
        *bitwise_remainder = value_1_divisible;
    }

    return 0;
}

int get_max_bit(s21_work_decimal value_1) {
    int max_bit_index = 0;
    for (int i = (32 * 6) - 1; i >= 0; i--) {
        if (s21_big_get_bit(value_1, i)) {
            max_bit_index = i;
            i = -1;
        }
    }
    return max_bit_index;
}

void sub_shift_left(s21_work_decimal *num, const int shift_value) {
    if (shift_value == 0) return;
    unsigned shift = 0;
    for (int i = 0; i < 7;
         i++) {
        unsigned temp = num->bits[i];
        num->bits[i] = num->bits[i] << shift_value;
        num->bits[i] |= shift;
        shift = temp >> (sizeof(unsigned) * 6 - shift_value);
    }
}
void shift_left(s21_work_decimal *num, const int shift_value) {
    int max_shift = sizeof(unsigned) * 6 - 1;
    for (int i = 0; i < shift_value / max_shift; ++i) {
        sub_shift_left(num, max_shift);
    }
    sub_shift_left(num, shift_value % max_shift);
}

void shift_right(s21_work_decimal *num, const int shift_value) {
    const int max_shift = sizeof(unsigned) * 8 - 1;
    for (int i = 0; i < shift_value / max_shift; ++i) {
        sub_shift_right(num, max_shift);
    }
    sub_shift_right(num, shift_value % max_shift);
}

void sub_shift_right(s21_work_decimal *num, const int shift_value) {
    unsigned shift = 0;
    for (int i = 6; i >=0; i--) {
        const unsigned temp = num->bits[i];
        num->bits[i] = num->bits[i] >> shift_value;
        num->bits[i] |= shift;
        shift = temp << (sizeof(unsigned) * 8 - shift_value);
    }
}

int get_fractional_part(s21_work_decimal* result, s21_work_decimal* remainder,
                        s21_work_decimal divider) {
    //s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}};
    s21_work_decimal new_number = {{0}};
    int scale = 0;
    //s21_mul_big_decimal(*result, ten, result);
    pointleft(result);
    while (check_mantis(*result) && !mantis_is_null(*remainder)) {
        pointleft(remainder);
        work_make_null(&new_number);
        s21_bitwise_division(*remainder, divider, &new_number, remainder);
        bitwise_add(*result, new_number, result);
        pointleft(result);
        scale++;
    }
    if(!mantis_is_null(*remainder)) {
        pointleft(remainder);
        work_make_null(&new_number);
        s21_bitwise_division(*remainder, divider, &new_number, remainder);
        bitwise_add(*result, new_number, result);
    }
    //banking_round(result);
    return scale;
}