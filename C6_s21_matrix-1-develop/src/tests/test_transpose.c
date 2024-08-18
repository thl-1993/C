#include "test.h"

START_TEST(transpose_1) {
  int res, s21_res;
  matrix_t A, result, s21_result;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &result);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  result.matrix[0][0] = 1;
  result.matrix[0][1] = 2;
  result.matrix[0][2] = 3;
  result.matrix[1][0] = 4;
  result.matrix[1][1] = 5;
  result.matrix[1][2] = 6;

  res = OK;
  s21_res = s21_transpose(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(result.rows, s21_result.rows);
  ck_assert_int_eq(result.columns, s21_result.columns);
  ck_assert_double_eq(result.matrix[0][0], s21_result.matrix[0][0]);
  ck_assert_double_eq(result.matrix[0][1], s21_result.matrix[0][1]);
  ck_assert_double_eq(result.matrix[0][2], s21_result.matrix[0][2]);
  ck_assert_double_eq(result.matrix[1][0], s21_result.matrix[1][0]);
  ck_assert_double_eq(result.matrix[1][1], s21_result.matrix[1][1]);
  ck_assert_double_eq(result.matrix[1][2], s21_result.matrix[1][2]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&s21_result);
}
END_TEST

START_TEST(transpose_2) {
  int res, s21_res;
  matrix_t A, s21_result;
  s21_create_matrix(3, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = S21_NAN;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;

  res = CALCULATION_ERROR;
  s21_res = s21_transpose(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(transpose_3) {
  int res, s21_res;
  matrix_t A, s21_result;
  s21_create_matrix(3, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = S21_INFINITY;

  res = CALCULATION_ERROR;
  s21_res = s21_transpose(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(transpose_4) {
  int res, s21_res;
  matrix_t A, s21_result;
  s21_create_matrix(3, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = S21_INFINITY_NEGATIVE;

  res = CALCULATION_ERROR;
  s21_res = s21_transpose(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(transpose_5) {
  int res, s21_res;
  matrix_t A = {.rows = 0, .columns = 3}, s21_result;

  res = INCORRECT_MATRIX;
  s21_res = s21_transpose(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);
}
END_TEST

START_TEST(transpose_6) {
  int res, s21_res;
  matrix_t A, result, s21_result;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &result);

  A.matrix[0][0] = 3;
  result.matrix[0][0] = 3;

  res = OK;
  s21_res = s21_transpose(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(result.rows, s21_result.rows);
  ck_assert_int_eq(result.columns, s21_result.columns);
  ck_assert_double_eq(result.matrix[0][0], s21_result.matrix[0][0]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&s21_result);
}
END_TEST

Suite *suite_transpose() {
  Suite *s = suite_create(YELLOW_BG BLACK "s21_transpose" RESET);
  TCase *tc = tcase_create("transpose_tc");
  tcase_add_test(tc, transpose_1);
  tcase_add_test(tc, transpose_2);
  tcase_add_test(tc, transpose_3);
  tcase_add_test(tc, transpose_4);
  tcase_add_test(tc, transpose_5);
  tcase_add_test(tc, transpose_6);
  suite_add_tcase(s, tc);
  return s;
}