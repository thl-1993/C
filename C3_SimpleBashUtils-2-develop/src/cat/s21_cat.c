#include "s21_cat.h"

int main(int argc, char *argv[]) {
  char *file_name[100];
  int count_file_name = 0;
  storage_flags flags = {0};
  if (argc == 1) {
    printf("Command line has no additional arguments\n");
  }
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (func_find_flags(&argv[i][1], &flags)) {
        return 1;
      }
    } else {
      while (i < argc) {
        file_name[count_file_name] = argv[i];
        count_file_name++;
        break;
      }
    }
  }
  for (int i = 0; i < count_file_name; i++) {
    func_open_file(file_name[i], &flags);
  }
  return 0;
}

void func_open_file(char *arr, storage_flags *flags) {
  FILE *file;
  file = fopen(arr, "r");
  if (NULL == file) {
    fprintf(stderr, "%s file cannot be opened!\n", arr);
    return;
  }
  int ch = fgetc(file);
  char tmp = '\n';
  int count_not_empty_string = 0;
  int count_number_all_string = 0;
  int empty_string = 0;
  while (ch != EOF) {
    if (tmp == '\n') {
      if (flags->b == 1 && ch != '\n') {
        count_not_empty_string++;
        printf("%6d\t", count_not_empty_string);
      }
      if (flags->n == 1 && empty_string <= 1 && ch != EOF) {
        count_number_all_string++;
        printf("%6d\t", count_number_all_string);
      }
    }
    if (flags->e == 1 && ch == '\n' && empty_string == 0) {
      printf("$");
    }
    if (tmp == '\n') {
      if (flags->s == 1 && ch == '\n' && ch != EOF) {
        empty_string++;
      } else {
        empty_string = 0;
      }
    } else {
      empty_string = 0;
    }
    tmp = ch;
    if (flags->t == 1 && ch == '\t') {
      printf("^I");
    } else if ((ch < 32 || ch == 127) && flags->v && ch != '\t' && ch != '\n') {
      if (ch < 32) {
        printf("^%c", ch + 64);
      } else if (ch == 127) {
        printf("^%c", ch - 64);
      }
    } else {
      if (empty_string <= 1) {
        if (ch != EOF) {
          printf("%c", ch);
        }
      }
    }
    ch = fgetc(file);
  };
  fclose(file);
}

int func_find_flags(char *flag, storage_flags *base_struct_flags) {
  int err_flag = 0;
  switch (*flag) {
    case 'b':
      base_struct_flags->b = 1;
      break;
    case 'e':
      base_struct_flags->e = 1;
      base_struct_flags->v = 1;
      break;
    case 'E':
#ifndef __APPLE__
      base_struct_flags->E = 1;
      base_struct_flags->e = 1;
      break;
#else
      func_error(flag);
      err_flag = 1;
      break;
#endif
    case 'v':
      base_struct_flags->v = 1;
      break;
    case 'n':
      base_struct_flags->n = 1;
      break;
    case 's':
      base_struct_flags->s = 1;
      break;
    case 't':
      base_struct_flags->t = 1;
      base_struct_flags->v = 1;
      break;
    case 'T':
#ifndef __APPLE__
      base_struct_flags->T = 1;
      base_struct_flags->t = 1;
      break;
#else
      func_error(flag);
      err_flag = 1;
      break;
#endif
    case '-':
#ifndef __APPLE__
      func_long_flag(flag, base_struct_flags);
      break;
#else
      func_error(flag);
      err_flag = 1;
      break;
#endif
    default:
      func_error(flag);
      err_flag = 1;
      break;
  }
  if (base_struct_flags->b) base_struct_flags->n = 0;
  if (*(flag + 1) != 0) {
    if (func_find_flags(flag + 1, base_struct_flags) == 1) {
      err_flag = 1;
    }
  }

  return err_flag;
}

int func_long_flag(char *long_flag, storage_flags *long_struct_flag) {
  if (strcmp(long_flag, NUMBER_NONBLANK) == 0) {
    long_struct_flag->b = 1;
  } else if (strcmp(long_flag, NUMBER) == 0) {
    long_struct_flag->n = 1;
  } else if (strcmp(long_flag, SQUEEZE_BLANK) == 0) {
    long_struct_flag->s = 1;
  } else {
    printf("illegal option -- %s\n", long_flag);
    return 0;
  }
  return 1;
}

void func_error(char *flag) {
  printf("s21_cat: illegal option -- %c\n", *flag);
  printf("usage: s21_cat [-benstv] [file ...]\n");
}