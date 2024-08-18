#include "../s21_decimal.h"

/*
Функция преобразует тип данных decimal в тип данных int
*/

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  // объявляем переменную result, хранящую значение "успех"
  int result = S21_SUCCESS;
  // проверяем данные на валидность
  if (s21_valid_value_decimal(src) && dst != NULL) {
    // объявляем переменную degree, хранящую значение степени 10
    int degree = s21_get_scale(src);
    // проверяем степень
    if (degree > 0) {
      // пока значение degree больше 0, умнажаем мантису src на 10
      while (degree > 0) {
        s21_shift_divide_by_10(&src);
        degree--;
      }
      // передаем в src значение степени 0
      s21_set_scale(&src, 0);
    }
    // если мантиса src, левее 30 бита, равна 0, то приравниваем к ней dst
    if (src.bits[S21_MID] == 0 && src.bits[S21_HIGH] == 0 &&
        (src.bits[S21_LOW] & 0x80000000) == 0) {
      *dst = src.bits[S21_LOW];
      // если бит знака в src равен 1, то делаем инверсию dst
      if (s21_get_sign(src) != S21_POSITIVE) {
        *dst *= -1;
      }
      // если только 31 бит мантисы src равен 1, а знак "-", приравниваем dst к
      // минимальному значению
    } else if (src.bits[S21_MID] == 0 && src.bits[S21_HIGH] == 0 &&
               (unsigned int)src.bits[S21_LOW] == 0x80000000 &&
               s21_get_sign(src) != S21_POSITIVE) {
      *dst = -2147483648;
    } else {
      // передаем в result статус "ошибка"
      result = S21_CONVERTING_ERROR;
      // передаем в dst значение 0
      *dst = 0;
    }
  } else {
    // передаем в result статус "ошибка"
    result = S21_CONVERTING_ERROR;
  }
  // возвращаем статус из result
  return result;
}
