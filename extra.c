#include "s21_decimal.h"

// работа с переполнением
int is_overflow(s21_work_decimal) {}

// увеличивание scale
int pointleft(s21_work_decimal) {}

// уменьшение scale
int pointright(s21_work_decimal) {}

// нормализация (сравниваем scale?)
int normalize(s21_work_decimal, const int summ, const int sign) {}

// перевод из исходного decimal в рабочий
s21_work_decimal decimal_to_work(s21_decimal) {}

// перевод из рабочего decimala в исходный
s21_decimal work_to_decimal(s21_work_decimal) {}