#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  value_2.bits[S21_DEG] += 1U << 31;
  return s21_add(value_1, value_2, result);
}
