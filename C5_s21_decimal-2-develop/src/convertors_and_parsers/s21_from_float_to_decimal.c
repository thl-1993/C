#include "../s21_decimal.h"

/*
Функция преобразует тип данных float в тип данных decimal
*/

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  // объяввляем переменную result, передаем ей статус "ошибка"
  int result = S21_CONVERTING_ERROR;
  // обнуляем dst
  s21_set_zero_decimal(dst);
  // проверяем валидность данных
  if ((s21_valid_value_float(src) && dst != NULL)) {
    // проверяем src на 0
    if (src != 0.0) {
      // объявляем переменную sign, хранящую знак числа
      int sign = S21_POSITIVE;
      if (src < 0) {
        // если src отрицательно, передаем это в sign и инверсируем src
        sign = S21_NEGATIVE;
        src *= -1;
      }
      // объявляем переменную tmp для хранения значения src по типу double
      double tmp = (double)src;
      // объяаляем переменную degree для хранения значения степени числа 10
      int degree = 0;
      // вычисляем degree
      while (degree < 28 && (int)tmp / (int)powl(2, 21) == 0) {
        tmp *= 10;
        degree++;
      }
      // округляем tmp до ближайшего целого числа
      tmp = round(tmp);
      // отбрасываем незначащие цифры в tmp, меняя degree
      while (fmod(tmp, 10) == 0 && degree > 0) {
        degree--;
        tmp /= 10;
      }
      // объявляем переменную fl для хранения значения tmp по типу float
      union union_src {
        float asFloat;
        int asInteger;
      };
      union union_src fl;
      fl.asFloat = tmp;
      // объяаляем переменную exp для хранения значения степени числа 2
      int exp = s21_get_exp_float(fl.asFloat);
      // передаем результат преобразования в dst
      dst->bits[exp / 32] = 1 << exp % 32;
      for (int i = exp - 1, j = 22; j >= 0; i--, j--)
        if ((fl.asInteger & (0x1 << j)) != 0)
          dst->bits[i / 32] |= 0x1 << i % 32;
      // передаем значения степени и знака в dst
      s21_set_sign(dst, sign);
      s21_set_scale(dst, degree);
    }
    // передаем в result статус "успех"
    result = S21_SUCCESS;
  }
  // возвращаем статус из result
  return result;
}