#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  /*
  Returns the result of multiplying the specified Decimal by -1.
  */
  int bit = 0;
  *result = value;
  bit = s21_get_bit(value, S21_SIGN_INDEX);
  if (bit == S21_NEGATIVE)
    s21_set_bit(result, S21_SIGN_INDEX, S21_POSITIVE);
  else
    s21_set_bit(result, S21_SIGN_INDEX, S21_NEGATIVE);
  return S21_SUCCESS;
}