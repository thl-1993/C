#include "test.h"

START_TEST(calc_complements_1) {
  int res, s21_res;
  matrix_t A, result, s21_result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &result);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  result.matrix[0][0] = 0;
  result.matrix[0][1] = 10;
  result.matrix[0][2] = -20;
  result.matrix[1][0] = 4;
  result.matrix[1][1] = -14;
  result.matrix[1][2] = 8;
  result.matrix[2][0] = -8;
  result.matrix[2][1] = -2;
  result.matrix[2][2] = 4;

  res = OK;

  s21_res = s21_calc_complements(&A, &s21_result);

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

START_TEST(calc_complements_2) {
  int res, s21_res;
  matrix_t A, s21_result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = S21_NAN;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  res = CALCULATION_ERROR;

  s21_res = s21_calc_complements(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_3) {
  int res, s21_res;
  matrix_t A, result, s21_result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &result);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  result.matrix[0][0] = 4;
  result.matrix[0][1] = -3;
  result.matrix[1][0] = -2;
  result.matrix[1][1] = 1;

  res = OK;

  s21_res = s21_calc_complements(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(result.rows, s21_result.rows);
  ck_assert_int_eq(result.columns, s21_result.columns);
  ck_assert_double_eq(result.matrix[0][0], s21_result.matrix[0][0]);
  ck_assert_double_eq(result.matrix[0][1], s21_result.matrix[0][1]);
  ck_assert_double_eq(result.matrix[1][0], s21_result.matrix[1][0]);
  ck_assert_double_eq(result.matrix[1][1], s21_result.matrix[1][1]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&s21_result);
}
END_TEST

START_TEST(calc_complements_4) {
  int res, s21_res;
  matrix_t A = {.rows = 0}, s21_result;
  s21_create_matrix(0, 3, &A);

  res = INCORRECT_MATRIX;

  s21_res = s21_calc_complements(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);
}
END_TEST

START_TEST(calc_complements_5) {
  int res, s21_res;
  matrix_t A, s21_result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 1;

  res = OK;

  s21_res = s21_calc_complements(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);

  s21_remove_matrix(&A);
  s21_remove_matrix(&s21_result);
}
END_TEST

START_TEST(calc_complements_6) {
  int res, s21_res;
  matrix_t A, result, s21_result;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &result);

  A.matrix[0][0] = 2;
  result.matrix[0][0] = 2;

  res = OK;
  s21_res = s21_calc_complements(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(result.rows, s21_result.rows);
  ck_assert_int_eq(result.columns, s21_result.columns);
  ck_assert_double_eq(result.matrix[0][0], s21_result.matrix[0][0]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&s21_result);
}
END_TEST

START_TEST(calc_complements_7) {
  int res, s21_res;
  matrix_t A, s21_result;
  s21_create_matrix(1, 2, &A);
  A.matrix[0][0] = 1;

  res = CALCULATION_ERROR;

  s21_res = s21_calc_complements(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);

  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_calc_complements() {
  Suite *s = suite_create(YELLOW_BG BLACK "s21_calc_complements" RESET);
  TCase *tc = tcase_create("calc_complements_tc");
  tcase_add_test(tc, calc_complements_1);
  tcase_add_test(tc, calc_complements_2);
  tcase_add_test(tc, calc_complements_3);
  tcase_add_test(tc, calc_complements_4);
  tcase_add_test(tc, calc_complements_5);
  tcase_add_test(tc, calc_complements_6);
  tcase_add_test(tc, calc_complements_7);
  suite_add_tcase(s, tc);
  return s;
}