#include "../s21_decimal.h"

/*
Функция преобразует тип данных int в тип данных decimal
*/

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  // создаем переменную result, по умочанию хранящую статус ошибки
  int result = S21_CONVERTING_ERROR;
  // проверяем валидность данных
  if (dst != NULL) {
    // обнуляем переменную dst
    s21_set_zero_decimal(dst);
    // проверяем src на отрицательность
    if (src < 0) {
      // передаем в dst знак -
      s21_set_sign(dst, S21_NEGATIVE);
      // инвертируем src
      src *= -1;
    }
    // передаем значение src в dst.bits[S21_LOW]
    dst->bits[S21_LOW] = src;
    // меняем статус в result на "успех"
    result = S21_SUCCESS;
  }
  // возвращаем статус из result
  return result;
}
