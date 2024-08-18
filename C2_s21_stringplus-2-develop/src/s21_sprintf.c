#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  TOK f = {0};
  va_list va;
  va_start(va, format);
  int printed_chars = 0, a = 0;
  while (*format) {
    if (*format != '%') {
      printed_chars++;
      if (a == 0) {
        *str++ = *format++;
      } else {
        format++;
      }
      continue;
    } else {
      format++;
      s21_memset(&f, 0, sizeof(TOK));
    }
    format = get_flags(format, &f);
    format = get_width(format, &f, va);
    format = get_dot(format, &f, va);
    format = get_length(format, &f);
    f.specifier = *format;
    format++;
    char buff[SIZE_CHAR] = {'\0'};
    if (f.specifier == 'd' || f.specifier == 'i')
      sprintf_int(f, buff, va);
    else if (f.specifier == 'u')
      sprintf_U(f, buff, va);
    else if (f.specifier == '%')
      buff[0] = '%';
    else if (f.specifier == 'c') {
      sprintf_char(f, buff, va);
      if (buff[0] == '\0') {
        *str = '\0';
        a++;
      }
    } else if (f.specifier == 's')
      sprintf_string(f, buff, va);
    else if (f.specifier == 'f')
      sprintf_double(f, buff, va);
    for (int i = 0; buff[i]; i++, str++, printed_chars++) {
      if (a == 0) *str = buff[i];
    }
  }
  *str = '\0';
  printed_chars = printed_chars + a;
  va_end(va);
  return printed_chars;
}

const char *get_flags(const char *format, TOK *f) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '0' ||
         *format == '#') {
    switch (*format) {
      case '0':
        f->zero = 1;
        break;
      case '-':
        f->minus = 1;
        break;
      case '+':
        f->plus = 1;
        break;
      case ' ':
        f->space = 1;
        break;
    }
    format++;
  }
  return format;
}

const char *get_width(const char *format, TOK *f, va_list va) {
  if (*format == '*') {
    format++;
    f->width = va_arg(va, int);
  } else if (isNumber(*format)) {
    char tmp[SIZE_CHAR] = {'\0'};
    for (int i = 0; isNumber(*format); i++, format++) tmp[i] = *format;
    f->width = s21_atoi(tmp);
  }
  return format;
}

const char *get_dot(const char *format, TOK *f, va_list va) {
  if (*format == '.') {
    f->dot_set = 1;
    format++;
  }

  if (*format == '*') {
    format++;
    f->dot = va_arg(va, int);
  }
  if (isNumber(*format)) {
    char tmp[SIZE_CHAR] = {'\0'};
    for (int i = 0; isNumber(*format); i++, format++) tmp[i] = *format;
    f->dot = s21_atoi(tmp);
  }
  return format;
}

const char *get_length(const char *format, TOK *f) {
  switch (*format) {
    case 'h':
      f->length = 'h';
      format++;
      break;
    case 'l':
      f->length = 'l';
      format++;
      break;
    case 'L':
      f->length = 'L';
      format++;
  }
  return format;
}

int isNumber(char c) { return (c >= '0' && c <= '9'); }

void sprintf_int(TOK f, char *buff, va_list va) {
  int64_t val = va_arg(va, int64_t);

  switch (f.length) {
    case 0:
      val = (int32_t)val;
      break;
    case 'h':
      val = (int16_t)val;
  }
  if (val == -9223372036854775807 - 1) {
    unsigned_num_to_string((uint64_t)val, buff);
    s21_strcpy(buff, "-9223372036854775808");
  } else {
    whole_num_to_string(val, buff);
  }
  format_dot(buff, f);
  format_flags(buff, f);
}

void whole_num_to_string(int64_t val, char *ret) {
  char tmp[SIZE_CHAR] = {'\0'};
  int idx = SIZE_CHAR - 2;

  int neg = val < 0 ? 1 : 0;
  val = neg ? -val : val;

  if (val == 0) tmp[idx] = '0';

  while (val > 0) {
    idx--;
    tmp[idx] = "0123456789"[val % 10];
    val /= 10;
  }
  for (int j = 0; tmp[idx]; idx++, j++) {
    if (neg && j == 0) {
      ret[j++] = '-';
    }

    ret[j] = tmp[idx];
  }
}

void format_dot(char *buff, TOK f) {
  char tmp[SIZE_CHAR] = {'\0'};

  int sign = 0;
  int len = s21_strlen(buff);

  if (buff[0] == '-') {
    tmp[0] = '-';
    len--;
    sign = 1;
  }

  if (f.dot > len) {
    int idx;
    for (idx = sign; idx < f.dot - len + sign; idx++) tmp[idx] = '0';

    for (int i = sign; buff[i]; i++, idx++) tmp[idx] = buff[i];

    s21_strcpy(buff, tmp);
  }

  if (f.dot_set && f.dot == 0 && check_integer_specifier(f.specifier) &&
      buff[0] == '0')
    buff[0] = '\0';
}

int check_integer_specifier(char c) {
  char specs[] = {'d', 'i', 'u'};
  int res = 0;
  for (s21_size_t i = 0; i < sizeof(specs); i++) {
    if (specs[i] == c) {
      res = 1;
      break;
    }
  }
  return res;
}

void format_flags(char *buff, TOK f) {
  int neg = buff[0] == '-' ? 1 : 0;
  char tmp[SIZE_CHAR + 1] = {'\0'};
  if (f.width > (int)s21_strlen(buff) && f.zero && (neg || f.plus || f.space) &&
      !f.minus) {
    int idx = f.width - s21_strlen(buff);
    if (neg) {
      buff[0] = '0';
      f.plus = f.space = 0;
      format_flags_zero(tmp, buff, idx, '-');
    } else if (f.plus) {
      format_flags_zero(tmp, buff, idx, '+');
      f.plus = f.space = 0;
    } else if (f.space) {
      format_flags_zero(tmp, buff, idx, ' ');
      f.space = 0;
    }
    s21_strcpy(buff, tmp);
  }
  if (f.plus && f.specifier != 'u') {
    tmp[0] = buff[0] == '-' ? buff[0] : '+';
    s21_strcpy(tmp + 1, buff[0] == '-' ? buff + 1 : buff);
    s21_strcpy(buff, tmp);
  } else if (f.space && buff[0] != '-' && f.specifier != 'u') {
    tmp[0] = ' ';
    s21_strcpy(tmp + 1, buff);
    s21_strcpy(buff, tmp);
  }
  if (f.width > (int)s21_strlen(buff)) {
    int idx = f.width - s21_strlen(buff);
    if (!f.minus) {
      s21_memset(tmp, f.zero ? '0' : ' ', idx);
      s21_strcpy(tmp + idx, buff);
    } else {
      s21_strcpy(tmp, buff);
      s21_memset(tmp + s21_strlen(tmp), ' ', idx);
    }
    s21_strcpy(buff, tmp);
  }
}

void format_flags_zero(char *tmp, char *buff, int idx, char sign) {
  s21_memset(tmp, '0', idx);
  s21_strcat(tmp, buff);
  tmp[0] = sign;
}

void sprintf_U(TOK f, char *buff, va_list va) {
  uint64_t val = va_arg(va, uint64_t);
  switch (f.length) {
    case 'h':
      val = (uint16_t)val;
      break;
    case 'l':
      val = (uint64_t)val;
      break;
    case 0:
      val = (uint32_t)val;
  }
  unsigned_num_to_string(val, buff);
  format_dot(buff, f);
  format_flags(buff, f);
}

void unsigned_num_to_string(uint64_t val, char *ret) {
  char buf[SIZE_CHAR + 1] = {'\0'};
  int idx = SIZE_CHAR - 1;
  if (val == 0) {
    buf[idx] = '0';
    idx--;
  }

  for (; val && idx; --idx, val /= 10) buf[idx] = "0123456789"[val % 10];
  for (int j = 0; buf[idx + 1]; idx++, j++) ret[j] = buf[idx + 1];
}

void sprintf_char(TOK f, char *buff, va_list va) {
  if (f.length == 'l') {
    wchar_t w_c;
    w_c = va_arg(va, wchar_t);
    format_wchar(f, buff, w_c);
  } else {
    char c;
    c = va_arg(va, int);
    format_char(f, buff, c);
  }
}

void format_wchar(TOK f, char *buff, wchar_t w_c) {
  char tmp[SIZE_CHAR] = {'\0'};
  wctomb(tmp, w_c);

  int len = s21_strlen(tmp);
  int shift = f.width - len;

  if (f.minus && shift > 0) {
    s21_strcpy(buff, tmp);
    s21_memset(buff + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buff, ' ', shift);
    s21_strcpy(buff + shift, tmp);
  } else {
    s21_strcpy(buff, tmp);
  }
}

void format_char(TOK f, char *buff, char c) {
  if (c == '\0') {
    buff[0] = '\0';
  } else {
    int shift = f.width - 1;

    if (f.minus && shift > 0) {
      buff[0] = c;
      s21_memset(buff + 1, ' ', shift);
    } else if (shift > 0) {
      s21_memset(buff, ' ', shift);
      buff[shift] = c;
    } else {
      buff[0] = c;
    }
  }
}

void sprintf_string(TOK f, char *buff, va_list va) {
  if (f.length == 'l') {
    wchar_t *wstr = va_arg(va, wchar_t *);
    format_wide_string(f, buff, wstr);
  } else {
    char *str = va_arg(va, char *);
    format_string(f, buff, str);
  }
}

void format_wide_string(TOK f, char *buff, wchar_t *wstr) {
  char tmp[SIZE_CHAR] = {'\0'};
  char str[SIZE_CHAR] = {'\0'};

  wcstombs(str, wstr, SIZE_CHAR);
  s21_strcpy(tmp, str);
  if (f.dot_set) tmp[f.dot] = '\0';

  int shift = f.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (f.minus && shift > 0) {
    s21_strcpy(buff, tmp);
    s21_memset(buff + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buff, ' ', shift);
    s21_strcpy(buff + shift, tmp);
  } else {
    s21_strcpy(buff, tmp);
  }
}

void format_string(TOK f, char *buff, char *str) {
  if (str == 0) {
    s21_strcpy(buff, "(null)");
  } else {
    char tmp[SIZE_CHAR] = {'\0'};
    s21_strcpy(tmp, str);
    if (f.dot_set) tmp[f.dot] = '\0';

    int shift = f.width - s21_strlen(tmp);
    int len = s21_strlen(tmp);

    if (f.minus && shift > 0) {
      s21_strcpy(buff, tmp);
      s21_memset(buff + len, ' ', shift);
    } else if (shift > 0) {
      s21_memset(buff, ' ', shift);
      s21_strcpy(buff + shift, tmp);
    } else {
      s21_strcpy(buff, tmp);
    }
  }
}

void sprintf_double(TOK f, char *buff, va_list va) {
  long double val = 0;
  if (f.length == 'L') {
    val = va_arg(va, long double);
  } else {
    val = va_arg(va, double);
  }

  if (!f.dot_set) {
    f.dot = 6;
  }

  double_to_string(val, buff, f);
  format_flags(buff, f);
}

void double_to_string(long double val, char *ret, TOK f) {
  char buff[SIZE_CHAR] = {'\0'};
  int idx = SIZE_CHAR - 2;
  int neg = val < 0 ? 1 : 0;
  val = neg ? val * -1 : val;
  long double l = 0, r = modfl(val, &l);
  if (f.dot == 0) {
    l = roundl(val);
    r = 0;
  }
  char f_rest[SIZE_CHAR] = {'\0'};
  for (int i = 0; i < f.dot; i++) {
    r = r * 10;
    f_rest[i] = (int)r + '0';
  }
  long long right = roundl(r), left = l;
  if (!right) {
    for (int i = 0; i < f.dot; idx--, i++) buff[idx] = '0';
  } else {
    for (int i = s21_strlen(f_rest); right || i > 0; right /= 10, idx--, i--)
      buff[idx] = (int)(right % 10 + 0.05) + '0';
  }
  if ((f.dot_set && f.dot != 0) || (int)r || (!f.dot_set && val == 0) ||
      s21_strlen(f_rest))
    buff[idx--] = '.';
  if (!left) {
    buff[idx] = '0';
    idx--;
  } else {
    for (; left; left /= 10, idx--) buff[idx] = (int)(left % 10) + '0';
  }
  for (int i = 0; buff[idx + 1]; idx++, i++) {
    if (neg && i == 0) {
      ret[i] = '-';
      i++;
    }
    ret[i] = buff[idx + 1];
  }
}
