#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int scale = s21_get_scale(value);
  int sign = s21_get_sign(value);
  s21_decimal five_tenths_decimal;
  s21_init(&five_tenths_decimal);
  *result = value;
  five_tenths_decimal.bits[0] = 5;
  s21_set_scale(&five_tenths_decimal, 1);

  if (scale) {
    if (sign) {
      s21_sub(value, five_tenths_decimal, result);
    } else {
      s21_add(value, five_tenths_decimal, result);
    }
  }
  s21_truncate(*result, result);
  return S21_SUCCESS;
}