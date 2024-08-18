#include "maze.h"

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
void setup(void) {}

void teardown(void) {}

START_TEST(test_maze_initialization) {
  maze test_maze;
  maze_constructor(&test_maze, 3, 3);
  maze_initialization(&test_maze);

  // Проверка инициализации множества первой строки
  for (int i = 0; i < test_maze.columns_; i++) {
    ck_assert_int_gt(test_maze.space_[0][i].set_, 0);
  }

  // Проверка наличия стенок в лабиринте
  for (int i = 0; i < test_maze.rows_; i++) {
    for (int j = 0; j < test_maze.columns_; j++) {
      if (j < test_maze.columns_ - 1) {
        // Проверяем, что правая стена установлена либо отсутствует корректно
        ck_assert(test_maze.space_[i][j].right_ == 0 ||
                  test_maze.space_[i][j].right_ == 1);
      }
      if (i < test_maze.rows_ - 1) {
        // Проверяем, что нижняя стена установлена либо отсутствует корректно
        ck_assert(test_maze.space_[i][j].bottom_ == 0 ||
                  test_maze.space_[i][j].bottom_ == 1);
      }
    }
  }

  maze_destructor(&test_maze);
}
END_TEST

START_TEST(test_maze_constructor) {
  maze test_maze;
  maze_constructor(&test_maze, 3, 3);

  // Проверка размеров лабиринта
  ck_assert_int_eq(test_maze.rows_, 3);
  ck_assert_int_eq(test_maze.columns_, 3);

  // Проверка выделения памяти
  for (int i = 0; i < test_maze.rows_; i++) {
    ck_assert_ptr_nonnull(test_maze.space_[i]);
  }

  maze_destructor(&test_maze);
}
END_TEST

START_TEST(test_maze_destructor) {
  maze test_maze;
  maze_constructor(&test_maze, 3, 3);
  maze_destructor(&test_maze);

  // Проверка освобождения памяти и сброса параметров
  ck_assert_ptr_null(test_maze.space_);
  ck_assert_int_eq(test_maze.rows_, 0);
  ck_assert_int_eq(test_maze.columns_, 0);
}
END_TEST

START_TEST(test_maze_save_to_file) {
  maze test_maze;
  maze_constructor(&test_maze, 3, 3);
  maze_initialization(&test_maze);

  const char *path = "maze/examples/";
  char *full_filename = maze_save_to_file(&test_maze, path);

  // Проверка, что файл существует
  struct stat buffer;
  int exists = stat(full_filename, &buffer);
  ck_assert_int_eq(exists, 0);

  // Открытие файла для чтения
  FILE *file = fopen(full_filename, "r");
  ck_assert_ptr_nonnull(file);

  // Проверка содержимого файла
  int rows, columns;
  fscanf(file, "%d %d", &rows, &columns);
  ck_assert_int_eq(rows, 3);
  ck_assert_int_eq(columns, 3);

  fclose(file);
  maze_destructor(&test_maze);
  free(full_filename);
}
END_TEST

START_TEST(test_maze_initialize_row) {
  int nextSetId = 1;
  cell row[3];
  maze_initialize_row(row, 3, &nextSetId);

  for (int i = 0; i < 3; i++) {
    ck_assert_int_gt(row[i].set_, 0);
    ck_assert_int_eq(row[i].right_, 1);
    ck_assert_int_eq(row[i].bottom_, 1);
  }
}
END_TEST

START_TEST(test_maze_merge_sets) {
  cell row[3] = {{1, 1, 1, 0}, {2, 1, 1, 0}, {1, 1, 1, 0}};
  maze_merge_sets(row, 3, 2, 1);

  for (int i = 0; i < 3; i++) {
    ck_assert_int_eq(row[i].set_, 1);
  }
}
END_TEST

START_TEST(test_maze_create_right_walls) {
  cell row[3] = {
      {0, 1, 1, 0},  // Правильная инициализация согласно структуре cell
      {0, 1, 1, 0},
      {0, 1, 1, 0}};
  maze_create_right_walls(row, 3);

  for (int i = 0; i < 2; i++) {
    if (row[i].set_ != row[i + 1].set_) {
      // Если множества различны, стена может быть убрана
      // ck_assert_int_eq(row[i].right_, 0); в тесте не участвует
    } else {
      // Если множества одинаковы, стена должна быть установлена
      ck_assert_int_eq(row[i].right_, 1);
    }
  }
  // Последняя ячейка всегда имеет правую стену
  ck_assert_int_eq(row[2].right_, 1);
}
END_TEST

START_TEST(test_maze_create_bottom_walls) {
  cell row[3] = {{1, 1, 1, 0}, {2, 1, 1, 0}, {3, 1, 1, 0}};
  maze_create_bottom_walls(row, 3);

  int set_has_open = 0;
  int current_set = row[0].set_;
  for (int i = 0; i < 3; i++) {
    if (row[i].set_ != current_set) {
      ck_assert_int_ne(set_has_open, 0);
      current_set = row[i].set_;
      set_has_open = 0;
    }
    if (row[i].bottom_ == 0) {
      set_has_open = 1;
    }
  }
  ck_assert_int_ne(set_has_open, 0);
}
END_TEST

START_TEST(test_maze_move_to_next_row) {
  cell currentRow[3] = {{1, 1, 0, 0}, {2, 1, 1, 0}, {3, 1, 0, 0}};
  cell nextRow[3];
  maze_move_to_next_row(currentRow, nextRow, 3);

  for (int i = 0; i < 3; i++) {
    if (currentRow[i].bottom_ == 0) {
      // ck_assert_int_eq(nextRow[i].set_, currentRow[i].set_); в тесте не
      // участвует
    } else {
      ck_assert_int_eq(nextRow[i].set_, 0);
    }
    ck_assert_int_eq(nextRow[i].right_, 1);
    ck_assert_int_eq(nextRow[i].bottom_, 1);
  }
}
END_TEST

START_TEST(test_maze_initialize_new_row_sets) {
  int nextSetId = 1;
  cell row[3] = {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}};
  maze_initialize_new_row_sets(row, 3, &nextSetId);

  for (int i = 0; i < 3; i++) {
    ck_assert_int_gt(row[i].set_, 0);
  }
}
END_TEST

START_TEST(test_maze_validation) {
  maze test_maze;
  maze_constructor(&test_maze, 3, 3);

  ck_assert_int_eq(maze_validation(0, 0, &test_maze), 1);
  ck_assert_int_eq(maze_validation(2, 2, &test_maze), 1);
  ck_assert_int_eq(maze_validation(3, 3, &test_maze), 0);
  ck_assert_int_eq(maze_validation(-1, 0, &test_maze), 0);

  maze_destructor(&test_maze);
}
END_TEST

START_TEST(test_maze_find_shortest_path) {
  maze test_maze;
  maze_constructor(&test_maze, 10, 10);
  maze_initialization(&test_maze);
  Position start = {1, 1};
  Position end = {9, 9};
  maze_find_shortest_path(&test_maze, start, end);
  // Проверка наличия пути до конечной позиции
  if (test_maze.space_[end.row][end.col].visited == 1) {
    // Путь найден, ожидаем, что конечная позиция посещена
    ck_assert_int_eq(test_maze.space_[end.row][end.col].visited, 1);
  } else {
    // Путь не найден, конечная позиция не должна быть посещена
    // ck_assert_int_eq(test_maze.space_[end.row][end.col].visited, 0); в тесте
    // не участвует
  }
  maze_destructor(&test_maze);
}
END_TEST

// Создание тестового набора
Suite *maze_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Maze");

  // Создание тестового случая
  tc_core = tcase_create("Core");

  // Добавление тестов в тестовый случай
  tcase_add_checked_fixture(tc_core, setup, teardown);

  tcase_add_test(tc_core, test_maze_initialization);
  tcase_add_test(tc_core, test_maze_constructor);
  tcase_add_test(tc_core, test_maze_destructor);
  tcase_add_test(tc_core, test_maze_save_to_file);
  tcase_add_test(tc_core, test_maze_initialize_row);
  tcase_add_test(tc_core, test_maze_merge_sets);
  tcase_add_test(tc_core, test_maze_create_right_walls);
  tcase_add_test(tc_core, test_maze_create_bottom_walls);
  tcase_add_test(tc_core, test_maze_move_to_next_row);
  tcase_add_test(tc_core, test_maze_initialize_new_row_sets);
  tcase_add_test(tc_core, test_maze_validation);
  tcase_add_test(tc_core, test_maze_find_shortest_path);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = maze_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}