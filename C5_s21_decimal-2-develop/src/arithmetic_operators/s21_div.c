#include "../s21_decimal.h"

int s21_check_zero(s21_decimal value) {
  int result = S21_FALSE;
  for (int i = 0; i < S21_DEG; i++) {
    if (value.bits[i] != 0) result = S21_TRUE;
  }
  return result;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_init(result);

  if (!s21_check_zero(value_1) && s21_check_zero(value_2)) {
    int response = (s21_get_sign(value_1)) ? 2 : S21_CONVERTING_ERROR;
    return response;
  } else if (s21_check_zero(value_1) && s21_check_zero(value_2))
    return 3;

  int response = S21_SUCCESS;
  int scale = 0;
  int result_scale = 0;
  int sign = 0;
  big_decimal bd_value_1;
  big_decimal bd_value_2;
  big_decimal bd_current;
  big_decimal bd_result;
  big_decimal bd_buffer;
  big_decimal bd_ten;

  s21_decimal_to_big_decimal(value_1, &bd_value_1);
  s21_decimal_to_big_decimal(value_2, &bd_value_2);
  big_decimal_init(&bd_current);
  big_decimal_init(&bd_result);
  big_decimal_init(&bd_buffer);
  big_decimal_init(&bd_ten);

  bd_ten.bits[0] = 10;
  result_scale = scale = s21_get_scale(value_1) - s21_get_scale(value_2);
  sign = (s21_get_sign(value_1) == s21_get_sign(value_2)) ? S21_POSITIVE
                                                          : S21_NEGATIVE;

  for (int i = 0; i < 28 - scale && !big_decimal_is_zero(bd_value_1); i++) {
    bd_value_1 = big_decimal_mantissa_div(bd_value_1, bd_value_2, &bd_current);
    big_decimal_mantissa_add(bd_result, bd_current, &bd_result);
    if (!big_decimal_is_zero(bd_value_1)) {
      big_decimal_mantissa_mul(bd_result, bd_ten, &bd_result);
      big_decimal_mantissa_mul(bd_value_1, bd_ten, &bd_value_1);
      result_scale++;
    }
  }

  while (result_scale < 0) {
    big_decimal_mantissa_mul(bd_result, bd_ten, &bd_result);
    result_scale++;
  }

  result_scale =
      big_decimal_scale_processor(&bd_result, &bd_buffer, result_scale);

  big_decimal_set_sign(&bd_result, sign);

  response =
      big_decimal_bank_round(bd_buffer, &bd_result, &bd_value_1, result_scale);

  big_decimal_set_scale(&bd_result, result_scale);

  if (!response)
    big_decimal_to_s21_decimal(bd_result, result);
  else
    s21_set_zero_decimal(result);

  return response;
}