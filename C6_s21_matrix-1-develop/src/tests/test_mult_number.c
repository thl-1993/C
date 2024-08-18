#include "test.h"

START_TEST(mult_number_1) {
  int res, s21_res;
  double number = 2;
  matrix_t A, result, s21_result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &result);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 4;
  result.matrix[0][0] = 2;
  result.matrix[0][1] = 4;
  result.matrix[0][2] = 6;
  result.matrix[1][0] = 0;
  result.matrix[1][1] = 8;
  result.matrix[1][2] = 4;
  result.matrix[2][0] = 4;
  result.matrix[2][1] = 6;
  result.matrix[2][2] = 8;
  result.rows = 3;
  result.columns = 3;

  res = OK;
  s21_res = s21_mult_number(&A, number, &s21_result);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(result.rows, s21_result.rows);
  ck_assert_int_eq(result.columns, s21_result.columns);
  ck_assert_double_eq(result.matrix[0][0], s21_result.matrix[0][0]);
  ck_assert_double_eq(result.matrix[0][1], s21_result.matrix[0][1]);
  ck_assert_double_eq(result.matrix[0][2], s21_result.matrix[0][2]);
  ck_assert_double_eq(result.matrix[1][0], s21_result.matrix[1][0]);
  ck_assert_double_eq(result.matrix[1][1], s21_result.matrix[1][1]);
  ck_assert_double_eq(result.matrix[1][2], s21_result.matrix[1][2]);
  ck_assert_double_eq(result.matrix[2][0], s21_result.matrix[2][0]);
  ck_assert_double_eq(result.matrix[2][1], s21_result.matrix[2][1]);
  ck_assert_double_eq(result.matrix[2][2], s21_result.matrix[2][2]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&s21_result);
}
END_TEST

START_TEST(mult_number_2) {
  int res, s21_res;
  double number = -2;
  matrix_t A, result, s21_result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &result);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 4;
  result.matrix[0][0] = -2;
  result.matrix[0][1] = -4;
  result.matrix[0][2] = -6;
  result.matrix[1][0] = -0;
  result.matrix[1][1] = -8;
  result.matrix[1][2] = -4;
  result.matrix[2][0] = -4;
  result.matrix[2][1] = -6;
  result.matrix[2][2] = -8;
  result.rows = 3;
  result.columns = 3;

  res = OK;
  s21_res = s21_mult_number(&A, number, &s21_result);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(result.rows, s21_result.rows);
  ck_assert_int_eq(result.columns, s21_result.columns);
  ck_assert_double_eq(result.matrix[0][0], s21_result.matrix[0][0]);
  ck_assert_double_eq(result.matrix[0][1], s21_result.matrix[0][1]);
  ck_assert_double_eq(result.matrix[0][2], s21_result.matrix[0][2]);
  ck_assert_double_eq(result.matrix[1][0], s21_result.matrix[1][0]);
  ck_assert_double_eq(result.matrix[1][1], s21_result.matrix[1][1]);
  ck_assert_double_eq(result.matrix[1][2], s21_result.matrix[1][2]);
  ck_assert_double_eq(result.matrix[2][0], s21_result.matrix[2][0]);
  ck_assert_double_eq(result.matrix[2][1], s21_result.matrix[2][1]);
  ck_assert_double_eq(result.matrix[2][2], s21_result.matrix[2][2]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&s21_result);
}
END_TEST

START_TEST(mult_number_3) {
  int res, s21_res;
  double number = 2;
  matrix_t A, s21_result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = S21_INFINITY;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 4;

  res = CALCULATION_ERROR;
  s21_res = s21_mult_number(&A, number, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_4) {
  int res, s21_res;
  double number = S21_INFINITY;
  matrix_t A, s21_result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 4;

  res = CALCULATION_ERROR;
  s21_res = s21_mult_number(&A, number, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_5) {
  int res, s21_res;
  double number = 2;
  matrix_t A = {.columns = 0, .rows = 10}, s21_result;

  res = INCORRECT_MATRIX;
  s21_res = s21_mult_number(&A, number, &s21_result);

  ck_assert_int_eq(res, s21_res);
}
END_TEST

START_TEST(mult_number_6) {
  int res, s21_res;
  double number = S21_NAN;
  matrix_t A, s21_result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 4;

  res = CALCULATION_ERROR;
  s21_res = s21_mult_number(&A, number, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_7) {
  int res, s21_res;
  double number = MAX_DOUBLE;
  matrix_t A, s21_result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 4;

  res = CALCULATION_ERROR;
  s21_res = s21_mult_number(&A, number, &s21_result);
  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_8) {
  int res, s21_res;
  double number = 5;
  matrix_t A, s21_result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = MIN_DOUBLE;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 4;

  res = CALCULATION_ERROR;
  s21_res = s21_mult_number(&A, number, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_9) {
  int res, s21_res;
  double number = 5;
  matrix_t A, s21_result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = S21_NAN;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 4;

  res = CALCULATION_ERROR;
  s21_res = s21_mult_number(&A, number, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_10) {
  int res, s21_res;
  double number = 2;
  matrix_t A, result, s21_result;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &result);

  A.matrix[0][0] = 1;
  result.matrix[0][0] = 2;
  result.rows = 1;
  result.columns = 1;

  res = OK;
  s21_res = s21_mult_number(&A, number, &s21_result);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(result.rows, s21_result.rows);
  ck_assert_int_eq(result.columns, s21_result.columns);
  ck_assert_double_eq(result.matrix[0][0], s21_result.matrix[0][0]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&s21_result);
}
END_TEST

Suite *suite_mult_number() {
  Suite *s = suite_create(YELLOW_BG BLACK "s21_mult_number" RESET);
  TCase *tc = tcase_create("mult_number_tc");
  tcase_add_test(tc, mult_number_1);
  tcase_add_test(tc, mult_number_2);
  tcase_add_test(tc, mult_number_3);
  tcase_add_test(tc, mult_number_4);
  tcase_add_test(tc, mult_number_5);
  tcase_add_test(tc, mult_number_6);
  tcase_add_test(tc, mult_number_7);
  tcase_add_test(tc, mult_number_8);
  tcase_add_test(tc, mult_number_9);
  tcase_add_test(tc, mult_number_10);
  suite_add_tcase(s, tc);
  return s;
}