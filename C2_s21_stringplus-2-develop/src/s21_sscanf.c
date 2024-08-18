#include "s21_string.h"

#define S21_SSCANF_FLAGS "cdieEfgGosuxXpn"
#define S21_LENGTH "hlL"
#define S21_NUMBERS "1234567890"
#define S21_NUMBERS_OCT "12345670"
#define S21_NUMBERS_HEX "0123456789ABCDEFabcdef"
#define S21_NUMBERS_HEX_UP "0123456789ABCDEF"
#define S21_NUMBERS_HEX_LOW "0123456789abcdef"
#define S21_NUMBERS_HEX_SYMBOLS_UP "ABCDEF"

#define S21_FLOAT_MAX 3.40282347e+38
#define S21_FLOAT_MIN 1.17549435e-38
#define S21_LONG_LONG_INT_MAX 9223372036854775807
#define S21_LONG_LONG_INT_MIN -9223372036854775807 - 1
#define S21_UNSIGNED_LONG_LONG_INT_MAX 18446744073709551615

#define S21_NAN 0.0 / 0.0L
#define S21_INFINITY 1.0 / 0.0L

typedef struct {
  char flag;
  float width;
  float accurancy;
  int length;  // h - 1, l - 2, L - 3
  char specifier;
  int star;
} flags;

void null_value(flags *value);

int format_counter(char **pp_format, int *start);

void flag_input(flags *value, char **pp_format);

void s21_isnumber(long double *number, char symbol, int status, flags *flag);

void s21_isnumber_u(unsigned long long int *number, char symbol, int *status,
                    flags *flag);

void status_u(unsigned long long int *number, int status);

void s21_first_format_flag_position(char **pp_format);

char s21_sscanf_c(char **pp_format, char **pp_string, int *sscanf_result,
                  flags *value);

long long int s21_sscanf_d(char **pp_format, char **pp_string, flags *value,
                           int *sscanf_result);

long double s21_sscanf_f(char **pp_format, char **pp_string, flags *value,
                         int *sscanf_result);

void s21_sscanf_s(char **pp_format, char **pp_string, flags *value);

unsigned long long int s21_sscanf_u(char **pp_format, char **pp_string,
                                    flags *value, int *sscanf_result);

unsigned long long int s21_sscanf_o(char **pp_format, char **pp_string,
                                    flags *value, int *sscanf_result);

unsigned long long int s21_sscanf_p(char **pp_format, char **pp_string,
                                    flags *value, int *sscanf_result);

unsigned long long int s21_sscanf_x(char **pp_format, char **pp_string,
                                    flags *value, int *sscanf_result);

long long int s21_sscanf_i(char **pp_format, char **pp_string, flags *value,
                           int *sscanf_result);

int s21_min(int a, int b);

void space_pointer(char **pp_string);

int null_string_test(char **pp_string);

int result_test(int result_1, int result_2);

void twins_check(char **pp_format, char **pp_string);

void is_const(long double *result, char **pp_string);

/*===================s21_sscanf====================*/

int s21_sscanf(char *str, char *format, ...) {
  char *p_string = &str[0];
  char *p_string_n = &str[0];
  char *p_format = &format[0];
  const char *cp_format = &format[0];
  int result = null_string_test(&p_string);
  int result_buffer = result;
  flags value = {.flag = '\0',
                 .width = 0.0L,
                 .accurancy = 0.0L,
                 .length = 0,
                 .specifier = '\0',
                 .star = 0.0L};

  char *p_c = s21_NULL;
  short int *p_hd = s21_NULL;
  int *p_d = s21_NULL;
  long int *p_ld = s21_NULL;
  long long int *p_Ld = s21_NULL;

  unsigned short int *p_hu = s21_NULL;
  unsigned int *p_u = s21_NULL;
  unsigned long int *p_lu = s21_NULL;
  unsigned long long int *p_Lu = s21_NULL;

  float *p_f = s21_NULL;
  double *p_lf = s21_NULL;
  long double *p_Lf = s21_NULL;

  void **p_p = s21_NULL;

  va_list ap;
  va_start(ap, format);

  if (*p_format == '%') {
    while (*p_format == '%' && *p_string == '%') {
      p_format++;
      p_string++;
    }
    while (*p_format == '%') {
      p_format++;
    }
    p_format--;
  }

  int format_count = format_counter(&p_format, &result);
  if (!format_count) result = 0;
  if (result >= 0) {
    int run_status = 1;
    for (int i = 0; i < format_count; i++) {
      twins_check(&p_format, &p_string);
      flag_input(&value, &p_format);
      if (run_status) {
        char *p_format_buffer = p_format;
        s21_first_format_flag_position(&p_format);
        p_format--;
        if (p_format != cp_format) {
          p_format--;
          while ((*p_format == ' ' || *p_format == '\t' || *p_format == '\n') &&
                 (*p_string == ' ' || *p_string == '\t' || *p_string == '\n')) {
            p_string++;
          }
        }
        p_format = p_format_buffer;
      }
      long long int buffer_int = 0;
      unsigned long long int buffer_u_int = 0;
      long double buffer_float = 0;
      if (value.specifier == 'c' && run_status) {
        char buffer_char = 0;
        buffer_char = s21_sscanf_c(&p_format, &p_string, &result, &value);
        if (!value.star) {
          p_c = va_arg(ap, char *);
          if (result_test(result, result_buffer))
            *p_c = buffer_char;
          else
            run_status = 0;
        }
        null_value(&value);
      } else if (value.specifier == 'd' && run_status) {
        space_pointer(&p_string);
        buffer_int = s21_sscanf_d(&p_format, &p_string, &value, &result);
        if (!value.star) {
          switch (value.length) {
            case 0:
              p_d = va_arg(ap, int *);
              if (result_test(result, result_buffer))
                *p_d = buffer_int;
              else
                run_status = 0;
              break;

            case 1:
              p_hd = va_arg(ap, short int *);
              if (result_test(result, result_buffer))
                *p_hd = buffer_int;
              else
                run_status = 0;
              break;

            case 2:
              p_ld = va_arg(ap, long int *);
              if (result_test(result, result_buffer))
                *p_ld = buffer_int;
              else
                run_status = 0;
              break;

            case 3:
              p_Ld = va_arg(ap, long long int *);
              if (result_test(result, result_buffer))
                *p_Ld = buffer_int;
              else
                run_status = 0;
              break;
          }
        }
        buffer_int = 0;
        null_value(&value);
      } else if ((value.specifier == 'f' || value.specifier == 'e' ||
                  value.specifier == 'E' || value.specifier == 'g' ||
                  value.specifier == 'G') &&
                 run_status) {
        space_pointer(&p_string);
        buffer_float = s21_sscanf_f(&p_format, &p_string, &value, &result);
        if (!value.star) {
          switch (value.length) {
            case 0:
              p_f = va_arg(ap, float *);
              if (result_test(result, result_buffer))
                *p_f = buffer_float;
              else
                run_status = 0;
              break;

            case 2:
              p_lf = va_arg(ap, double *);
              if (result_test(result, result_buffer))
                *p_lf = buffer_float;
              else
                run_status = 0;
              break;

            case 3:
              p_Lf = va_arg(ap, long double *);
              if (result_test(result, result_buffer))
                *p_Lf = buffer_float;
              else
                run_status = 0;
              break;
          }
        }
        buffer_float = 0;
        null_value(&value);
      } else if (value.specifier == 's' && run_status) {
        s21_sscanf_s(&p_format, &p_string, &value);
        if (!value.star) {
          p_c = va_arg(ap, char *);
          for (int j = 0; j < (int)value.width; j++) {
            *p_c = *p_string;
            p_c++;
            p_string++;
          }
          if (value.width > 0) {
            result++;
          } else
            run_status = 0;
          *p_c = '\0';
        } else {
          for (int j = 0; j < (int)value.width; j++) {
            p_string++;
          }
        }
        null_value(&value);
      } else if (value.specifier == 'u' && run_status) {
        space_pointer(&p_string);
        buffer_u_int = s21_sscanf_u(&p_format, &p_string, &value, &result);
        if (!value.star) {
          switch (value.length) {
            case 0:
              p_u = va_arg(ap, unsigned int *);
              if (result_test(result, result_buffer))
                *p_u = (unsigned int)buffer_u_int;
              else
                run_status = 0;
              break;

            case 1:
              p_hu = va_arg(ap, unsigned short int *);
              if (result_test(result, result_buffer))
                *p_hu = (unsigned short int)buffer_u_int;
              else
                run_status = 0;
              break;

            case 2:
              p_lu = va_arg(ap, unsigned long int *);
              if (result_test(result, result_buffer))
                *p_lu = (unsigned long int)buffer_u_int;
              else
                run_status = 0;
              break;

            case 3:
              p_Lu = va_arg(ap, unsigned long long int *);
              if (result_test(result, result_buffer))
                *p_Lu = (unsigned long long int)buffer_u_int;
              else
                run_status = 0;
              break;
          }
        }
        buffer_int = 0;
        null_value(&value);
      } else if (value.specifier == 'o' && run_status) {
        space_pointer(&p_string);
        buffer_u_int = s21_sscanf_o(&p_format, &p_string, &value, &result);
        if (!value.star) {
          switch (value.length) {
            case 0:
              p_u = va_arg(ap, unsigned int *);
              if (result_test(result, result_buffer))
                *p_u = (unsigned int)buffer_u_int;
              else
                run_status = 0;
              break;

            case 1:
              p_hu = va_arg(ap, unsigned short int *);
              if (result_test(result, result_buffer))
                *p_hu = (unsigned short int)buffer_u_int;
              else
                run_status = 0;
              break;

            case 2:
              p_lu = va_arg(ap, unsigned long int *);
              if (result_test(result, result_buffer))
                *p_lu = (unsigned long int)buffer_u_int;
              else
                run_status = 0;
              break;

            case 3:
              p_Lu = va_arg(ap, unsigned long long int *);
              if (result_test(result, result_buffer))
                *p_Lu = (unsigned long long int)buffer_u_int;
              else
                run_status = 0;
              break;
          }
        }
        buffer_u_int = 0;
        null_value(&value);
      } else if ((value.specifier == 'x' || value.specifier == 'X') &&
                 run_status) {
        space_pointer(&p_string);
        buffer_u_int = s21_sscanf_x(&p_format, &p_string, &value, &result);
        if (!value.star) {
          switch (value.length) {
            case 0:
              p_u = va_arg(ap, unsigned int *);
              if (result_test(result, result_buffer))
                *p_u = (unsigned int)buffer_u_int;
              else
                run_status = 0;
              break;

            case 1:
              p_hu = va_arg(ap, unsigned short int *);
              if (result_test(result, result_buffer))
                *p_hu = (unsigned short int)buffer_u_int;
              else
                run_status = 0;
              break;

            case 2:
              p_lu = va_arg(ap, unsigned long int *);
              if (result_test(result, result_buffer))
                *p_lu = (unsigned long int)buffer_u_int;
              else
                run_status = 0;
              break;

            case 3:
              p_Lu = va_arg(ap, unsigned long long int *);
              if (result_test(result, result_buffer))
                *p_Lu = (unsigned long long int)buffer_u_int;
              else
                run_status = 0;
              break;
          }
        }
        buffer_u_int = 0;
        null_value(&value);
      } else if (value.specifier == 'n' && run_status) {
        s21_first_format_flag_position(&p_format);
        if (*p_format == 'l') {
          value.length = 2;
          p_format++;
          if (*p_format == 'l') {
            value.length = 3;
            p_format++;
          }
        } else if (*p_format == 'h') {
          value.length = 1;
          p_format++;
          if (*p_format == 'h') {
            value.length = 0;
            p_format++;
          }
        }
        if (!value.star) {
          switch (value.length) {
            case 0:
              p_u = va_arg(ap, unsigned int *);
              *p_u = p_string - p_string_n;
              break;

            case 1:
              p_hd = va_arg(ap, short int *);
              *p_hd = p_string - p_string_n;
              break;

            case 2:
              p_lu = va_arg(ap, unsigned long int *);
              *p_lu = p_string - p_string_n;
              break;

            case 3:
              p_Lu = va_arg(ap, unsigned long long int *);
              *p_Lu = p_string - p_string_n;
              break;
          }
        }
        null_value(&value);
      } else if (value.specifier == 'p' && run_status) {
        space_pointer(&p_string);
        buffer_u_int = s21_sscanf_p(&p_format, &p_string, &value, &result);
        if (!value.star) {
          p_p = va_arg(ap, void **);
          if (result_test(result, result_buffer))
            *p_p = (void *)(buffer_u_int);
          else
            run_status = 0;
        }
        null_value(&value);
      } else if (value.specifier == 'i' && run_status) {
        space_pointer(&p_string);
        buffer_int = s21_sscanf_i(&p_format, &p_string, &value, &result);
        if (!value.star) {
          switch (value.length) {
            case 0:
              p_d = va_arg(ap, int *);
              if (result_test(result, result_buffer))
                *p_d = buffer_int;
              else
                run_status = 0;
              break;

            case 1:
              p_hd = va_arg(ap, short int *);
              if (result_test(result, result_buffer))
                *p_hd = buffer_int;
              else
                run_status = 0;
              break;

            case 2:
              p_ld = va_arg(ap, long int *);
              if (result_test(result, result_buffer))
                *p_ld = buffer_int;
              else
                run_status = 0;
              break;

            case 3:
              p_Ld = va_arg(ap, long long int *);
              if (result_test(result, result_buffer))
                *p_Ld = buffer_int;
              else
                run_status = 0;
              break;
          }
        }
        buffer_int = 0;
        null_value(&value);
      }
      p_format++;
      result_buffer = result;
    }
  }
  va_end(ap);
  return result;
}

/*=================================================*/

void null_value(flags *value) {
  value->accurancy = 0.0L;
  value->flag = '\0';
  value->length = 0;
  value->width = 0.0L;
  value->star = 0.0L;
}

/*=================================================*/

void flag_input(flags *value, char **pp_format) {
  /* this funcion defines the type of the variable */
  char *p_format = *pp_format;
  while (*p_format != '%') {
    p_format++;
  }
  p_format++;
  while (!s21_strchr(S21_SSCANF_FLAGS, *p_format)) {
    p_format++;
  }
  value->specifier = *p_format;
  *pp_format = p_format;
}

/*=================================================*/

int format_counter(char **pp_format, int *start) {
  /* this function count the number of specifiers */
  char *p_format = *pp_format;
  char *p_format_start = p_format;
  int result = 0;
  char *flags = S21_SSCANF_FLAGS;
  int specifier_status = 0;
  while (*p_format != '\0') {
    if (*p_format == '%' && !specifier_status) {
      specifier_status = 1;
    } else if (*p_format == '%' && specifier_status) {
      specifier_status = 2;
    } else if (s21_strchr(flags, *p_format) && specifier_status == 1) {
      if (*p_format == 'n') {
        *start = 0;
      }
      result++;
      specifier_status = 0;
    }
    p_format++;
  }
  *pp_format = p_format_start;
  return result;
}

/*==================s21_isnumber===================*/

void s21_isnumber(long double *number, char symbol, int status, flags *flag) {
  /* this function */
  long double buffer = *number;
  unsigned int step = 0;
  if (symbol > 47 && symbol < 58) {
    step = 48;
  } else if (symbol > 96 && symbol < 103) {
    step = 87;
  } else if (symbol > 64 && symbol < 71) {
    step = 55;
  }
  unsigned int value = symbol - step;
  if (flag->specifier == 'd' || flag->specifier == 'f' ||
      flag->specifier == 'e' || flag->specifier == 'E' ||
      flag->specifier == 'g' || flag->specifier == 'G' ||
      flag->specifier == 's' || flag->specifier == 'u') {
    *number *= 10;
  } else if (flag->specifier == 'o') {
    *number *= 8;
  } else if (flag->specifier == 'x') {
    *number *= 16;
  }
  if (status) {
    *number += value;
  } else {
    *number -= value;
  }
  if (flag->specifier == 'd' || flag->specifier == 'o' ||
      flag->specifier == 'x') {
    if (status) {
      if ((long long int)*number < buffer) {
        *number = S21_LONG_LONG_INT_MAX;
      }
    } else {
      if ((long long int)*number > buffer) {
        *number = S21_LONG_LONG_INT_MIN;
      }
    }
  } else if (flag->specifier == 'f' || flag->specifier == 'e' ||
             flag->specifier == 'E') {
    if (status) {
      if (*number < buffer) {
        *number = S21_FLOAT_MAX;
      }
    } else {
      if (*number > buffer) {
        *number = S21_FLOAT_MIN;
      }
    }
  }
}

/*====================status_u=====================*/

void status_u(unsigned long long int *number, int status) {
  if (status == 0) {
    *number = -*number;
  }
}
/*=================s21_isnumber_u==================*/

void s21_isnumber_u(unsigned long long int *number, char symbol, int *status,
                    flags *flag) {
  /* this function */
  unsigned long long int buffer = *number;
  if (*status != 2) {
    unsigned int step = 0;
    if (symbol > 47 && symbol < 58) {
      step = 48;
    } else if (symbol > 96 && symbol < 103) {
      step = 87;
    } else if (symbol > 64 && symbol < 71) {
      step = 55;
    }
    unsigned int value = symbol - step;
    if (flag->specifier == 'u') {
      *number *= 10;
    } else if (flag->specifier == 'o') {
      *number *= 8;
    } else if (flag->specifier == 'x' || flag->specifier == 'X' ||
               flag->specifier == 'p') {
      *number *= 16;
    }
    *number += value;
    if (buffer >= *number) {
      *number = S21_LONG_LONG_INT_MAX;
      *number += S21_LONG_LONG_INT_MAX;
      *number += 1;
      *status = 2;
    }
  }
}

/*=================================================*/

void s21_first_format_flag_position(char **pp_format) {
  char *p_format = *pp_format;
  while (*p_format != '%') {
    p_format -= 1;
  }
  p_format++;
  *pp_format = p_format;
}

/*===================s21_sscanf_c===================*/

char s21_sscanf_c(char **pp_format, char **pp_string, int *sscanf_result,
                  flags *value) {
  char *p_format = *pp_format;
  char *p_string = *pp_string;
  char result = '\0';
  s21_first_format_flag_position(&p_format);
  if (*p_format == 'c' && *p_string != '\0') {
    result = *p_string;
    *sscanf_result += 1;
  } else if (*p_format == '*') {
    value->star = 1;
  }
  p_string++;
  *pp_format = p_format;
  *pp_string = p_string;
  return result;
}

/*===================s21_sscanf_d===================*/

long long int s21_sscanf_d(char **pp_format, char **pp_string, flags *value,
                           int *sscanf_result) {
  char *p_format = *pp_format;
  char *p_string = *pp_string;
  long double result = 0;

  s21_first_format_flag_position(&p_format);
  if (*p_format == '*') {
    value->star = 1;
    p_format++;
  }

  long double width = 0;
  int count = 0;
  int status = 1;  // показывает что число неотрицательное
  while (s21_strchr(S21_NUMBERS, *p_format)) {
    s21_isnumber(&width, *p_format, status, value);
    p_format++;
    count++;
  }
  switch (*p_format) {
    case 'h':
      value->length = 1;
      p_format++;
      if (*p_format == 'h') {
        value->length = 0;
        p_format++;
      }
      break;

    case 'l':
      value->length = 2;
      p_format++;
      if (*p_format == 'l') {
        value->length = 3;
        p_format++;
      }
      break;

    default:
      break;
  }
  char *p_buf;
  if (*p_format == 'd') {
    int len_s = 0;
    int plus_status = 1;
    if (*p_string == '-') {
      plus_status = 0;
      p_string++;
      width--;
    } else if (*p_string == '+') {
      p_string++;
      width--;
    }
    p_buf = p_string;
    while (s21_strchr(S21_NUMBERS, *p_string) && *p_string != '\0') {
      p_string++;
      len_s++;
    }
    if (count) {
      len_s = s21_min(len_s, width);
    }
    if (len_s > 0 && !value->star) {
      *sscanf_result += 1;
    }
    p_string = p_buf;
    for (int i = 0; i < len_s; i++) {
      s21_isnumber(&result, *p_string, plus_status, value);
      p_string++;
    }
    // } else {
    //   value->specifier = '\0';
  }
  *pp_format = p_format;
  *pp_string = p_string;
  return result;
}

/*===================s21_sscanf_f===================*/

long double s21_sscanf_f(char **pp_format, char **pp_string, flags *value,
                         int *sscanf_result) {
  char *p_format = *pp_format;
  char *p_string = *pp_string;
  long double result = 0;
  long double integer_result = 0;

  s21_first_format_flag_position(&p_format);
  if (*p_format == '*') {
    value->star = 1;
    p_format++;
  }

  long double width = 0;
  int count = 0;
  int status = 1;  // показывает что число неотрицательное
  int result_status = 0;
  while (s21_strchr(S21_NUMBERS, *p_format)) {
    s21_isnumber(&width, *p_format, status, value);
    p_format++;
    count++;
  }

  switch (*p_format) {
    case 'l':
      value->length = 2;
      p_format++;
      break;

    case 'L':
      value->length = 3;
      p_format++;
      break;

    default:
      break;
  }

  if (*p_format == 'f' || *p_format == 'e' || *p_format == 'E' ||
      *p_format == 'g' || *p_format == 'G') {
    value->specifier = 'f';
  }

  if (value->specifier == 'f') {
    if (*p_string == '-') {
      status = 0;
      p_string++;
      width--;
    } else if (*p_string == '+') {
      p_string++;
      width--;
    }

    is_const(&result, &p_string);
    if (result == 0) {
      while (s21_strchr(S21_NUMBERS, *p_string) && *p_string != '\0' &&
             (width > 0 || !count)) {
        s21_isnumber(&integer_result, *p_string, status, value);
        p_string++;
        width--;
        result_status = 1;
      }

      result = integer_result;
      integer_result = 0;

      if ((width > 0 || !count)) {
        int e_status = 0;
        long double e_result = 0;
        long double fractional_result = 0;
        int fractional_length = 0;
        if (*p_string == '.') {
          p_string++;
          width--;
          while (s21_strchr(S21_NUMBERS, *p_string) && *p_string != '\0' &&
                 (width > 0 || !count)) {
            s21_isnumber(&integer_result, *p_string, status, value);
            p_string++;
            fractional_length++;
            width--;
            result_status = 1;
          }
          fractional_result = integer_result;
        }

        for (int i = 0; i < fractional_length; i++) {
          fractional_result /= 10;
        }
        result += fractional_result;
        if (result_status == 1 && (width > 0 || !count) &&
            (*p_string == 'e' || *p_string == 'E')) {
          p_string++;
          width--;
          e_status = 1;
        }
        status = 1;
        if ((width > 0 || !count) &&
            ((*p_string == '+' || *p_string == '-') && e_status)) {
          if (*p_string == '-') {
            status = 0;
          }
          p_string++;
          width--;
        }
        while (s21_strchr(S21_NUMBERS, *p_string) && *p_string != '\0' &&
               (width > 0 || !count) && e_status) {
          s21_isnumber(&e_result, *p_string, 1, value);
          p_string++;
          width--;
        }
        if (e_status) {
          if (e_result > 5000) e_result = 5000;
          for (int i = 0; i < e_result; i++) {
            if (status)
              result *= 10;
            else
              result /= 10;
          }
        }
      }
    } else {
      result_status = 1;
      if (!status) result = -result;
    }
  }
  if (result_status && !value->star) {
    *sscanf_result += 1;
  }

  *pp_format = p_format;
  *pp_string = p_string;
  return result;
}

/*===================s21_sscanf_s===================*/

void s21_sscanf_s(char **pp_format, char **pp_string, flags *value) {
  char *p_format = *pp_format;
  char *p_string = *pp_string;
  long double width = 0;
  int count = 0;
  int status = 1;
  s21_first_format_flag_position(&p_format);
  if (*p_format == '*') {
    value->star = 1;
    p_format++;
  }
  while (!s21_strchr(S21_SSCANF_FLAGS, *p_format)) {
    s21_isnumber(&width, *p_format, status, value);
    p_format++;
    count++;
  }
  int len_s = 0;
  while (*p_string == ' ' || *p_string == '\n' || *p_string == '\t') {
    p_string++;
  }
  char *p_buf = p_string;
  while (*p_string != ' ' && *p_string != '\t' && *p_string != '\0' &&
         *p_string != '\n') {
    len_s++;
    p_string++;
  }
  if (count) {
    len_s = s21_min(len_s, width);
  }
  value->width = len_s;
  *pp_format = p_format;
  *pp_string = p_buf;
}

/*===================s21_sscanf_u===================*/

unsigned long long int s21_sscanf_u(char **pp_format, char **pp_string,
                                    flags *value, int *sscanf_result) {
  unsigned long long int result = 0;
  long double width = 0;
  int count = 0;
  int status = 1;
  int result_status = 0;

  char *p_format = *pp_format;
  char *p_string = *pp_string;

  s21_first_format_flag_position(&p_format);
  if (*p_format == '*') {
    value->star = 1;
    p_format++;
  }

  while (s21_strchr(S21_NUMBERS, *p_format)) {
    s21_isnumber(&width, *p_format, status, value);
    p_format++;
    count++;
  }

  if (*p_format == 'l') {
    value->length = 2;
    p_format++;
    if (*p_format == 'l') {
      value->length = 3;
      p_format++;
    }
  } else if (*p_format == 'h') {
    value->length = 1;
    p_format++;
    if (*p_format == 'h') {
      value->length = 0;
      p_format++;
    }
  }

  if (*p_format == 'u') {
    if (*p_string == '-') {
      status = 0;
      p_string++;
      width--;
    } else if (*p_string == '+') {
      p_string++;
      width--;
    }
    while (*p_string == '0') {
      p_string++;
      width--;
    }
    while (s21_strchr(S21_NUMBERS, *p_string) && *p_string != '\0' &&
           (width > 0 || !count)) {
      s21_isnumber_u(&result, *p_string, &status, value);
      p_string++;
      width--;
      result_status = 1;
    }
    status_u(&result, status);
  }
  if (result_status && !value->star) {
    *sscanf_result += 1;
  }

  *pp_format = p_format;
  *pp_string = p_string;
  return result;
}

/*===================s21_sscanf_o===================*/

unsigned long long int s21_sscanf_o(char **pp_format, char **pp_string,
                                    flags *value, int *sscanf_result) {
  unsigned long long int result = 0;
  long double width = 0;
  int count = 0;
  int status = 1;
  int result_status = 0;

  char *p_format = *pp_format;
  char *p_string = *pp_string;

  s21_first_format_flag_position(&p_format);
  if (*p_format == '*') {
    value->star = 1;
    p_format++;
  }

  while (s21_strchr(S21_NUMBERS, *p_format)) {
    s21_isnumber(&width, *p_format, status, value);
    p_format++;
    count++;
  }

  if (*p_format == 'l') {
    value->length = 2;
    p_format++;
    if (*p_format == 'l') {
      value->length = 3;
      p_format++;
    }
  } else if (*p_format == 'h') {
    value->length = 1;
    p_format++;
    if (*p_format == 'h') {
      value->length = 0;
      p_format++;
    }
  }

  if (*p_format == 'o') {
    if (*p_string == '-') {
      status = 0;
      p_string++;
      width--;
    } else if (*p_string == '+') {
      p_string++;
      width--;
    }
    if (width > 0 || !count) {
      while (*p_string == '0') {
        p_string++;
        width--;
        result_status = 1;
      }
      while (s21_strchr(S21_NUMBERS_OCT, *p_string) && *p_string != '\0' &&
             (width > 0 || !count)) {
        s21_isnumber_u(&result, *p_string, &status, value);
        p_string++;
        width--;
        result_status = 1;
      }
      status_u(&result, status);
    }
  }
  if (result_status && !value->star) {
    *sscanf_result += 1;
  }

  *pp_format = p_format;
  *pp_string = p_string;
  return result;
}

/*===================s21_sscanf_x===================*/

unsigned long long int s21_sscanf_x(char **pp_format, char **pp_string,
                                    flags *value, int *sscanf_result) {
  unsigned long long int result = 0;
  long double width = 0;
  int count = 0;
  int status = 1;
  int result_status = 0;

  char *p_format = *pp_format;
  char *p_string = *pp_string;

  s21_first_format_flag_position(&p_format);
  if (*p_format == '*') {
    value->star = 1;
    p_format++;
  }

  value->specifier = 'd';
  while (s21_strchr(S21_NUMBERS, *p_format)) {
    s21_isnumber(&width, *p_format, status, value);
    p_format++;
    count++;
  }
  value->specifier = 'x';

  if (*p_format == 'l') {
    value->length = 2;
    p_format++;
    if (*p_format == 'l') {
      value->length = 3;
      p_format++;
    }
  } else if (*p_format == 'h') {
    value->length = 1;
    p_format++;
    if (*p_format == 'h') {
      value->length = 0;
      p_format++;
    }
  }

  if ((*p_format == 'x' || *p_format == 'X') && (width > 0 || !count)) {
    int status_0x = 0;
    if (*p_string == '0') {
      status_0x = 1;
      p_string++;
      width--;
      result_status = 1;
    }
    if ((*p_string == 'x' || *p_string == 'X') && (width > 0 || !count)) {
      status_0x = 1;
      p_string++;
      width--;
      result_status = 1;
    }
    if (*p_string == '-' && !status_0x && (width > 0 || !count)) {
      status = 0;
      p_string++;
      width--;
    } else if (*p_string == '+' && !status_0x && (width > 0 || !count)) {
      p_string++;
      width--;
    }
    if (*p_string == '0' && !status_0x && (width > 0 || !count)) {
      status_0x = 2;
      p_string++;
      width--;
      result_status = 1;
    }
    if ((*p_string == 'x' || *p_string == 'X') &&
        (!status_0x || status_0x == 2) && (width > 0 || !count)) {
      p_string++;
      width--;
      result_status = 1;
    }
    while (*p_string == '0') {
      p_string++;
      width--;
    }
    while (s21_strchr(S21_NUMBERS_HEX, *p_string) && *p_string != '\0' &&
           (width > 0 || !count)) {
      s21_isnumber_u(&result, *p_string, &status, value);
      p_string++;
      width--;
      result_status = 1;
    }
    status_u(&result, status);
  }
  if (result_status && !value->star) {
    *sscanf_result += 1;
  }

  *pp_format = p_format;
  *pp_string = p_string;
  return result;
}

/*===================s21_sscanf_p===================*/

unsigned long long int s21_sscanf_p(char **pp_format, char **pp_string,
                                    flags *value, int *sscanf_result) {
  unsigned long long int result = 0;
  long double width = 0;
  int count = 0;
  int status = 1;
  int result_status = 0;

  char *p_format = *pp_format;
  char *p_string = *pp_string;

  s21_first_format_flag_position(&p_format);
  if (*p_format == '*') {
    value->star = 1;
    p_format++;
  }
  value->specifier = 'd';
  while (s21_strchr(S21_NUMBERS, *p_format)) {
    s21_isnumber(&width, *p_format, status, value);
    p_format++;
    count++;
  }
  value->specifier = 'p';
  if (*p_format == 'p' && (width > 0 || !count)) {
    int status_0x = 0;
    if (*p_string == '0') {
      status_0x = 1;
      p_string++;
      width--;
      result_status = 1;
    }
    if ((*p_string == 'x' || *p_string == 'X') && (width > 0 || !count)) {
      status_0x = 1;
      p_string++;
      width--;
      result_status = 1;
    }
    if (*p_string == '-' && !status_0x && (width > 0 || !count)) {
      status = 0;
      p_string++;
      width--;
    } else if (*p_string == '+' && !status_0x && (width > 0 || !count)) {
      p_string++;
      width--;
    }
    if (*p_string == '0' && !status_0x && (width > 0 || !count)) {
      status_0x = 2;
      p_string++;
      width--;
      result_status = 1;
    }
    if ((*p_string == 'x' || *p_string == 'X') &&
        (!status_0x || status_0x == 2) && (width > 0 || !count)) {
      p_string++;
      width--;
      result_status = 1;
    }
    while (*p_string == '0') {
      p_string++;
      width--;
    }
    while (s21_strchr(S21_NUMBERS_HEX, *p_string) && *p_string != '\0' &&
           (width > 0 || !count)) {
      s21_isnumber_u(&result, *p_string, &status, value);
      p_string++;
      width--;
      result_status = 1;
    }
    status_u(&result, status);
  }
  if (result_status && !value->star) {
    *sscanf_result += 1;
  }

  *pp_format = p_format;
  *pp_string = p_string;
  return result;
}

/*===================s21_sscanf_i===================*/

long long int s21_sscanf_i(char **pp_format, char **pp_string, flags *value,
                           int *sscanf_result) {
  char *p_format = *pp_format;
  char *p_string = *pp_string;
  long double result = 0;
  long double width = 0;
  int count = 0;
  int status = 1;
  int result_status = 0;

  s21_first_format_flag_position(&p_format);
  if (*p_format == '*') {
    value->star = 1;
    p_format++;
  }

  value->specifier = 'd';

  while (s21_strchr(S21_NUMBERS, *p_format)) {
    s21_isnumber(&width, *p_format, status, value);
    p_format++;
    count++;
  }

  if (*p_format == 'l') {
    value->length = 2;
    p_format++;
    if (*p_format == 'l') {
      value->length = 3;
      p_format++;
    }
  } else if (*p_format == 'h') {
    value->length = 1;
    p_format++;
    if (*p_format == 'h') {
      value->length = 0;
      p_format++;
    }
  }

  if (*p_format == 'i') {
    if (*p_string == '-') {
      status = 0;
      p_string++;
      width--;
    } else if (*p_string == '+') {
      p_string++;
      width--;
    }
    if (width > 0 || !count) {
      char *numbers;
      if (*p_string == '0') {
        p_string++;
        width--;
        result_status = 1;
        if ((*p_string == 'x' || *p_string == 'X') && result_status &&
            (width > 0 || !count)) {
          p_string++;
          width--;
          value->specifier = 'x';
          numbers = S21_NUMBERS_HEX;
        } else {
          value->specifier = 'o';
          numbers = S21_NUMBERS_OCT;
        }
      } else {
        value->specifier = 'd';
        numbers = S21_NUMBERS;
      }
      while (s21_strchr(numbers, *p_string) && *p_string != '\0' &&
             (width > 0 || !count)) {
        s21_isnumber(&result, *p_string, status, value);
        p_string++;
        width--;
        result_status = 1;
      }
    }
  }
  if (result_status && !value->star) {
    *sscanf_result += 1;
  }

  *pp_format = p_format;
  *pp_string = p_string;

  return result;
}

/*=================================================*/

int s21_min(int a, int b) {
  int result = a;
  if (b < a) result = b;
  return result;
}

/*=================================================*/

void space_pointer(char **pp_string) {
  char *p_string = *pp_string;
  while (*p_string == ' ' || *p_string == '\t' || *p_string == '\n') {
    p_string++;
  }
  *pp_string = p_string;
}

/*=================================================*/

int null_string_test(char **pp_string) {
  char *p_string_buf = *pp_string;
  char *p_string = p_string_buf;
  int result = -1;
  while (*p_string != EOF && *p_string != '\0') {
    if (*p_string != ' ' && *p_string != '\n' && *p_string != '\t') {
      result = 0;
    }
    p_string++;
  }
  *pp_string = p_string_buf;
  return result;
}

/*=================================================*/

int result_test(int result_1, int result_2) {
  int result = 0;
  if (result_1 > result_2) result = 1;
  return result;
}

/*=================================================*/

void twins_check(char **pp_format, char **pp_string) {
  char *p_format = *pp_format;
  char *p_string = *pp_string;
  int space_status = 0;
  while (*p_format != '%') {
    if (*p_format == ' ') space_status = 1;
    if (*p_format == *p_string) {
      p_string++;
    }
    p_format++;
  }
  p_format--;
  if (space_status) {
    while (*p_string == ' ') {
      p_string++;
    }
  }
  *pp_format = p_format;
  *pp_string = p_string;
}

/*=================================================*/

void is_const(long double *result, char **pp_string) {
  char *p_string = *pp_string;
  if (s21_strchr("Ii", *p_string) && *p_string != '\0') {
    p_string++;
    if (s21_strchr("Nn", *p_string) && *p_string != '\0') {
      p_string++;
      if (s21_strchr("Ff", *p_string) && *p_string != '\0') {
        p_string++;
        *result = S21_INFINITY;
      } else
        p_string -= 2;
    } else
      p_string--;
  } else if (s21_strchr("Nn", *p_string) && *p_string != '\0') {
    p_string++;
    if (s21_strchr("Aa", *p_string) && *p_string != '\0') {
      p_string++;
      if (s21_strchr("Nn", *p_string) && *p_string != '\0') {
        p_string++;
        *result = S21_NAN;
        *result = -*result;
      } else
        p_string -= 2;
    } else
      p_string--;
  }

  *pp_string = p_string;
}
