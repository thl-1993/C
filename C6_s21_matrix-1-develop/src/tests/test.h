#ifndef SRC_TESTS_TESTS_H_
#define SRC_TESTS_TESTS_H_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_matrix.h"

#define RESET "\x1b[0m"
#define YELLOW_BG "\x1b[103m"
#define BLACK "\x1b[30m"
#define WHITE "\x1b[97m"

#define RED_BG "\x1b[41m"
#define GREEN_BG "\x1b[42m"
#define WHITE_BG "\x1b[47m"
#define GRAY_BG "\x1b[100m"

Suite *suite_create_matrix();
Suite *suite_remove_matrix();
Suite *suite_eq_matrix();
Suite *suite_sum_matrix();
Suite *suite_sub_matrix();
Suite *suite_mult_number();
Suite *suite_mult_matrix();
Suite *suite_transpose();
Suite *suite_calc_complements();
Suite *suite_determinant();
Suite *suite_inverse_matrix();

void run();

#endif  // SRC_TESTS_TESTS_H_