#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <string.h>

#define S21_NAN 0.0 / 0.0L
#define S21_INFINITY 1.0 / 0.0L
#define S21_NEGATIVE_INFINITY -1.0 / 0.0L
#define S21_MAX_DECIMAL 79228162514264337593543950335

#define DECIMAL_ZERO_MULTI(value1, value2)                      \
  (((!value1.bits[0] && !value1.bits[1]) && !value1.bits[2]) && \
   ((!value2.bits[0] && !value2.bits[1]) && !value2.bits[2]))

#define START_EXTRA 96

#define S21_D_NUMBER_OF_BITS 4

#define S21_LOW 0
#define S21_MID 1
#define S21_HIGH 2
#define S21_DEG 3

#define S21_SIGN_INDEX 127
#define S21_POSITIVE 0
#define S21_NEGATIVE 1

#define S21_TRUE 0
#define S21_FALSE 1

#define S21_SUCCESS 0
#define S21_CONVERTING_ERROR 1

#define BD_NUMBER_OF_BITS 7
#define BD_DEG 6
#define BD_MANTISSA_LEGHT 6
#define BD_MANTISSA_BITS_LEGHT 192

enum BD_SIGN_COMPARE_RESULT {
  VAL_1_BIG_VAL_2 = 1,
  VAL_2_BIG_VAL_1 = -1,
  VAL_1_VAL_2_ZERO = 2,
  VAL_1_VAL_2_ONE = -2
};

typedef struct {
  unsigned int bits[7];
} big_decimal;

typedef struct {
  int bits[4];
} s21_decimal;

/* Arithmetic Operators */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/* Comparison Operators */
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

/* Convertors and parsers */
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/* Another functions */
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

/* Secondary functions */
void s21_init(s21_decimal *number);
void s21_set_zero_decimal(s21_decimal *dst);
void s21_set_sign(s21_decimal *decl, int sign);
int s21_get_sign(s21_decimal decl);
int s21_get_bit(s21_decimal decl, int index);
void s21_set_bit(s21_decimal *decl, int index, int bit);
int s21_get_scale(s21_decimal decl);
void s21_set_scale(s21_decimal *decl, int scale);
int s21_mul_ten(s21_decimal value, s21_decimal *result);
int s21_up_scale(s21_decimal *value_1, s21_decimal *value_2);
void s21_shift_left(s21_decimal *number, int i);
int s21_shift_divide_by_10(s21_decimal *dst);

int s21_valid_value_int(int src);
int s21_valid_value_float(float src);
int s21_valid_value_decimal(s21_decimal src);

int s21_fraction(float value);
void s21_div_10(s21_decimal *value, int exp);

int s21_get_exp_float(float src);
/* Big Decimal Core. */
void big_decimal_init(big_decimal *a);
void s21_decimal_to_big_decimal(s21_decimal src, big_decimal *dst);
void big_decimal_to_s21_decimal(big_decimal src, s21_decimal *dst);
void big_decimal_copy(big_decimal src, big_decimal *dst);

void big_decimal_set_sign(big_decimal *dst, int sign);
int big_decimal_get_sign(big_decimal src);

int big_decimal_get_scale(big_decimal dst);
void big_decimal_set_scale(big_decimal *dst, int scale);

int big_decimal_is_zero(big_decimal src);

int big_decimal_get_bit(big_decimal decl, int index);
void big_decimal_set_bit(big_decimal *dst, int index, int bit);

int big_decimal_left_shift(big_decimal *src);
void big_decimal_right_shift(big_decimal *src);

int big_decimal_mantissa_is_bigger_or_equal(big_decimal val_1,
                                            big_decimal val_2);

int big_decimal_mantissa_add(big_decimal val_1, big_decimal val_2,
                             big_decimal *dst);
void big_decimal_mantissa_sub(big_decimal val_1, big_decimal val_2,
                              big_decimal *dst);
int big_decimal_mantissa_mul(big_decimal val_1, big_decimal val_2,
                             big_decimal *dst);
big_decimal big_decimal_mantissa_div(big_decimal val_1, big_decimal val_2,
                                     big_decimal *dst);

void big_decimal_equal_scales(big_decimal *val_1, big_decimal *val_2);
int big_decimal_sign_compare(big_decimal val_1, big_decimal val_2);
big_decimal big_decimal_scale_up(big_decimal src);
big_decimal big_decimal_normalization(big_decimal src, int scale);
int big_decimal_compare(big_decimal val_1, big_decimal val_2);

int big_decimal_scale_processor(big_decimal *bd_result, big_decimal *bd_buffer,
                                int scale);
int big_decimal_bank_round(big_decimal bd_buffer, big_decimal *bd_result,
                           big_decimal *bd_value_1, int scale);

#endif
