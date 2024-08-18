#include "test.h"

START_TEST(create_matrix_1) {
  int res, s21_res, rows, columns;
  matrix_t s21_mtrx = {.rows = 0, .columns = 0, .matrix = 0};

  rows = 2;
  columns = 3;

  s21_res = s21_create_matrix(rows, columns, &s21_mtrx);

  res = OK;
  ck_assert_int_eq(rows, s21_mtrx.rows);
  ck_assert_int_eq(columns, s21_mtrx.columns);
  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&s21_mtrx);
}
END_TEST

START_TEST(create_matrix_2) {
  int res, s21_res, rows, columns;
  matrix_t s21_mtrx = {.rows = 0, .columns = 0, .matrix = 0};

  rows = -2;
  columns = 3;

  s21_res = s21_create_matrix(rows, columns, &s21_mtrx);

  res = INCORRECT_MATRIX;
  ck_assert_int_eq(FAILURE, s21_mtrx.rows);
  ck_assert_int_eq(FAILURE, s21_mtrx.columns);
  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&s21_mtrx);
}
END_TEST

START_TEST(create_matrix_3) {
  int res, s21_res, rows, columns;
  matrix_t s21_mtrx = {.rows = 0, .columns = 0, .matrix = 0};

  rows = 2;
  columns = -3;

  s21_res = s21_create_matrix(rows, columns, &s21_mtrx);

  res = INCORRECT_MATRIX;
  ck_assert_int_eq(FAILURE, s21_mtrx.rows);
  ck_assert_int_eq(FAILURE, s21_mtrx.columns);
  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&s21_mtrx);
}
END_TEST

START_TEST(create_matrix_4) {
  int res, s21_res, rows, columns;
  matrix_t s21_mtrx = {.rows = 0, .columns = 0, .matrix = NULL};

  rows = 0;
  columns = 0;

  s21_res = s21_create_matrix(rows, columns, &s21_mtrx);

  res = INCORRECT_MATRIX;
  ck_assert_int_eq(FAILURE, s21_mtrx.rows);
  ck_assert_int_eq(FAILURE, s21_mtrx.columns);
  ck_assert_int_eq(res, s21_res);
  s21_remove_matrix(&s21_mtrx);
}
END_TEST

Suite *suite_create_matrix() {
  Suite *s = suite_create(YELLOW_BG BLACK "s21_create_matrix" RESET);
  TCase *tc = tcase_create("create_matrix_tc");
  tcase_add_test(tc, create_matrix_1);
  tcase_add_test(tc, create_matrix_2);
  tcase_add_test(tc, create_matrix_3);
  tcase_add_test(tc, create_matrix_4);
  suite_add_tcase(s, tc);
  return s;
}
