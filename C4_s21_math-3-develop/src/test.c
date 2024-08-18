#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_math.h"

typedef struct {
  int abs;
  int acos;
  int asin;
  int atan;
  int ceil;
  int cos;
  int exp;
  int fabs;
  int floor;
  int fmod;
  int log;
  int pow;
  int sin;
  int sqrt;
  int tan;
  int all;
  int value;
  int help;
} flags;

int main(int argc, char* argv[]) {
  flags flag = {0};
  const struct option long_options[] = {{"abs", no_argument, &flag.abs, 1},
                                        {"acos", no_argument, &flag.acos, 1},
                                        {"asin", no_argument, &flag.asin, 1},
                                        {"atan", no_argument, &flag.atan, 1},
                                        {"ceil", no_argument, &flag.ceil, 1},
                                        {"cos", no_argument, &flag.cos, 1},
                                        {"exp", no_argument, &flag.exp, 1},
                                        {"fabs", no_argument, &flag.fabs, 1},
                                        {"floor", no_argument, &flag.floor, 1},
                                        {"fmod", no_argument, &flag.fmod, 1},
                                        {"log", no_argument, &flag.log, 1},
                                        {"pow", no_argument, &flag.pow, 1},
                                        {"sin", no_argument, &flag.sin, 1},
                                        {"sqrt", no_argument, &flag.sqrt, 1},
                                        {"tan", no_argument, &flag.tan, 1},
                                        {"all", no_argument, &flag.all, 1},
                                        {"value", no_argument, &flag.value, 1},
                                        {"help", no_argument, &flag.help, 1},
                                        {NULL, 0, NULL, 0}};

  while (getopt_long_only(argc, argv, "", long_options, NULL) != -1)
    ;
  if (flag.all) {
    flag.abs = 1;
    flag.acos = 1;
    flag.asin = 1;
    flag.atan = 1;
    flag.ceil = 1;
    flag.cos = 1;
    flag.exp = 1;
    flag.fabs = 1;
    flag.floor = 1;
    flag.fmod = 1;
    flag.log = 1;
    flag.pow = 1;
    flag.sin = 1;
    flag.sqrt = 1;
    flag.tan = 1;
  }

  if (flag.help) {
    flag.abs = 0;
    flag.acos = 0;
    flag.asin = 0;
    flag.atan = 0;
    flag.ceil = 0;
    flag.cos = 0;
    flag.exp = 0;
    flag.fabs = 0;
    flag.floor = 0;
    flag.fmod = 0;
    flag.log = 0;
    flag.pow = 0;
    flag.sin = 0;
    flag.sqrt = 0;
    flag.tan = 0;
    flag.value = 0;
    printf(
        "1 -abs сравнивает функцию abs math.h c s21_abs\n"
        "2 -acos сравнивает функцию acos math.h c s21_acos\n"
        "3 -asin сравнивает функцию asin math.h c s21_asin\n"
        "4 -atan сравнивает функцию atan math.h c s21_atan\n"
        "5 -ceil сравнивает функцию ceil math.h c s21_ceil\n"
        "6 -cos сравнивает функцию cos math.h c s21_cos\n"
        "7 -exp сравнивает функцию exp math.h c s21_exp\n"
        "8 -fabs сравнивает функцию fabs math.h c s21_fabs\n"
        "9 -floor сравнивает функцию floor math.h c s21_floor\n"
        "10 -fmod сравнивает функцию fmod math.h c s21_fmod\n"
        "11 -log сравнивает функцию log math.h c s21_log\n"
        "12 -pow сравнивает функцию pow math.h c s21_pow\n"
        "13 -sin сравнивает функцию sin math.h c s21_sin\n"
        "14 -sqrt сравнивает функцию sqrt math.h c s21_sqrt\n"
        "15 -tan сравнивает функцию tan math.h c s21_tan\n"
        "16 -value позволяет ввести свои тестовые значениея\n");
  }

  double arr[] = {
      S21_INFINITY, -S21_INFINITY, S21_NAN, -0.0L, 0.0L, 3,     2,  5.55, -13,
      2.5,          5.7,           -2.22,   -3.33, 4.44, -5.55, -1, 1};
  int arr_len = sizeof(arr) / sizeof(arr[0]);
  int arr_for_abs[arr_len];
  for (int i = 0; i < arr_len; i++) {
    arr_for_abs[i] = (int)arr[i];
  }
  int arr_len_abs = sizeof(arr_for_abs) / sizeof(arr_for_abs[0]);
  if (flag.value) {
    char symbol = ' ';
    double number = 0;
    int arr_count = 0;
    while (symbol != '\n') {
      scanf("%lf%c", &number, &symbol);
      arr_for_abs[arr_count] = (int)number;
      arr[arr_count] = number;
      arr_count++;
      if (arr_count == arr_len) break;
    }
    arr_len = arr_count;
    arr_len_abs = arr_count;
  }
  /* test abs */
  if (flag.abs) {
    for (int i = 0; i < arr_len_abs; i++) {
      printf("\n");
      printf("abs(%d)     = %d\n", arr_for_abs[i], abs(arr_for_abs[i]));
      printf("s21_abs(%d) = %d\n", arr_for_abs[i], s21_abs(arr_for_abs[i]));
    }
  }

  /* test acos */
  if (flag.acos) {
    for (int i = 0; i < arr_len; i++) {
      printf("\n");
      printf("acos(%lf)     = %lf\n", arr[i], acos(arr[i]));
      printf("s21_acos(%lf) = %Lf\n", arr[i], s21_acos(arr[i]));
    }
  }

  /* test asin */
  if (flag.asin) {
    for (int i = 0; i < arr_len; i++) {
      printf("\n");
      printf("asin(%lf)     = %lf\n", arr[i], asin(arr[i]));
      printf("s21_asin(%lf) = %Lf\n", arr[i], s21_asin(arr[i]));
    }
  }

  /* test atan */
  if (flag.atan) {
    for (int i = 0; i < arr_len; i++) {
      printf("\n");
      printf("atan(%lf)     = %lf\n", arr[i], atan(arr[i]));
      printf("s21_atan(%lf) = %Lf\n", arr[i], s21_atan(arr[i]));
    }
  }

  /* test ceil */
  if (flag.ceil) {
    for (int i = 0; i < arr_len; i++) {
      printf("\n");
      printf("ceil(%lf)     = %lf\n", arr[i], ceil(arr[i]));
      printf("s21_ceil(%lf) = %Lf\n", arr[i], s21_ceil(arr[i]));
    }
  }

  /* test cos */
  if (flag.cos) {
    for (int i = 0; i < arr_len; i++) {
      printf("\n");
      printf("cos(%lf)     = %lf\n", arr[i], cos(arr[i]));
      printf("s21_cos(%lf) = %Lf\n", arr[i], s21_cos(arr[i]));
    }
  }

  /* test exp */
  if (flag.exp) {
    for (int i = 0; i < arr_len; i++) {
      printf("\n");
      printf("exp(%lf)     = %lf\n", arr[i], exp(arr[i]));
      printf("s21_exp(%lf) = %Lf\n", arr[i], s21_exp(arr[i]));
    }
  }

  /* test fabs */
  if (flag.fabs) {
    for (int i = 0; i < arr_len; i++) {
      printf("\n");
      printf("fabs(%lf)     = %lf\n", arr[i], fabs(arr[i]));
      printf("s21_fabs(%lf) = %Lf\n", arr[i], s21_fabs(arr[i]));
    }
  }

  /* test floor */
  if (flag.floor) {
    for (int i = 0; i < arr_len; i++) {
      printf("\n");
      printf("floor(%lf)     = %lf\n", arr[i], floor(arr[i]));
      printf("s21_floor(%lf) = %Lf\n", arr[i], s21_floor(arr[i]));
    }
  }

  /* test fmod */
  if (flag.fmod) {
    for (int i = 0; i < arr_len; i++) {
      for (int j = 0; j < arr_len; j++) {
        printf("\n");
        printf("fmod(%lf, %lf)     = %lf\n", arr[i], arr[j],
               fmod(arr[i], arr[j]));
        printf("s21_fmod(%lf, %lf) = %Lf\n", arr[i], arr[j],
               s21_fmod(arr[i], arr[j]));
      }
    }
  }

  /* test log */
  if (flag.log) {
    for (int i = 0; i < arr_len; i++) {
      printf("\n");
      printf("log(%lf)     = %lf\n", arr[i], log(arr[i]));
      printf("s21_log(%lf) = %Lf\n", arr[i], s21_log(arr[i]));
    }
  }

  /* test pow */
  if (flag.pow) {
    for (int i = 0; i < arr_len; i++) {
      for (int j = 0; j < arr_len; j++) {
        printf("\n");
        printf("pow(%lf, %lf)     = %lf\n", arr[i], arr[j],
               pow(arr[i], arr[j]));
        printf("s21_pow(%lf, %lf) = %Lf\n", arr[i], arr[j],
               s21_pow(arr[i], arr[j]));
      }
    }
  }

  /* test sin */
  if (flag.sin) {
    for (int i = 0; i < arr_len; i++) {
      printf("\n");
      printf("sin(%lf)     = %lf\n", arr[i], sin(arr[i]));
      printf("s21_sin(%lf) = %Lf\n", arr[i], s21_sin(arr[i]));
    }
  }

  /* test sqrt */
  if (flag.sqrt) {
    for (int i = 0; i < arr_len; i++) {
      printf("\n");
      printf("sqrt(%lf)     = %lf\n", arr[i], sqrt(arr[i]));
      printf("s21_sqrt(%lf) = %Lf\n", arr[i], s21_sqrt(arr[i]));
    }
  }

  /* test tan */
  if (flag.tan) {
    for (int i = 0; i < arr_len; i++) {
      printf("\n");
      printf("tan(%lf)     = %lf\n", arr[i], tan(arr[i]));
      printf("s21_tan(%lf) = %Lf\n", arr[i], s21_tan(arr[i]));
    }
  }

  return 0;
}