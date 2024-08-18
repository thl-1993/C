#include "s21_grep.h"
int main(int argc, char* argv[]) {
  storage_flags flags_and_name = {.e = 0,
                                  .i = 0,
                                  .v = 0,
                                  .c = 0,
                                  .l = 0,
                                  .n = 0,
                                  .h = 0,
                                  .s = 0,
                                  .f = 0,
                                  .o = 0,
                                  .count_string_regular = 0,
                                  .count_name_files = 0,
                                  .string_regular = {'\0'},
                                  .name_files = {'\0'}};
  regex_t preg;
  regmatch_t pmatch;
  opterr = 0;
  func_pars(&flags_and_name, &preg, argc, argv);
  for (int i = 0; i < flags_and_name.count_name_files; i++) {
  }
  for (int i = 0; i < flags_and_name.count_name_files; i++) {
    func_check_files(flags_and_name.name_files[i], &preg, &pmatch,
                     &flags_and_name);
  }
  regfree(&preg);
  return 0;
}
void func_pars(storage_flags* flags_and_name, regex_t* preg, int argc,
               char** argv) /* zapisyvaet flagi i imena failov */
{
  int value = 0;
  while (value != -1) {
    value = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL);
    switch (value) {
      case 'e':
        flags_and_name->e = 1;
        if (flags_and_name->count_string_regular > 0) {
          strcat(flags_and_name->string_regular, "|");
        }
        strcat(flags_and_name->string_regular, optarg);
        flags_and_name->count_string_regular += 1;
        break;
      case 'i':
        flags_and_name->i = 1;
        break;
      case 'v':
        flags_and_name->v = 1;
        break;
      case 'c':
        flags_and_name->c = 1;
        break;
      case 'l':
        flags_and_name->l = 1;
        break;
      case 'n':
        flags_and_name->n = 1;
        break;
      case 'h':
        flags_and_name->h = 1;
        break;
      case 's':
        flags_and_name->s = 1;
        break;
      case 'f':
        flags_and_name->f = 1;
        func_flag_f(optarg, flags_and_name);
        break;
      case 'o':
        flags_and_name->o = 1;
        break;
      default:
        break;
    }
  }
  if (!flags_and_name->e && !flags_and_name->f && optind < argc) {
    strcat(flags_and_name->string_regular, argv[optind]);
    flags_and_name->count_string_regular += 1;
    for (int i = 0; i < argc - optind - 1; i++) {
      flags_and_name->name_files[i] = argv[i + optind + 1];
      flags_and_name->count_name_files += 1;
    }
  } else {
    for (int i = 0; i < argc - optind; i++) {
      flags_and_name->name_files[i] = argv[i + optind];
      flags_and_name->count_name_files += 1;
    }
  }
  int parameter = REG_EXTENDED;
  if (flags_and_name->i) {
    parameter = REG_EXTENDED | REG_ICASE;
  }
  regcomp(preg, flags_and_name->string_regular, parameter);
}
int func_open_file(char* file_name, storage_flags* flags_and_name) {
  FILE* file;
  int result = 1;
  file = fopen(file_name, "r");
  if (NULL == file) {
    if (!flags_and_name->s) {
      fprintf(stderr, "grep: %s: No such file or directory\n", file_name);
    }
    result = 0;
  } else
    fclose(file);
  return result;
}

void func_flag_f(char* file_name, storage_flags* string) {
  if (func_open_file(file_name, string)) {
    FILE* file;
    file = fopen(file_name, "r");
    char* buffer = NULL;
    size_t len_buffer = 0;
    while (getline(&buffer, &len_buffer, file) != -1) { /*-1 kogda konec faila*/
      if (string->count_string_regular > 0) {
        strcat(string->string_regular, "|");
      }
      int len = strlen(buffer);
      if (buffer[len - 1] == '\n') {
        if (len <= 2) {
          buffer[len - 1] = '.';
        } else {
          buffer[len - 1] = '\0';
        }
      }
      strcat(string->string_regular, buffer);
      string->count_string_regular += 1;
    }
    free(buffer);
    fclose(file);
  } else {
    exit(1);
  }
}

void func_check_files(char* file_name, regex_t* preg, regmatch_t* pmatch,
                      storage_flags* flags_and_name) {
  FILE* file;
  file = fopen(file_name, "r");
  if (func_open_file(file_name, flags_and_name)) {
    int thrue_counter = 0; /* schetchik istinnosti */
    char* buffer = NULL;
    size_t len_buffer = 0;
    int counter_string = 0;
    while (getline(&buffer, &len_buffer, file) != -1) { /*-1 kogda konec faila*/
      counter_string++;
      int len = strlen(buffer);
      if ((!regexec(preg, buffer, 1, pmatch, 0)) ^ (flags_and_name->v)) {
        thrue_counter += 1;
        if (!flags_and_name->c && !flags_and_name->l) {
          if (!flags_and_name->h && flags_and_name->count_name_files > 1) {
            printf("%s:", file_name);
          }
          if (flags_and_name->n) {
            printf("%d:", counter_string);
          }
          if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
          }
          if (!flags_and_name->o || flags_and_name->v) {
            printf("%s\n", buffer);
          } else {
            char* o_string = buffer;
            for (; !regexec(preg, o_string, 1, pmatch, 0);
                 o_string += pmatch->rm_eo) {
              printf("%.*s\n", (int)(pmatch->rm_eo - pmatch->rm_so),
                     o_string + pmatch->rm_so);
            }
          }
        }
      }
    }
    if (flags_and_name->c) {
      if (flags_and_name->count_name_files > 1 && !flags_and_name->h) {
        printf("%s:", file_name);
      }
      if (flags_and_name->l && thrue_counter) {
        printf("1\n");
      } else {
        printf("%d\n", thrue_counter);
      }
    }
    if (flags_and_name->l && thrue_counter > 0) {
      printf("%s\n", file_name);
    }
    free(buffer);
  }

  fclose(file);
}
