#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  big_decimal bd_value;
  big_decimal buffer;
  big_decimal bd_ten;
  s21_decimal one_dec;
  int scale = s21_get_scale(value);
  int sign = s21_get_sign(value);
  int flag = S21_FALSE;
  s21_decimal_to_big_decimal(value, &bd_value);
  big_decimal_init(&buffer);
  big_decimal_init(&bd_ten);
  s21_init(&one_dec);
  one_dec.bits[0] = 1;
  bd_ten.bits[0] = 10;

  while (scale && flag) {
    buffer = big_decimal_mantissa_div(bd_value, bd_ten, &bd_value);
    scale--;
    flag = (buffer.bits[0]) ? S21_TRUE : S21_FALSE;
  }
  s21_truncate(value, result);
  if (sign && !flag) {
    s21_sub(*result, one_dec, result);
  }
  return S21_SUCCESS;
}