#include "s21_decimal.h"

void big_decimal_init(big_decimal *a) {
  for (int i = 0; i < BD_NUMBER_OF_BITS; i++) a->bits[i] = 0;
}

void s21_decimal_to_big_decimal(s21_decimal src, big_decimal *dst) {
  for (int i = 0; i < BD_MANTISSA_LEGHT; i++)
    dst->bits[i] = (i < 3) ? src.bits[i] : 0;
  dst->bits[BD_DEG] = src.bits[S21_DEG];
}

void big_decimal_to_s21_decimal(big_decimal src, s21_decimal *dst) {
  for (int i = 0; i < S21_D_NUMBER_OF_BITS; i++)
    dst->bits[i] = (i < 3) ? src.bits[i] : src.bits[BD_DEG];
}

void big_decimal_copy(big_decimal src, big_decimal *dst) {
  for (int i = 0; i < BD_NUMBER_OF_BITS; i++) dst->bits[i] = src.bits[i];
}

//  Не проверена на тестах - различия в реализации!
void big_decimal_set_sign(big_decimal *dst, int sign) {
  unsigned int degree = 0xFF0000 & dst->bits[BD_DEG];
  dst->bits[BD_DEG] = (sign == S21_POSITIVE) ? 0 : 0x80000000;
  dst->bits[BD_DEG] += degree;
}

int big_decimal_get_sign(big_decimal src) {
  return (0x80000000 & src.bits[BD_DEG]) > 0;
}

int big_decimal_get_scale(big_decimal dst) {
  int mask = 0b11111111 << 16;
  int scale = (dst.bits[BD_DEG] & mask) >> 16;
  return scale;
}

void big_decimal_set_scale(big_decimal *dst, int scale) {
  int sign = big_decimal_get_sign(*dst);
  dst->bits[BD_DEG] = scale << 16;
  big_decimal_set_sign(dst, sign);
}

int big_decimal_is_zero(big_decimal src) {
  int result = S21_FALSE;
  for (int i = 0; i < BD_MANTISSA_LEGHT; i++) {
    if (src.bits[i] != 0) {
      result = S21_TRUE;
      break;
    }
  }
  return result;
}

int big_decimal_get_bit(big_decimal decl, int index) {
  int num_int = index / 32;
  int num_bit = index % 32;
  return (decl.bits[num_int] & (1u << num_bit)) >> num_bit;
}

void big_decimal_set_bit(big_decimal *dst, int index, int bit) {
  int num_int = index / 32;
  int num_bit = index % 32;
  if (bit == 1) {
    dst->bits[num_int] |= (1u << num_bit);
  } else {
    dst->bits[num_int] &= (~((1u) << num_bit));
  }
}

int big_decimal_left_shift(big_decimal *src) {
  int result = S21_SUCCESS;
  char bit_array[6] = {0};
  for (int i = 0; i < BD_MANTISSA_LEGHT; i++)
    bit_array[i] = big_decimal_get_bit(*src, 32 * (1 + i) - 1);
  if (!bit_array[5]) {
    src->bits[0] <<= 1;
    for (int j = 1; j < BD_MANTISSA_LEGHT; j++) {
      src->bits[j] <<= 1;
      big_decimal_set_bit(src, 32 * j, bit_array[j - 1]);
    }
  } else
    result = S21_CONVERTING_ERROR;
  return result;
}

void big_decimal_right_shift(big_decimal *src) {
  char bit_array[5] = {0};
  for (int i = 0; i < 5; i++)
    bit_array[i] = big_decimal_get_bit(*src, 32 * (i + 1));
  src->bits[5] >>= 1;
  for (int j = 4; j >= 0; j--) {
    src->bits[j] >>= 1;
    big_decimal_set_bit(src, (j + 1) * 32 - 1, bit_array[j]);
  }
}

int big_decimal_mantissa_is_bigger_or_equal(big_decimal val_1,
                                            big_decimal val_2) {
  int result = S21_FALSE;
  for (int i = BD_MANTISSA_LEGHT - 1; i >= 0; i--) {
    if (val_1.bits[i] < val_2.bits[i]) {
      result = S21_TRUE;
      break;
    } else if (val_1.bits[i] == val_2.bits[i]) {
      continue;
    } else {
      result = S21_FALSE;
      break;
    }
  }
  return result;
}

int big_decimal_mantissa_add(big_decimal val_1, big_decimal val_2,
                             big_decimal *dst) {
  int result = S21_SUCCESS;
  char bit_transfer = 0;
  big_decimal_init(dst);
  for (int i = 0; i < BD_MANTISSA_BITS_LEGHT; i++) {
    char bit_write = (char)big_decimal_get_bit(val_1, i) +
                     (char)big_decimal_get_bit(val_2, i) + bit_transfer;
    if (bit_write > 1) {
      bit_transfer = 1;
      bit_write -= 2;
    } else
      bit_transfer = 0;
    big_decimal_set_bit(dst, i, bit_write);
  }
  if (bit_transfer) result = S21_FALSE;
  return result;
}

void big_decimal_mantissa_sub(big_decimal val_1, big_decimal val_2,
                              big_decimal *dst) {
  big_decimal_init(dst);
  for (int i = 0; i < BD_MANTISSA_BITS_LEGHT; i++) {
    int bit_val_1 = big_decimal_get_bit(val_1, i);
    int bit_val_2 = big_decimal_get_bit(val_2, i);
    if (bit_val_1 >= bit_val_2)
      big_decimal_set_bit(dst, i, bit_val_1 - bit_val_2);
    else {
      int j = i + 1;
      while (!big_decimal_get_bit(val_1, j)) j++;
      big_decimal_set_bit(&val_1, j, 0);
      for (j -= 1; j > i; j--) big_decimal_set_bit(&val_1, j, 1);
      big_decimal_set_bit(dst, i, 1);
    }
  }
}

int big_decimal_mantissa_mul(big_decimal val_1, big_decimal val_2,
                             big_decimal *dst) {
  int result = S21_SUCCESS;
  big_decimal buffer;
  big_decimal_init(&buffer);
  big_decimal_init(dst);
  for (int i = 0; i < BD_MANTISSA_BITS_LEGHT && !result; i++) {
    if (big_decimal_get_bit(val_1, i)) {
      big_decimal_copy(val_2, &buffer);
      for (int j = 0; j < i && !result; j++)
        result = big_decimal_left_shift(&buffer);
      if (!result) big_decimal_mantissa_add(buffer, *dst, dst);
    }
  }
  return result;
}

big_decimal big_decimal_mantissa_div(big_decimal val_1, big_decimal val_2,
                                     big_decimal *dst) {
  big_decimal buffer;
  big_decimal one_bd;
  big_decimal_init(dst);
  while (big_decimal_mantissa_is_bigger_or_equal(val_1, val_2)) {
    int exp = 0;
    big_decimal_init(&one_bd);
    one_bd.bits[0] = 1;
    big_decimal_copy(val_2, &buffer);
    while (big_decimal_mantissa_is_bigger_or_equal(val_1, buffer)) {
      big_decimal_left_shift(&buffer);
      exp++;
    }
    big_decimal_right_shift(&buffer);
    big_decimal_mantissa_sub(val_1, buffer, &val_1);
    exp--;
    while (exp) {
      big_decimal_left_shift(&one_bd);
      exp--;
    }
    big_decimal_mantissa_add(one_bd, *dst, dst);
  }
  return val_1;
}

void big_decimal_equal_scales(big_decimal *val_1, big_decimal *val_2) {
  big_decimal ten_bd;
  big_decimal_init(&ten_bd);
  ten_bd.bits[0] = 10;
  int scale_val_1 = big_decimal_get_scale(*val_1);
  int scale_val_2 = big_decimal_get_scale(*val_2);
  while (scale_val_1 < scale_val_2) {
    big_decimal_mantissa_mul(*val_1, ten_bd, val_1);
    scale_val_1++;
  }
  while (scale_val_1 > scale_val_2) {
    big_decimal_mantissa_mul(*val_2, ten_bd, val_2);
    scale_val_2++;
  }
  big_decimal_set_scale(val_1, scale_val_1);
  big_decimal_set_scale(val_2, scale_val_2);
}

// int big_decimal_sign_compare(big_decimal val_1, big_decimal val_2) {
//   int result;
//   int val_1_sign = big_decimal_get_sign(val_1);
//   int val_2_sign = big_decimal_get_sign(val_2);
//   if (!val_1_sign && val_2_sign) result = VAL_1_BIG_VAL_2;
//   if (val_1_sign && !val_2_sign) result = VAL_2_BIG_VAL_1;
//   if (!val_1_sign && !val_2_sign) result = VAL_1_VAL_2_ZERO;
//   if (val_1_sign && val_2_sign) result = VAL_1_VAL_2_ONE;
//   return result;
// }

// big_decimal big_decimal_scale_up(big_decimal src) {
//   unsigned long long int buffer = 0;
//   big_decimal result;
//   big_decimal_init(&result);
//   for (int i = 0; i < BD_MANTISSA_LEGHT; i++) {
//     buffer += (unsigned long long int)src.bits[i] * 10;
//     result.bits[i] = (unsigned int)buffer;
//     buffer >>= 32;
//   }
//   return result;
// }

// big_decimal big_decimal_normalization(big_decimal src, int scale) {
//   while (scale) {
//     src = big_decimal_scale_up(src);
//   }
//   return src;
// }

// int big_decimal_compare(big_decimal val_1, big_decimal val_2) {
//   int result = 0;
//   int val_1_scale = big_decimal_get_scale(val_1);
//   int val_2_scale = big_decimal_get_scale(val_2);
//   if (val_1_scale > val_2_scale)
//     val_2 = big_decimal_normalization(val_2, val_1_scale - val_2_scale);
//   if (val_1_scale < val_2_scale)
//     val_1 = big_decimal_normalization(val_1, val_2_scale - val_1_scale);
//   for (int i = BD_MANTISSA_LEGHT - 1; i >= 0; i--) {
//     if (val_1.bits[i] > val_2.bits[i]) {
//       result = VAL_1_BIG_VAL_2;
//       break;
//     } else if (val_1.bits[i] < val_2.bits[i]) {
//       result = VAL_2_BIG_VAL_1;
//       break;
//     }
//   }
//   return result;
// }

int big_decimal_scale_processor(big_decimal *bd_result, big_decimal *bd_buffer,
                                int scale) {
  big_decimal bd_ten;
  big_decimal_init(&bd_ten);
  bd_ten.bits[0] = 10;
  while ((bd_result->bits[5] || bd_result->bits[4] || bd_result->bits[3]) &&
         scale) {
    *bd_buffer = big_decimal_mantissa_div(*bd_result, bd_ten, bd_result);
    scale--;
  }
  return scale;
}

int big_decimal_bank_round(big_decimal bd_buffer, big_decimal *bd_result,
                           big_decimal *bd_value_1, int scale) {
  int bits_buffer = bd_buffer.bits[0];
  int response = 0;
  big_decimal bd_ten;
  big_decimal_init(&bd_ten);
  bd_ten.bits[0] = 10;

  if (!scale &&
      (bd_result->bits[5] || bd_result->bits[4] || bd_result->bits[3])) {
    if (big_decimal_get_sign(*bd_result))
      response = 2;
    else
      response = 1;
  } else {
    if (bits_buffer > 5) {
      bd_ten.bits[0] = 1;
      response = big_decimal_mantissa_add(*bd_result, bd_ten, bd_result);
    } else if (bits_buffer == 5) {
      bd_buffer = big_decimal_mantissa_div(*bd_result, bd_ten, bd_value_1);
      int bits_buffer_2 = bd_buffer.bits[0];
      if (bits_buffer_2 % 2 == 1) {
        bd_ten.bits[0] = 1;
        response = big_decimal_mantissa_add(*bd_result, bd_ten, bd_result);
      }
    }
  }
  return response;
}