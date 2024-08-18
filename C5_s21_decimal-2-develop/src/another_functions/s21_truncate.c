#include "../s21_decimal.h"
// TODO: переделать нормально, а то говно какое-то написал.
int s21_truncate(s21_decimal value, s21_decimal *result) {
  /*
  Returns the integer digits of the specified Decimal number;
  any fractional digits are discarded, including trailing zeros.
  */
  big_decimal bd_ten, buffer;
  int sign = s21_get_sign(value);
  int scale = s21_get_scale(value);
  big_decimal_init(&bd_ten);
  big_decimal_init(&buffer);
  s21_decimal_to_big_decimal(value, &buffer);
  bd_ten.bits[0] = 10;

  while (scale) {
    big_decimal_mantissa_div(buffer, bd_ten, &buffer);
    scale--;
  }

  big_decimal_set_scale(&buffer, scale);
  big_decimal_set_sign(&buffer, sign);
  big_decimal_to_s21_decimal(buffer, result);
  return S21_SUCCESS;
}