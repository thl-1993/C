#include "s21_string.h"

// 1.Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str.
void *s21_memchr(const void *str, int c, s21_size_t n) {
  int flag = 1;
  char *ptr = (char *)str, *res = s21_NULL;
  for (size_t i = 0; i < n && flag == 1; i++) {
    int ch;
    ch = *(ptr + i);
    if (ch == c) {
      flag = 0;
      res = ptr + i;
    }
  }
  return res;
}

// 2.Сравнивает первые n байтов str1 и str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  unsigned char *ps1 = (unsigned char *)str1;
  unsigned char *ps2 = (unsigned char *)str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (*ps1 == *ps2) {
      ps1++;
      ps2++;
    } else {
      result = *ps1 - *ps2;
      n = 0;
    }
  }
  return result;
}

// 3.Копирует n символов из src в dest.
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *dest2 = (char *)dest;
  while (n--) {
    *(char *)dest = *(char *)src;
    dest = (char *)dest + 1;
    src = (char *)src + 1;
  }
  return dest2;
}

// 4.Копирует символ c (беззнаковый тип) в первые n символов строки, на которую
// указывает аргумент str.
void *s21_memset(void *str, int c, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    char sym = c;
    *((char *)str + i) = sym;
  }
  return str;
}

// 5.Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длиной до n символов.
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *destmem = dest;
  while (*dest != 0) dest++;
  while (*src != 0 && n > 0) {
    *dest = *src;
    dest++;
    src++;
    n--;
  }
  *dest = 0;
  return destmem;
}

// 6.Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке,
// на которую указывает аргумент str.
char *s21_strchr(const char *str, int c) {
  char *ptr = s21_NULL;
  while (*str != '\0') {
    if (*str == c) {
      ptr = (char *)str;
      break;
    }
    str++;
  }
  if (c == '\0') ptr = (char *)str;
  return ptr;
}

// 7.Сравнивает не более первых n байтов str1 и str2.
// 7.Сравнивает не более первых n байтов str1 и str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int ret = 0;
  for (; n && !ret; n--) {
    if (*str1++ != *str2++) ret = *(str1 - 1) - *(str2 - 1);
  }
  return ret;
}

// 8.Копирует до n символов из строки, на которую указывает src, в dest.
// 8.Копирует до n символов из строки, на которую указывает src, в dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *addr = dest;
  while (*src && n--) {
    *dest = *(char *)src;
    dest++;
    src++;
  }
  if (*src == '\0') {
    *dest = '\0';
  }
  return addr;
}

// 9.Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int len1 = s21_strlen(str1);
  int len2 = s21_strlen(str2);
  int i;
  for (i = 0; i < len1; i++)
    for (int j = 0; j < len2; j++)
      if (str1[i] == str2[j]) return i;
  return i;
}

// 10.Выполняет поиск во внутреннем массиве номера ошибки errnum и
// возвращает указатель на строку с сообщением об ошибке.
// Нужно объявить макросы, содержащие массивы сообщений об ошибке
// для операционных систем mac и linux.
// Описания ошибок есть в оригинальной библиотеке.
// Проверка текущей ОС осуществляется с помощью директив.
char *s21_strerror(int errnum) {
  static char res[50];
#if __linux__
#define MAX_NUM_ERR 134
  if (errnum >= 0 && errnum < MAX_NUM_ERR) {
    static const char *Error_1[] = {
        "Success",
        "Operation not permitted",
        "No such file or directory",
        "No such process",
        "Interrupted system call",
        "Input/output error",
        "No such device or address",
        "Argument list too long",
        "Exec format error",
        "Bad file descriptor",
        "No child processes",
        "Resource temporarily unavailable",
        "Cannot allocate memory",
        "Permission denied",
        "Bad address",
        "Block device required",
        "Device or resource busy",
        "File exists",
        "Invalid cross-device link",
        "No such device",
        "Not a directory",
        "Is a directory",
        "Invalid argument",
        "Too many open files in system",
        "Too many open files",
        "Inappropriate ioctl for device",
        "Text file busy",
        "File too large",
        "No space left on device",
        "Illegal seek",
        "Read-only file system",
        "Too many links",
        "Broken pipe",
        "Numerical argument out of domain",
        "Numerical result out of range",
        "Resource deadlock avoided",
        "File name too long",
        "No locks available",
        "Function not implemented",
        "Directory not empty",
        "Too many levels of symbolic links",
        "Unknown error 41",
        "No message of desired type",
        "Identifier removed",
        "Channel number out of range",
        "Level 2 not synchronized",
        "Level 3 halted",
        "Level 3 reset",
        "Link number out of range",
        "Protocol driver not attached",
        "No CSI structure available",
        "Level 2 halted",
        "Invalid exchange",
        "Invalid request descriptor",
        "Exchange full",
        "No anode",
        "Invalid request code",
        "Invalid slot",
        "Unknown error 58",
        "Bad font file format",
        "Device not a stream",
        "No data available",
        "Timer expired",
        "Out of streams resources",
        "Machine is not on the network",
        "Package not installed",
        "Object is remote",
        "Link has been severed",
        "Advertise error",
        "Srmount error",
        "Communication error on send",
        "Protocol error",
        "Multihop attempted",
        "RFS specific error",
        "Bad message",
        "Value too large for defined data type",
        "Name not unique on network",
        "File descriptor in bad state",
        "Remote address changed",
        "Can not access a needed shared library",
        "Accessing a corrupted shared library",
        ".lib section in a.out corrupted",
        "Attempting to link in too many shared libraries",
        "Cannot exec a shared library directly",
        "Invalid or incomplete multibyte or wide character",
        "Interrupted system call should be restarted",
        "Streams pipe error",
        "Too many users",
        "Socket operation on non-socket",
        "Destination address required",
        "Message too long",
        "Protocol wrong type for socket",
        "Protocol not available",
        "Protocol not supported",
        "Socket type not supported",
        "Operation not supported",
        "Protocol family not supported",
        "Address family not supported by protocol",
        "Address already in use",
        "Cannot assign requested address",
        "Network is down",
        "Network is unreachable",
        "Network dropped connection on reset",
        "Software caused connection abort",
        "Connection reset by peer",
        "No buffer space available",
        "Transport endpoint is already connected",
        "Transport endpoint is not connected",
        "Cannot send after transport endpoint shutdown",
        "Too many references: cannot splice",
        "Connection timed out",
        "Connection refused",
        "Host is down",
        "No route to host",
        "Operation already in progress",
        "Operation now in progress",
        "Stale file handle",
        "Structure needs cleaning",
        "Not a XENIX named type file",
        "No XENIX semaphores available",
        "Is a named type file",
        "Remote I/O error",
        "Disk quota exceeded",
        "No medium found",
        "Wrong medium type",
        "Operation canceled",
        "Required key not available",
        "Key has expired",
        "Key has been revoked",
        "Key was rejected by service",
        "Owner died",
        "State not recoverable",
        "Operation not possible due to RF-kill",
        "Memory page has hardware error"};
    s21_sprintf(res, "%s", Error_1[errnum]);
  } else if (errnum < 0 || errnum >= MAX_NUM_ERR) {
    s21_sprintf(res, "Unknown error %d", errnum);
  }

#else
#define MAX_NUM_ERR 107
  if (errnum >= 0 && errnum < MAX_NUM_ERR) {
    static const char *Error_2[] = {
        "Undefined error: 0",
        "Operation not permitted",
        "No such file or directory",
        "No such process",
        "Interrupted system call",
        "Input/output error",
        "Device not configured",
        "Argument list too long",
        "Exec format error",
        "Bad file descriptor",
        "No child processes",
        "Resource deadlock avoided",
        "Cannot allocate memory",
        "Permission denied",
        "Bad address",
        "Block device required",
        "Resource busy",
        "File exists",
        "Cross-device link",
        "Operation not supported by device",
        "Not a directory",
        "Is a directory",
        "Invalid argument",
        "Too many open files in system",
        "Too many open files",
        "Inappropriate ioctl for device",
        "Text file busy",
        "File too large",
        "No space left on device",
        "Illegal seek",
        "Read-only file system",
        "Too many links",
        "Broken pipe",
        "Numerical argument out of domain",
        "Result too large",
        "Resource temporarily unavailable",
        "Operation now in progress",
        "Operation already in progress",
        "Socket operation on non-socket",
        "Destination address required",
        "Message too long",
        "Protocol wrong type for socket",
        "Protocol not available",
        "Protocol not supported",
        "Socket type not supported",
        "Operation not supported",
        "Protocol family not supported",
        "Address family not supported by protocol family",
        "Address already in use",
        "Can't assign requested address",
        "Network is down",
        "Network is unreachable",
        "Network dropped connection on reset",
        "Software caused connection abort",
        "Connection reset by peer",
        "No buffer space available",
        "Socket is already connected",
        "Socket is not connected",
        "Can't send after socket shutdown",
        "Too many references: can't splice",
        "Operation timed out",
        "Connection refused",
        "Too many levels of symbolic links",
        "File name too long",
        "Host is down",
        "No route to host",
        "Directory not empty",
        "Too many processes",
        "Too many users",
        "Disc quota exceeded",
        "Stale NFS file handle",
        "Too many levels of remote in path",
        "RPC struct is bad",
        "RPC version wrong",
        "RPC prog. not avail",
        "Program version wrong",
        "Bad procedure for program",
        "No locks available",
        "Function not implemented",
        "Inappropriate file type or format",
        "Authentication error",
        "Need authenticator",
        "Device power is off",
        "Device error",
        "Value too large to be stored in data type",
        "Bad executable (or shared library)",
        "Bad CPU type in executable",
        "Shared library version mismatch",
        "Malformed Mach-o file",
        "Operation canceled",
        "Identifier removed",
        "No message of desired type",
        "Illegal byte sequence",
        "Attribute not found",
        "Bad message",
        "EMULTIHOP (Reserved)",
        "No message available on STREAM",
        "ENOLINK (Reserved)",
        "No STREAM resources",
        "Not a STREAM",
        "Protocol error",
        "STREAM ioctl timeout",
        "Operation not supported on socket",
        "Policy not found",
        "State not recoverable",
        "Previous owner died",
        "Interface output queue is full"};
    s21_sprintf(res, "%s", Error_2[errnum]);
  } else if (errnum < 0 || errnum >= MAX_NUM_ERR) {
    s21_sprintf(res, "Unknown error: %d", errnum);
  }
#endif
  return res;
}

// 11.Вычисляет длину строки str, не включая завершающий нулевой символ.
s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  while (*(str + length) != 0) {
    length++;
  }
  return length;
}

// 12. Находит первый символ в строке str1, который соответствует любому
// символу, указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  char *ret = s21_NULL;
  for (; *str1 != 0 && !ret; str1++) {
    for (char *p = (char *)str2; *p != 0; p++) {
      if (*str1 == *p) {
        ret = (char *)str1;
        break;
      }
    }
  }
  return ret;
}

// 13.Выполняет поиск последнего вхождения символа c (беззнаковый тип)
// 13.Выполняет поиск последнего вхождения символа c (беззнаковый тип)
// в строке, на которую указывает аргумент str.
char *s21_strrchr(const char *str, int c) {
  char *p_char = s21_NULL;
  for (; *str != '\0'; ++str) {
    if (*str == (char)c) {
      p_char = (char *)str;
    }
  }
  if (p_char == s21_NULL) {
    p_char = (char *)str;
  }
  return *p_char == c ? (char *)p_char : s21_NULL;
}

// 14.Находит первое вхождение всей строки needle (не включая завершающий
// нулевой символ), которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  char *s = s21_NULL;
  s21_size_t n = s21_strlen(needle);
  int diff = s21_strlen(haystack) - n;
  if (diff >= 0)
    for (int i = 0; i <= diff; i++, haystack++)
      if ((!s21_memcmp(haystack, needle, n))) {
        s = (char *)haystack;
        break;
      }

  return s;
}

// 15.Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim) {
  static char *olds = s21_NULL;
  char *token = s21_NULL, *ps;
  if (str == s21_NULL) str = olds;
  int tok = 1;

  // Фикс ошибки в тестах 17 - 20.
  // Цикл, который перебирает начало строки на предмет символов разделителей.
  // Если первый/ые символы строки являются разделительными - изменяет указатель
  // str на следующий символ не являющийся разделительным.

  if (str != s21_NULL && ifContains(*str, delim)) {
    for (ps = str++; ps != s21_NULL && *ps != 0; ps++) {
      if (!ifContains(*ps, delim)) {
        str = ps;
        break;
      }
    }
  }

  for (ps = str; ps != s21_NULL && *ps != 0 && tok; ps++) {
    if (ifContains(*ps, delim)) {
      *ps = 0;
      // if (!ifContains(*(ps + 1), delim)) tok = 0; Фикс от ошибки в 16 тесте.
      tok = 0;  // Фикс от ошибки в 16 тесте.
    }
  }
  if (!tok) {
    olds = ps;
    if (*str == 0) str = s21_strtok(s21_NULL, delim);
    token = str;
  }
  if (tok) {
    olds = s21_NULL;
    if (str && *str == 0) str = s21_NULL;
    token = str;
  }
  return token;
}

// Вспомогающая функция для s21_strtok()
int ifContains(char ch, const char *delim) {
  int ret = 0;
  for (char *pd = (char *)delim; *pd != 0 && !ret; pd++) {
    if (*pd == ch) ret++;
  }
  return ret;
}

// преводит строку в int
int s21_atoi(char *s) {
  int n = 0;
  while (*s >= '0' && *s <= '9') {
    n *= 10;
    n += *s++;
    n -= '0';
  }
  return n;
}

// 16
// Возвращает копию строки (str), преобразованной в
// верхний регистр. В случае какой-либо ошибки следует
// вернуть значение NULL
void *s21_to_upper(const char *str) {
  char *buf = s21_NULL;
  if (str) {
    buf = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (buf) {
      s21_strcpy(buf, str);
      for (char *tmp_str = buf; *tmp_str; tmp_str++) {
        if (*tmp_str >= 'a' && *tmp_str <= 'z') {
          *tmp_str -= 32;
        }
      }
    }
  }
  return (void *)buf;
}

// 17
// 17
// Возвращает копию строки (str), преобразованной в
// нижний регистр. В случае какой-либо ошибки следует
// вернуть значение NULL
void *s21_to_lower(const char *str) {
  char *buf = s21_NULL;
  if (str) {
    buf = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (buf) {
      s21_strcpy(buf, str);
      for (char *tmp_str = buf; *tmp_str; tmp_str++) {
        if (*tmp_str >= 'A' && *tmp_str <= 'Z') {
          *tmp_str += 32;
        }
      }
    }
  }
  return (void *)buf;
}

// 18
// 18
// Возвращает новую строку, в которой указанная строка
// (str) вставлена в указанную позицию (start_index) в
// данной строке (src). В случае какой-либо ошибки
// следует вернуть значение NULL
void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *buf = s21_NULL;
  if (src && str && s21_strlen(src) >= start_index) {
    buf =
        (char *)malloc((s21_strlen(src) + s21_strlen(str) + 1) * sizeof(char));
    if (buf) {
      s21_strncpy(buf, src, start_index);
      *(buf + start_index) = '\0';
      s21_strcat(buf, str);
      s21_strcat(buf, src + start_index);
    }
  }
  return (void *)buf;
}

// 19
// 19
// Возвращает новую строку, в которой удаляются все
// начальные и конечные вхождения набора заданных
// символов (trim_chars) из данной строки (src). В случае
// какой-либо ошибки следует вернуть значение NULL
void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;

  if (src) {
    if (trim_chars && *trim_chars) {
      s21_size_t len = s21_strlen(src);
      s21_size_t chars_len = s21_strlen(trim_chars);

      s21_trim_left(&src, trim_chars, &len, chars_len);
      if (len) s21_trim_right(&src, trim_chars, &len, chars_len);

      res = (char *)malloc(sizeof(char) * (len + 1));

      if (res) {
        for (s21_size_t i = 0; i < len + 1; i++) {
          if (i < len) {
            res[i] = src[i];
          } else {
            res[i] = '\0';
          }
        }
      }
    } else {
      res = (char *)malloc(sizeof(char) * (s21_strlen(src) + 1));
      if (res) {
        s21_strcpy(res, src);
      }
    }
  }

  return res;
}

void s21_trim_left(const char **src, const char *trim_chars,
                   s21_size_t *src_len, const s21_size_t trim_chars_len) {
  s21_size_t m = 0;

  while (src && m != trim_chars_len) {
    if ((**src) == trim_chars[m]) {
      (*src)++;
      (*src_len) -= 1;
      m = 0;
      continue;
    }
    m++;
  }
}

void s21_trim_right(const char **src, const char *trim_chars,
                    s21_size_t *src_len, const s21_size_t trim_chars_len) {
  s21_size_t m = 0;
  s21_size_t i = (*src_len) - 1;

  while (src && m != trim_chars_len) {
    if ((*src)[i] == trim_chars[m]) {
      i--;
      (*src_len)--;
      m = 0;
      continue;
    }

    m++;
  }
}

// 20.Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest.
char *s21_strcat(char *dest, const char *src) {
  char *destmem = dest;
  while (*dest != 0) dest++;
  while (*src != 0) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = *src;
  return destmem;
}

// 21.Копирует строку, на которую указывает src, в dest.
char *s21_strcpy(char *dest, const char *src) {
  int i = 0;
  for (; src[i] != 0; i++) {
    dest[i] = src[i];
  }
  dest[i] = 0;
  return dest;
}
