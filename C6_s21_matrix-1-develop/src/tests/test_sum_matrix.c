#include "test.h"
START_TEST(sum_matrix_1) {
  int res, s21_res;
  matrix_t A, B, result, s21_result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &result);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 4;
  B.matrix[1][1] = 5;
  result.matrix[0][0] = 2;
  result.matrix[0][1] = 4;
  result.matrix[1][0] = 8;
  result.matrix[1][1] = 10;
  result.rows = 2;
  result.columns = 2;

  res = OK;
  s21_res = s21_sum_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(result.rows, s21_result.rows);
  ck_assert_int_eq(result.columns, s21_result.columns);
  ck_assert_double_eq(result.matrix[0][0], s21_result.matrix[0][0]);
  ck_assert_double_eq(result.matrix[0][1], s21_result.matrix[0][1]);
  ck_assert_double_eq(result.matrix[1][0], s21_result.matrix[1][0]);
  ck_assert_double_eq(result.matrix[1][1], s21_result.matrix[1][1]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&s21_result);
}
END_TEST

START_TEST(sum_matrix_2) {
  int res, s21_res;
  matrix_t A, B = {.matrix = 0, .rows = 0, .columns = 0}, s21_result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;

  res = INCORRECT_MATRIX;
  s21_res = s21_sum_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(sum_matrix_3) {
  int res, s21_res;
  matrix_t A, B, s21_result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 4;
  B.matrix[1][1] = 5;

  res = CALCULATION_ERROR;
  s21_res = s21_sum_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_4) {
  int res, s21_res;
  matrix_t A, B, s21_result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = S21_INFINITY;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 4;
  B.matrix[1][1] = 5;

  res = CALCULATION_ERROR;
  s21_res = s21_sum_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_5) {
  int res, s21_res;
  matrix_t A, B, s21_result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = S21_INFINITY_NEGATIVE;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 4;
  B.matrix[1][1] = 5;

  res = CALCULATION_ERROR;
  s21_res = s21_sum_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_6) {
  int res, s21_res;
  matrix_t A, B, s21_result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 0.0 / 0.0L;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 4;
  B.matrix[1][1] = 5;

  res = CALCULATION_ERROR;
  s21_res = s21_sum_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_7) {
  int res, s21_res;
  matrix_t A, B, s21_result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 1.4e+308;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 4;
  B.matrix[1][1] = 1.4e+308;

  res = CALCULATION_ERROR;

  s21_res = s21_sum_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_8) {
  int res, s21_res;
  matrix_t A, B, s21_result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 1.7976931348623158e+308;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 4;
  B.matrix[1][1] = 0;

  res = OK;
  s21_res = s21_sum_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&s21_result);
}
END_TEST

START_TEST(sum_matrix_9) {
  int res, s21_res;
  matrix_t A, B, s21_result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = -1.7976931348623158e+308;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 4;
  B.matrix[1][1] = 0;

  res = OK;
  s21_res = s21_sum_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&s21_result);
}
END_TEST

Suite *suite_sum_matrix() {
  Suite *s = suite_create(YELLOW_BG BLACK "s21_sum_matrix" RESET);
  TCase *tc = tcase_create("sum_matrix_tc");
  tcase_add_test(tc, sum_matrix_1);
  tcase_add_test(tc, sum_matrix_2);
  tcase_add_test(tc, sum_matrix_3);
  tcase_add_test(tc, sum_matrix_4);
  tcase_add_test(tc, sum_matrix_5);
  tcase_add_test(tc, sum_matrix_6);
  tcase_add_test(tc, sum_matrix_7);
  tcase_add_test(tc, sum_matrix_8);
  tcase_add_test(tc, sum_matrix_9);
  suite_add_tcase(s, tc);
  return s;
}