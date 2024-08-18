#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int count_string_regular;
  int count_name_files;
  char string_regular[4096];
  char* name_files[4096];
} storage_flags;

void func_pars(storage_flags* flags_and_name, regex_t* preg, int argc,
               char** argv);
int func_open_file(char* file_name, storage_flags* flags_and_name);
void func_flag_f(char* file_name, storage_flags* string);
void func_check_files(char* file_name, regex_t* preg, regmatch_t* pmatch,
                      storage_flags* flags_and_name);