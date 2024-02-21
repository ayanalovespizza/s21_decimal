#include "../s21_decimal.h"
#include <math.h>
#include <stdio.h>

#define MAX_SCALE 28

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




int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int status = 0; // Успешно
    const float DECIMAL_MAX = powf(10, MAX_SCALE + 7); // Максимальное значение для float
    const float MIN_POSITIVE = powf(10, -MAX_SCALE); // Минимальное положительное значение

    // Обнуление dst
    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;

    if (fabsf(src) < MIN_POSITIVE && src != 0.0) {
        // Слишком маленькое значение
        status = 1;
    } else if (fabsf(src) > DECIMAL_MAX || isinf(src)) {
        // Слишком большое значение или бесконечность
        status = 1;
    } else {
        // Округление до 7 значимых цифр
        int scale = 0;
        while (src != 0.0f && (fabsf(src) < 1e7 && scale < MAX_SCALE)) {
            src *= 10;
            scale++;
        }
        src = roundf(src);

        while (fabsf(src) >= 1e7 && scale > 0) {
            src /= 10;
            scale--;
        }

        long long intPart = (long long)src;
        // Заполнение bits[0-2] и scale
        dst->bits[0] = intPart & 0xFFFFFFFF; // Младшие 32 бита
        dst->bits[1] = (intPart >> 32) & 0xFFFFFFFF; // Средние 32 бита
        dst->bits[2] = 0;

        // Установка масштаба и знака
        dst->bits[3] = scale << 16; // Масштаб
        if (src < 0) {
            dst->bits[3] |= 0x80000000; // Знак
        }
    }

    return status;
}