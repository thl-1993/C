#include <stdio.h>

#include "test.h"
START_TEST(determinant_1) {
  int res, s21_res;
  double det, s21_det;
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 4;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 1;

  det = 0;

  res = OK;
  s21_res = s21_determinant(&A, &s21_det);

  ck_assert_int_eq(res, s21_res);
  ck_assert_double_eq(det, s21_det);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2) {
  int res, s21_res;
  double det, s21_det;
  matrix_t A;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 4;

  det = 4;

  res = OK;
  s21_res = s21_determinant(&A, &s21_det);
  // printf("\n\n\ns21_det %d\n\n\n", &s21_det);
  ck_assert_int_eq(res, s21_res);
  ck_assert_double_eq(det, s21_det);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3) {
  int res, s21_res;
  double det, s21_det;
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  det = 0;

  res = OK;
  s21_res = s21_determinant(&A, &s21_det);

  ck_assert_int_eq(res, s21_res);
  ck_assert_double_eq(det, s21_det);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_4) {
  int res, s21_res;
  double s21_det;
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = S21_INFINITY;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  res = CALCULATION_ERROR;
  s21_res = s21_determinant(&A, &s21_det);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_5) {
  int res, s21_res;
  double s21_det;
  matrix_t A;
  s21_create_matrix(3, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;

  res = CALCULATION_ERROR;
  s21_res = s21_determinant(&A, &s21_det);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_6) {
  int res, s21_res;
  double s21_det;
  matrix_t A = {.rows = 0, .columns = 2};
  s21_create_matrix(0, 2, &A);

  res = INCORRECT_MATRIX;
  s21_res = s21_determinant(&A, &s21_det);

  ck_assert_int_eq(res, s21_res);
}
END_TEST

START_TEST(determinant_7) {
  int res, s21_res;
  double s21_det;
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = MAX_DOUBLE;
  A.matrix[0][1] = S21_INFINITY;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = MAX_DOUBLE;

  res = CALCULATION_ERROR;
  s21_res = s21_determinant(&A, &s21_det);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_8) {
  int res, s21_res;
  double s21_det;
  matrix_t A;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = S21_NAN;

  res = CALCULATION_ERROR;
  s21_res = s21_determinant(&A, &s21_det);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_9) {
  int res, s21_res;
  double s21_det;
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = S21_NAN;

  res = CALCULATION_ERROR;
  s21_res = s21_determinant(&A, &s21_det);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_10) {
  int res, s21_res;
  double det, s21_det;
  matrix_t A;
  s21_create_matrix(5, 5, &A);

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 12;
  A.matrix[0][2] = -12;
  A.matrix[0][3] = 12;
  A.matrix[0][4] = 6;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = -9;
  A.matrix[1][2] = 9;
  A.matrix[1][3] = 9;
  A.matrix[1][4] = -6;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = -2;
  A.matrix[2][3] = 4;
  A.matrix[2][4] = -2;
  A.matrix[3][0] = -3;
  A.matrix[3][1] = -17;
  A.matrix[3][2] = 13;
  A.matrix[3][3] = 3;
  A.matrix[3][4] = -8;
  A.matrix[4][0] = 0;
  A.matrix[4][1] = 0;
  A.matrix[4][2] = 4;
  A.matrix[4][3] = -8;
  A.matrix[4][4] = 0;

  det = -1728;

  res = OK;
  s21_res = s21_determinant(&A, &s21_det);

  ck_assert_int_eq(res, s21_res);
  ck_assert_double_eq(det, s21_det);
  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_determinant() {
  Suite *s = suite_create(YELLOW_BG BLACK "s21_determinant" RESET);
  TCase *tc = tcase_create("determinant_tc");
  tcase_add_test(tc, determinant_1);
  tcase_add_test(tc, determinant_2);
  tcase_add_test(tc, determinant_3);
  tcase_add_test(tc, determinant_4);
  tcase_add_test(tc, determinant_5);
  tcase_add_test(tc, determinant_6);
  tcase_add_test(tc, determinant_7);
  tcase_add_test(tc, determinant_8);
  tcase_add_test(tc, determinant_9);
  tcase_add_test(tc, determinant_10);
  suite_add_tcase(s, tc);
  return s;
}