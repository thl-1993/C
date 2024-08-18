#include "../s21_decimal.h"

/*
Функция преобразует тип данных decimal в тип данных float
*/

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  // объявляем переменную result, хранящую значение "ошибка"
  int result = S21_CONVERTING_ERROR;
  // проверяем существование dst
  if (dst != NULL) {
    // передаем в result статус "успех"
    result = S21_SUCCESS;
    // проверяем src на допустимость значений
    if (s21_valid_value_decimal(src)) {
      *dst = 0.0;
      long double t =
          ((double)(unsigned int)src.bits[S21_LOW] +
           ((double)(unsigned int)src.bits[S21_MID] * 4294967295.0) +
           ((double)(unsigned int)src.bits[S21_HIGH] * 4294967295.0 *
            4294967295.0)) /
          powl(10, s21_get_scale(src));

      *dst = (float)t;
      // если src отрицательно, делаем инверсию dst
      if (s21_get_sign(src) == S21_NEGATIVE) {
        *dst *= -1;
      }
    }
  }
  // возвращаем статус из result
  return result;
}