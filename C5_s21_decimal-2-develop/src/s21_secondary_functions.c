#include "s21_decimal.h"

/// @brief зануляем биты
/// @param dst
void s21_set_zero_decimal(s21_decimal *dst) {
  /*
  This function equates all values ​​to null.
  */
  if (dst != NULL) {
    dst->bits[S21_LOW] = 0;
    dst->bits[S21_MID] = 0;
    dst->bits[S21_HIGH] = 0;
    dst->bits[S21_DEG] = 0;
  }
}

/// @brief устанавливаем знак в 31 бит[3]
/// @param decl
void s21_set_sign(s21_decimal *decl, int sign) {
  if (sign)
    decl->bits[3] = decl->bits[3] | 0x80000000;
  else
    decl->bits[3] = decl->bits[3] & 0xffffffff;
}

/// @brief Получаем знак числа
/// @param decl
/// @return 1 если знак минус и 0 если число положительное
int s21_get_sign(s21_decimal decl) { return (decl.bits[3] & 1u << 31) != 0; }

/// @brief возвращает из числа decl бит хранящийся в бите с номером index
/// @param decl
/// @param index номер бита
/// @return возвращает значение бита 1 или 0
int s21_get_bit(s21_decimal decl, int index) {
  int num_int = index / 32;
  int num_bit = index % 32;
  return (decl.bits[num_int] & (1u << num_bit)) != 0;
}

/// @brief Устаналивает значение bit в decl с номером index
/// @param decl
/// @param index индекс бита
/// @param bit значение бита 1 или 0
void s21_set_bit(s21_decimal *decl, int index, int bit) {
  int num_int = index / 32;
  int num_bit = index % 32;
  if (bit == 1) {
    decl->bits[num_int] |= (1u << num_bit);
  } else {
    decl->bits[num_int] &= (~((1u) << num_bit));
  }
}

/// @brief возвращает масштаб для десятичного числа
/// @param decl
/// @return масштаб
int s21_get_scale(s21_decimal decl) {
  int scale = 0;
  for (int i = START_EXTRA + 23; i >= START_EXTRA + 16; i--) {
    scale <<= 1;
    scale |= s21_get_bit(decl, i);
  }
  return scale;
}

/// @brief устанавливает масштаб десятичного числа decl равным scale
/// @param decl
/// @param scale масштаб
void s21_set_scale(s21_decimal *decl, int scale) {
  for (int i = START_EXTRA + 16; i < START_EXTRA + 23; i++) {
    s21_set_bit(decl, i, scale & 1);
    scale >>= 1;
  }
}

/// @brief функция сдвигает число на заданное количество битов влево
/// @param number
/// @param i шаг сдвига
void s21_shift_left(s21_decimal *number, int i) {
  do {
    for (int j = 95; j >= 0; j--) {
      if (j == 0)
        s21_set_bit(number, j, 0);
      else
        s21_set_bit(number, j, s21_get_bit(*number, j - 1));
    }
    i--;
  } while (i > 0);
}

/// @brief увеличивает масштаб одного числа до масштаба другого числа
/// @param value_1
/// @param value_2
/// @return
int s21_up_scale(s21_decimal *value_1, s21_decimal *value_2) {
  int scale_1 = s21_get_scale(*value_1), scale_2 = s21_get_scale(*value_2),
      error = 0;
  s21_decimal temp_result;
  s21_decimal temp_result1 = {{0, 0, 0, 0}};
  if (scale_1 > scale_2) {
    temp_result = *value_2;
    for (int i = 0; i < scale_1 - scale_2; i++) {
      if ((error = s21_mul_ten(temp_result, &temp_result1)) == 2) break;
      temp_result = temp_result1;
    }
    if (!error) *value_2 = temp_result;
    if (error == 2) *value_2 = temp_result1;
    s21_set_scale(value_2, scale_1);
  } else if (scale_1 < scale_2) {
    temp_result = *value_1;
    for (int i = 0; i < scale_2 - scale_1; i++) {
      if ((error = s21_mul_ten(temp_result, &temp_result1)) == 2) break;
      temp_result = temp_result1;
    }
    if (!error) *value_1 = temp_result;
    if (error == 2) *value_1 = temp_result1;
    s21_set_scale(value_1, scale_2);
  }
  return error;
}

/// @brief умножаем десятичное число на 10
/// @param value число которое умножаем
/// @param result результат умножения
/// @return возвращает flag 0 если все отработано хорошо и 2 если
/// ошибка(переполнение)
int s21_mul_ten(s21_decimal value, s21_decimal *result) {
  s21_decimal bleach = {0};
  *result = bleach;
  s21_decimal val1 = value, val2 = value;
  int temp = 0, flag = 0;
  s21_shift_left(&val1, 1);
  s21_shift_left(&val2, 3);
  for (int i = 0; i < 96; i++) {
    int bit1 = s21_get_bit(val1, i);
    int bit2 = s21_get_bit(val2, i);
    if (!bit1 && !bit2) {
      if (!temp)
        s21_set_bit(result, i, 0);
      else {
        s21_set_bit(result, i, 1);
        temp = 0;
      }

    } else if (bit1 && bit2) {
      if (!temp) {
        s21_set_bit(result, i, 0);
        temp = 1;
      } else {
        s21_set_bit(result, i, 1);
        temp = 1;
      }
    } else {
      if (!temp) {
        s21_set_bit(result, i, 1);
        temp = 0;
      } else {
        s21_set_bit(result, i, 0);
        temp = 1;
      }
    }
    if ((i == 95 && temp == 1) && (bit1 || bit2)) {
      flag = 2;
      s21_set_zero_decimal(result);
    }
  }
  if (s21_get_sign(value)) s21_set_sign(result, S21_NEGATIVE);
  return flag;
}

void s21_init(s21_decimal *number) {
  number->bits[3] = 0b00000000000000000000000000000000;
  number->bits[2] = 0b00000000000000000000000000000000;
  number->bits[1] = 0b00000000000000000000000000000000;
  number->bits[0] = 0b00000000000000000000000000000000;
}

int s21_shift_divide_by_10(s21_decimal *dst) {
  unsigned long long int transfer = 0;
  for (int i = 2; i >= 0; i--) {
    unsigned long long int long_int = 0;
    long_int = (unsigned long long int)(dst->bits[i] & 0xFFFFFFFF) + transfer;
    dst->bits[i] = (unsigned int)((long_int / 10) & 0xFFFFFFFF);
    transfer = 0;
    transfer = ((long_int % 10) & 0xFFFFFFFF) << 32;
  }
  return S21_SUCCESS;
}

int s21_get_exp_float(float src) {
  union union_src {
    float asFloat;
    int asInteger;
  };
  union union_src u_src;  // создаем переменную u_src класса union_src
  u_src.asFloat = src;
  return ((u_src.asInteger >> 23) & 0xFF) - 127;
}

int s21_valid_value_float(float src) {
  int result = 1;
  if (src > -1e-28 && src != 0.0 && src < 1e-28) {
    result = 0;
  } else if (src == S21_INFINITY) {
    result = 0;
  } else if (src == S21_NEGATIVE_INFINITY) {
    result = 0;
  } else if (isnan(src)) {
    result = 0;
  } else if (src > 79228162514264337593543950335.0) {
    result = 0;
  } else if (src < -79228162514264337593543950335.0) {
    result = 0;
  }
  return result;
}

int s21_valid_value_decimal(s21_decimal src) {
  int result = 1;
  if (src.bits[S21_DEG] & 0xFFFF) {
    result = 0;
  } else if (s21_get_scale(src) > 28) {
    result = 0;
  } else if (src.bits[S21_DEG] & (0x7F << 24)) {
    result = 0;
  }
  return result;
}