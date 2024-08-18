#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_NONBLANK "-number-nonblank"
#define NUMBER "-number"
#define SQUEEZE_BLANK "-squeeze-blank"

typedef struct {
  int b;
  int e;
  int E;
  int v;
  int n;
  int s;
  int t;
  int T;
} storage_flags;

void func_open_file(char *arr, storage_flags *flags);
int func_find_flags(char *flag, storage_flags *base_struct_flags);
int func_long_flag(char *long_flag, storage_flags *long_struct_flag);
void func_error(char *flag);