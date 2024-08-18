#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag = 1;
  s21_up_scale(&value_1, &value_2);
  if (s21_get_sign(value_1) == s21_get_sign(value_2)) {
    for (int i = 95; i >= 0; i--) {
      int bit1 = s21_get_bit(value_1, i);
      int bit2 = s21_get_bit(value_2, i);
      if (bit1 != bit2) {
        flag = 0;
      }
    }
  } else {
    if (DECIMAL_ZERO_MULTI(value_1, value_2))
      flag = 1;
    else
      flag = 0;
  }
  return flag;
}
