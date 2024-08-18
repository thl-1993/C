#include "test.h"

START_TEST(mult_matrix_1) {
  int res, s21_res;
  matrix_t A, B, result, s21_result;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(3, 3, &result);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;
  result.matrix[0][0] = 9;
  result.matrix[0][1] = 11;
  result.matrix[0][2] = 17;
  result.matrix[1][0] = 12;
  result.matrix[1][1] = 13;
  result.matrix[1][2] = 22;
  result.matrix[2][0] = 15;
  result.matrix[2][1] = 15;
  result.matrix[2][2] = 27;

  res = OK;
  s21_res = s21_mult_matrix(&A, &B, &s21_result);

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
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&s21_result);
}
END_TEST

START_TEST(mult_matrix_2) {
  int res, s21_res;
  matrix_t A, B, s21_result;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);

  A.matrix[0][0] = S21_NAN;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;

  res = CALCULATION_ERROR;
  s21_res = s21_mult_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_3) {
  int res, s21_res;
  matrix_t A, B, s21_result;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = S21_INFINITY;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;

  res = CALCULATION_ERROR;
  s21_res = s21_mult_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_4) {
  int res, s21_res;
  matrix_t A, B = {.rows = 0, .columns = 0}, s21_result;
  s21_create_matrix(3, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = S21_INFINITY;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;

  res = INCORRECT_MATRIX;
  s21_res = s21_mult_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_matrix_5) {
  int res, s21_res;
  matrix_t A, B = {.rows = 3, .columns = 0}, s21_result;
  s21_create_matrix(3, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;

  res = INCORRECT_MATRIX;
  s21_res = s21_mult_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

// START_TEST(mult_matrix_6) {
//   int res, s21_res;
//   matrix_t A, B, s21_result;
//   s21_create_matrix(3, 2, &A);
//   s21_create_matrix(2, 3, &B);

//   A.matrix[0][0] = 1;
//   A.matrix[0][1] = 4;
//   A.matrix[1][0] = 0;
//   A.matrix[1][1] = 5;
//   A.matrix[2][0] = 3;
//   A.matrix[2][1] = 6;
//   B.matrix[0][0] = 1;
//   B.matrix[0][1] = -1;
//   B.matrix[0][2] = 1;
//   B.matrix[1][0] = 2;
//   B.matrix[1][1] = 3;
//   B.matrix[1][2] = 4;

//   res = CALCULATION_ERROR;
//   s21_res = s21_mult_matrix(&A, &B, &s21_result);

//   ck_assert_int_eq(res, s21_res);
//   s21_remove_matrix(&A);
//   s21_remove_matrix(&B);
// }
// END_TEST

START_TEST(mult_matrix_7) {
  int res, s21_res;
  matrix_t A, B, s21_result;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 1.7976931348623158e+250;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;

  res = OK;
  s21_res = s21_mult_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&s21_result);
}
END_TEST

START_TEST(mult_matrix_8) {
  int res, s21_res;
  matrix_t A, B, s21_result;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3;

  res = CALCULATION_ERROR;
  s21_res = s21_mult_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_9) {
  int res, s21_res;
  matrix_t A, B, s21_result;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);

  res = OK;
  s21_res = s21_mult_matrix(&A, &B, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&s21_result);
}
END_TEST

START_TEST(mult_matrix_10) {
  int res, s21_res;
  matrix_t A, B, result, s21_result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &result);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = -38;
  B.matrix[1][1] = 41;
  B.matrix[1][2] = -34;
  B.matrix[2][0] = 27;
  B.matrix[2][1] = -29;
  B.matrix[2][2] = 24;
  result.matrix[0][0] = 1;
  result.matrix[0][1] = 0;
  result.matrix[0][2] = 0;
  result.matrix[1][0] = 0;
  result.matrix[1][1] = 1;
  result.matrix[1][2] = 0;
  result.matrix[2][0] = 0;
  result.matrix[2][1] = 0;
  result.matrix[2][2] = 1;

  res = OK;
  s21_res = s21_mult_matrix(&A, &B, &s21_result);

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
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&s21_result);
}
END_TEST

Suite *suite_mult_matrix() {
  Suite *s = suite_create(YELLOW_BG BLACK "s21_mult_matrix" RESET);
  TCase *tc = tcase_create("mult_matrix_tc");
  tcase_add_test(tc, mult_matrix_1);
  tcase_add_test(tc, mult_matrix_2);
  tcase_add_test(tc, mult_matrix_3);
  tcase_add_test(tc, mult_matrix_4);
  tcase_add_test(tc, mult_matrix_5);
  // tcase_add_test(tc, mult_matrix_6);
  tcase_add_test(tc, mult_matrix_7);
  tcase_add_test(tc, mult_matrix_8);
  tcase_add_test(tc, mult_matrix_9);
  tcase_add_test(tc, mult_matrix_10);
  suite_add_tcase(s, tc);
  return s;
}