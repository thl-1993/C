#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_
#define s21_NULL (void *)0
#define S21_NULL (void *)0  // Добавлен из-за тестов.

#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_CHAR 512
#define BUFF_SIZE 512

// ******   STRING   ******

typedef struct {
  int minus;
  int plus;
  int space;
  int zero;
  int hash;
  int dot;
  int dot_set;
  int width;
  char length;
  char specifier;
} TOK;

typedef long unsigned int s21_size_t;
typedef long unsigned s21_size_t;

int s21_sscanf(char *str, char *format, ...);
int s21_sprintf(char *str, const char *format, ...);
const char *get_flags(const char *format, TOK *f);              // -+0 #
const char *get_width(const char *format, TOK *f, va_list va);  // числа
const char *get_dot(const char *format, TOK *f,
                    va_list va);  // точность с точки
const char *get_length(const char *format, TOK *f);  // hlL
int isNumber(char c);  // возвращает если символ число
void sprintf_int(TOK f, char *buff, va_list va);  // разбор интового числа
void whole_num_to_string(int64_t val, char *ret);  // перевод числа в строку
void format_dot(char *buff, TOK f);  // вставляет нули по точности в строку
int check_integer_specifier(
    char c);  // проверяет совпадает символ со спецификатором
void format_flags(char *buff, TOK f);  // вставляет нули пробелы плюс
void format_flags_zero(char *tmp, char *buff, int idx,
                       char sign);  // исправление ошибки знак после нулей
void sprintf_U(TOK f, char *buff, va_list va);  // разбор инсайта
void unsigned_num_to_string(uint64_t val,
                            char *ret);  // перевод инсайта в строку
void sprintf_char(TOK f, char *buff, va_list va);  // разбор символа
void format_wchar(TOK f, char *buff, wchar_t w_c);  // символ с флагом l
void format_char(TOK f, char *buff, char c);  // символ без флага l
void sprintf_string(TOK f, char *buff, va_list va);  // разбор строки
void format_wide_string(TOK f, char *buff,
                        wchar_t *wstr);  // печать стрки с флагом
void format_string(TOK f, char *buff, char *str);  // печать строки без флага
void sprintf_double(TOK f, char *buff, va_list va);  // разбор дабле
void double_to_string(long double val, char *ret,
                      TOK f);  // перевод дабла в строку

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
int ifContains(char ch,
               const char *delim);  // дополнительная функция для s21_strtok
void s21_trim_left(const char **src, const char *trim_chars,
                   s21_size_t *src_len, const s21_size_t trim_chars_len);
void s21_trim_right(const char **src, const char *trim_chars,
                    s21_size_t *src_len, const s21_size_t trim_chars_len);

int s21_atoi(char *s);
int s21_num_length(unsigned long long num);

#endif  // SRC_S21_STRING_H_
