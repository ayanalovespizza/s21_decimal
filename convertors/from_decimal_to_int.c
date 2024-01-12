#include "../s21_decimal.h"

/**
 * @brief Преобразователь из decimal в int
 *
 * @warning Если в числе типа decimal есть дробная часть, то ее следует
 *          отбросить (0,9 => 0)
 *
 * @return 0 - OK
 *         1 - ошибка конвертации
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst) {}