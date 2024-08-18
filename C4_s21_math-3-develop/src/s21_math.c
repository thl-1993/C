#include "s21_math.h"

int s21_isnan(double x) { return (x != x); }

int s21_isinf(double x) {
  int result = 0;
  if (x == S21_INFINITY) result = 1;
  if (x == -S21_INFINITY) result = -1;
  return result;
}

int s21_isnull(double x) {
  int result = 0;
  if (1 / x == S21_INFINITY) result = 1;
  return result;
}

int s21_abs(int x) {
  /*| вычисляет абсолютное значение целого числа |*/
  int result = x;
  if (result < 0) result *= -1;
  if (!result) result = 0;
  return result;
}
long double s21_acos(double x) {
  /*| вычисляет арккосинус |*/
  long double result = S21_M_PI_2 - s21_asin(x);
  return result;
}

long double s21_asin(double x) {
  /*| вычисляет арксинус |*/
  long double result = 0.0;
  long double value = x;

  if (x < 0) value *= -1;

  if (value > 0.525 && value <= 1) {
    result = S21_M_PI_2 - 2 * s21_asin(s21_sqrt((1 - value) / 2));
  } else if (value <= 0.525) {
    long double previous = 0.0;
    result = previous = value;
    for (int i = 1; i <= 57; i++) {
      long double apper_fraction = value * value * (2 * (long double)i - 1) *
                                   (2 * (long double)i - 1) *
                                   (2 * (long double)i);
      long double lower_fraction =
          4 * (long double)i * (long double)i * (2 * (long double)i + 1);

      result = result + apper_fraction / lower_fraction * previous;

      previous = apper_fraction / lower_fraction * previous;
    }
  } else {
    result = S21_NAN;
  }

  if (x < 0) result *= -1;

  return result;
}
long double s21_atan(double x) {
  /*| вычисляет арктангенс |*/
  long double result = S21_M_PI_2;
  if (s21_isnan(x)) result = S21_NAN;
  if (x < 1210000.0) result = s21_asin(x / s21_sqrt(1 + s21_pow(x, 2)));
  if (x < 0) result = -s21_atan(-x);
  return result;
}
long double s21_ceil(double x) {
  /*| возвращает ближайшее целое число, не меньшее заданного значения |*/
  long double result;
  if (s21_isnan(x)) {
    result = S21_NAN;
  } else if (s21_isinf(x)) {
    if (s21_isinf(x) == 1) {
      result = S21_INFINITY;
    } else {
      result = -S21_INFINITY;
    }
  } else if (x == 0) {
    if (1 / x == S21_INFINITY)
      result = 0.0L;
    else
      result = -0.0L;
  } else if (s21_fmod(x, 1.) == 0.) {
    result = x;
  } else if (x > 0) {
    result = x + 1 - s21_fmod(x, 1.);
  } else {
    result = x - s21_fmod(x, 1.);
  }
  return result;
}

long double s21_cos(double x) {
  /*| вычисляет косинус |*/
  x = s21_fmod(x, 2 * S21_M_PI);
  long double result = 1.0;
  if (s21_isinf(x)) {
    result = S21_NAN;
  } else {
    int i = 2;
    long double term = 1.0;
    while (s21_fabs(term) > EPS) {
      term *= -x * x / (i * (i - 1));
      result += term;
      i += 2;
    }
  }
  return result;
}
long double s21_exp(double x) {
  /*| возвращает значение e, возведенное в заданную степень |*/
  long double result = 1;
  if (s21_isnan(x)) {
    result = S21_NAN;
  } else if (s21_isinf(x) == 1) {
    result = S21_INFINITY;
  } else if (s21_isinf(x) == -1) {
    result = 0;
  } else if (x > 0 && x < 710) {
    long double temp = 1;
    int count = 1;
    while (temp > EPS) {
      temp = temp * (x / count);
      result += temp;
      count++;
    }
  } else if (x < 0) {
    result = 1 / s21_exp(-x);
  } else if (x >= 710) {
    result = S21_INFINITY;
  }
  return result;
}

long double s21_fabs(double x) {
  /*| вычисляет абсолютное значение числа с плавающей точкой |*/
  double result = x;
  if (result < 0) result *= -1;
  if (!result) result = 0;
  return result;
}

long double s21_floor(double x) {
  /*| возвращает ближайшее целое число, не превышающее заданное значение |*/
  long double result;
  if (s21_isnan(x)) {
    result = S21_NAN;
  } else if (s21_isinf(x)) {
    if (s21_isinf(x) == 1) {
      result = S21_INFINITY;
    } else {
      result = -S21_INFINITY;
    }
  } else if (x == 0) {
    if (s21_isnull(x))
      result = 0.0L;
    else
      result = -0.0L;
  } else if (s21_fmod(x, 1.) == 0.) {
    result = x;
  } else if (x > 0) {
    result = x - s21_fmod(x, 1.);
  } else {
    result = x - 1. - s21_fmod(x, 1.);
  }
  return result;
}

long double s21_fmod(double x, double y) {
  /*| остаток операции деления с плавающей точкой |*/
  double result;
  if (s21_isinf(x) || s21_isnan(x) || s21_isnan(y) ||
      (y == 0 && !s21_isinf(y))) {
    result = S21_NAN;
  } else if (!x) {
    if (s21_isnull(x)) {
      result = 0.0L;
    } else {
      result = -0.0L;
    }
  } else if (s21_isinf(y)) {
    result = x;
  } else {
    result = x - (y * ((long long int)(x / y)));
    if (x < 0 && !result) result = -result;
  }
  return result;
}

long double s21_pow(double base, double exp) {
  /*| возводит число в заданную степень |*/
  long double result = 0;
  int sign = base < 0 ? -1 : 1;
  if (base == 1)
    result = 1;
  else if (s21_isnan(exp))
    result = S21_NAN;
  else if (!exp)
    result = 1;
  else if (1 / base == S21_INFINITY) {
    if (exp < 0 || exp == -S21_INFINITY)
      result = S21_INFINITY;
    else
      result = 0;
  } else if (1 / base == -S21_INFINITY) {
    if (exp == -S21_INFINITY)
      result = S21_INFINITY;
    else if (exp == -1)
      result = -S21_INFINITY;
    else if (exp == S21_INFINITY)
      result = 0;
    else if (s21_fabs(s21_fmod(exp, 2)) == 1)
      result = (exp > 0) ? -0.0L : -S21_INFINITY;
    else
      result = (exp > 0) ? 0.0L : S21_INFINITY;
  } else if (s21_isnan(base))
    result = S21_NAN;
  else if (base == -1) {
    if (s21_fabs(s21_fmod(exp, 2)) == 1)
      result = -1;
    else if (!s21_fabs(s21_fmod(exp, 2)) || s21_isinf(exp))
      result = 1;
    else
      result = S21_NAN;
  } else if (s21_isinf(base) == 1) {
    if (exp < 0 || exp == -S21_INFINITY)
      result = 0;
    else
      result = S21_INFINITY;
  } else if (s21_isinf(base) == -1) {
    if (exp == S21_INFINITY)
      result = S21_INFINITY;
    else if (exp == -S21_INFINITY)
      result = 0.0L;
    else if (s21_fabs(s21_fmod(exp, 2)) == 1 && exp != S21_INFINITY)
      result = (exp > 0) ? -S21_INFINITY : -0.0L;
    else
      result = (exp > 0) ? S21_INFINITY : 0.0L;
  } else if (exp == S21_INFINITY)
    result = s21_fabs(base) < 1 ? 0 : S21_INFINITY;
  else if (exp == -S21_INFINITY)
    result = s21_fabs(base) > 1 ? 0 : S21_INFINITY;
  else if (base == -S21_INFINITY && exp == -S21_INFINITY)
    result = 0;
  else if (base == -S21_INFINITY && !s21_isnan(exp))
    result = exp < 0 ? 0 : S21_INFINITY;
  else if (base < 0 && exp != (long long int)exp)
    result = S21_NAN;

  else {
    result = s21_exp(exp * s21_log(base * sign));
    if (s21_fmod(exp, 2)) result *= sign;
  }
  return result;
}

long double s21_sin(double x) {
  /*| вычисляет синус |*/
  x = s21_fmod(x, 2 * S21_M_PI);
  long double result = x;
  if (s21_isinf(x)) {
    result = S21_NAN;
  } else {
    long double term = x;
    int i = 3;
    while (term > EPS || term < -EPS) {
      term *= -x * x / ((i - 1) * i);
      result += term;
      i += 2;
    }
  }
  return result;
}
long double s21_sqrt(double x) {
  /*| вычисляет квадратный корень |*/
  long double result = x;
  if (x == -S21_INFINITY) {
    result = S21_NAN;
  }
  if (x == S21_INFINITY) {
    result = S21_INFINITY;
  } else {
    if (x >= 0) {
      long double temp = x;
      while (s21_fabs(temp) > EPS) {
        temp = result;
        result = 0.5 * (result + (x / result));
        temp -= result;
      }
    } else
      result = S21_NAN;
  }
  return result;
}
long double s21_tan(double x) {
  /*| вычисляет тангенс |*/
  long double result = S21_NAN;
  if (!s21_isinf(x)) result = s21_sin(x) / s21_cos(x);
  return result;
}
long double log_taylor(long double x) {
  long double result = 0;
  long double term = -1;
  for (int i = 1; i < 50; i++) {
    term *= -x;
    result += term / i;
  }
  return result;
}

long double log_taylor2(long double x) {
  long double result = S21_M_LN2;
  long double term = -1;
  for (int i = 1; i < 50; i++) {
    term *= (-x / 2);
    result += term / i;
  }
  return result;
}

long double s21_log(double x) {
  /*| вычисляет натуральный логарифм |*/
  int k = 0;
  long double result;

  if (x < 0) {
    result = S21_NAN;
  } else if (x == 0) {
    result = -S21_INFINITY;
  } else if (x == S21_INFINITY) {
    result = S21_INFINITY;
  } else {
    long double buf = x;
    if (buf > 2) {
      do {
        buf = buf / 2;
        k++;
      } while (buf > 2);
    }
    if (buf < 1) {
      do {
        buf = buf * 2;
        k--;
      } while (buf < 1);
    }
    if (buf <= 1.5)
      result = (log_taylor(buf - 1) + k * S21_M_LN2);
    else
      result = (log_taylor2(buf - 2) + k * S21_M_LN2);
  }
  return result;
}