#include "../s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0, flag_of_end = 0, scale1 = s21_get_scale(value_1),
      scale2 = s21_get_scale(value_2);
  if (s21_up_scale(&value_1, &value_2)) {
    if (scale1 > scale2) {
      flag = 0;
      flag_of_end = 1;
    } else {
      flag = 1;
      flag_of_end = 1;
    }
  }
  if (s21_get_sign(value_1) && !s21_get_sign(value_2)) {
    flag_of_end = 1;
    flag = 0;
  }
  if (!s21_get_sign(value_1) && s21_get_sign(value_2)) {
    if (DECIMAL_ZERO_MULTI(value_1, value_2))
      flag = 0;
    else
      flag = 1;
    flag_of_end = 1;
  }
  for (int i = 95; i >= 0 && !flag_of_end; i--) {
    int bit1 = s21_get_bit(value_1, i);
    int bit2 = s21_get_bit(value_2, i);
    if (bit1 != bit2) {
      if (bit1 < bit2) {
        flag_of_end = 1;
      } else {
        flag = 1;
        flag_of_end = 1;
      }
    }
  }
  if ((s21_get_sign(value_1) && s21_get_sign(value_2)) && flag_of_end)
    flag = !flag;
  return flag;
}
