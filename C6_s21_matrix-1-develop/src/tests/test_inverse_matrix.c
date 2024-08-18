#include "test.h"

START_TEST(inverse_matrix_1) {
  int res, s21_res;
  matrix_t A, result, s21_result = {.rows = 0, .columns = 0};
  s21_create_matrix(3, 3, &A);
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
  result.matrix[0][0] = 1;
  result.matrix[0][1] = -1;
  result.matrix[0][2] = 1;
  result.matrix[1][0] = -38;
  result.matrix[1][1] = 41;
  result.matrix[1][2] = -34;
  result.matrix[2][0] = 27;
  result.matrix[2][1] = -29;
  result.matrix[2][2] = 24;

  res = OK;
  s21_res = s21_inverse_matrix(&A, &s21_result);

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

START_TEST(inverse_matrix_2) {
  int res, s21_res;
  matrix_t A, s21_result = {.rows = 0, .columns = 0};
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = S21_NAN;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  res = CALCULATION_ERROR;
  s21_res = s21_inverse_matrix(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_3) {
  int res, s21_res;
  matrix_t A, result;
  matrix_t s21_result;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &result);

  A.matrix[0][0] = 5;
  result.matrix[0][0] = 0.2;

  res = OK;
  s21_res = s21_inverse_matrix(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(result.rows, s21_result.rows);
  ck_assert_int_eq(result.columns, s21_result.columns);
  ck_assert_double_eq(result.matrix[0][0], s21_result.matrix[0][0]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&s21_result);
}
END_TEST

START_TEST(inverse_matrix_4) {
  int res, s21_res;
  matrix_t A;
  matrix_t s21_result;
  s21_create_matrix(1, 2, &A);

  A.matrix[0][0] = 5;

  res = CALCULATION_ERROR;
  s21_res = s21_inverse_matrix(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_5) {
  int res, s21_res;
  matrix_t A;
  matrix_t s21_result;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = S21_INFINITY;

  res = CALCULATION_ERROR;
  s21_res = s21_inverse_matrix(&A, &s21_result);

  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&A);
}
END_TEST
START_TEST(s21_inverse_1) {
  matrix_t A, C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = -1.0;
  C.matrix[0][2] = 1.0;
  C.matrix[1][0] = -38.0;
  C.matrix[1][1] = 41.0;
  C.matrix[1][2] = -34.0;
  C.matrix[2][0] = 27.0;
  C.matrix[2][1] = -29.0;
  C.matrix[2][2] = 24.0;
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  matrix_t B;
  s21_inverse_matrix(&A, &B);
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

// START_TEST(test_incorrect) {
//   matrix_t m = {0};
//   matrix_t result = {0};
//   int code = s21_inverse_matrix(&m, &result);
//   ck_assert_int_eq(code, INCORRECT_MATRIX);
// }
// END_TEST

START_TEST(determinant) {
  const int size = 2;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 1;
  m.matrix[1][0] = 1;
  m.matrix[1][1] = 1;

  matrix_t result = {0};
  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, CALCULATION_ERROR);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(inverse) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;

  matrix_t res = {0};
  s21_inverse_matrix(&m, &res);

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;

  ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);

  s21_remove_matrix(&expected);
  s21_remove_matrix(&res);
  s21_remove_matrix(&m);
}
END_TEST

Suite *suite_inverse_matrix() {
  Suite *s = suite_create(YELLOW_BG BLACK "s21_inverse_matrix" RESET);
  TCase *tc = tcase_create("inverse_matrix_tc");
  tcase_add_test(tc, inverse_matrix_1);
  tcase_add_test(tc, inverse_matrix_2);
  tcase_add_test(tc, inverse_matrix_3);
  tcase_add_test(tc, inverse_matrix_4);
  tcase_add_test(tc, inverse_matrix_5);
  tcase_add_test(tc, inverse);
  tcase_add_test(tc, s21_inverse_1);
  tcase_add_test(tc, determinant);
  // tcase_add_test(tc, test_incorrect);
  suite_add_tcase(s, tc);
  return s;
}