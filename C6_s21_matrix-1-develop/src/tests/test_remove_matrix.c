#include "test.h"

START_TEST(remove_matrix_1) {
  int rows, columns;
  matrix_t s21_mtrx = {.rows = 0, .columns = 0, .matrix = 0};

  rows = 2;
  columns = 3;

  s21_create_matrix(rows, columns, &s21_mtrx);

  s21_remove_matrix(&s21_mtrx);
  ck_assert_int_eq(OK, s21_mtrx.rows);
  ck_assert_int_eq(OK, s21_mtrx.columns);
}
END_TEST

START_TEST(remove_matrix_2) {
  int rows, columns;
  matrix_t s21_mtrx = {.rows = 0, .columns = 0, .matrix = 0};

  rows = -2;
  columns = 3;

  s21_create_matrix(rows, columns, &s21_mtrx);

  s21_remove_matrix(&s21_mtrx);
  ck_assert_int_eq(OK, s21_mtrx.rows);
  ck_assert_int_eq(OK, s21_mtrx.columns);
}
END_TEST

START_TEST(remove_matrix_3) {
  int rows, columns;
  matrix_t s21_mtrx = {.rows = 0, .columns = 0, .matrix = 0};

  rows = 2;
  columns = -3;

  s21_create_matrix(rows, columns, &s21_mtrx);

  s21_remove_matrix(&s21_mtrx);
  ck_assert_int_eq(OK, s21_mtrx.rows);
  ck_assert_int_eq(OK, s21_mtrx.columns);
}
END_TEST

START_TEST(remove_matrix_4) {
  int rows, columns;
  matrix_t s21_mtrx = {.rows = 0, .columns = 0, .matrix = NULL};

  rows = 0;
  columns = 0;

  s21_create_matrix(rows, columns, &s21_mtrx);

  s21_remove_matrix(&s21_mtrx);
  ck_assert_int_eq(OK, s21_mtrx.rows);
  ck_assert_int_eq(OK, s21_mtrx.columns);
}
END_TEST

Suite *suite_remove_matrix() {
  Suite *s = suite_create(YELLOW_BG BLACK "s21_remove_matrix" RESET);
  TCase *tc = tcase_create("remove_matrix_tc");
  tcase_add_test(tc, remove_matrix_1);
  tcase_add_test(tc, remove_matrix_2);
  tcase_add_test(tc, remove_matrix_3);
  tcase_add_test(tc, remove_matrix_4);
  suite_add_tcase(s, tc);
  return s;
}
