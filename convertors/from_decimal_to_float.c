#include "../s21_decimal.h"
#define SCALE 0x00ff0000
#include <stdio.h>
#include <string.h>
#include <math.h>
/**
 * @brief Преобразователь из decimal в float
 *
 * @return 0 - OK
 *         1 - ошибка конвертации
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    // Извлекаем знак числа
    int sign = (src.bits[3] & 0x80000000) ? -1 : 1;

    // Извлекаем масштаб (показатель степени десяти)
    int scale = (src.bits[3] >> 16) & 0xFF;

    // Собираем целое число из bits[0-2]
    long long intPart = ((long long)src.bits[1] << 32) | src.bits[0];

    // Преобразуем в float, применяем масштаб и учитываем знак
    float result = intPart * powf(10, -scale) * sign;

    // Сохраняем результат в переданном указателе
    *dst = result;

    return 0; // Успешное выполнение
}
