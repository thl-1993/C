#ifndef A1_MAZE_INTERFACE_C
#define A1_MAZE_INTERFACE_C
#include <ncurses.h>

#include "../interface/interface.h"
#include "../maze/maze.h"

void printFullMaze(maze* obj) {
  // Печать верхней границы
  for (int col = 0; col < obj->columns_; col++) {
    printw(" _");  // Верхняя стена для каждой ячейки
  }
  printw("\n");

  // Печать лабиринта
  for (int row = 0; row < obj->rows_; row++) {
    for (int col = 0; col < obj->columns_; col++) {
      // Левые стены
      if (col == 0) {
        printw("|");
      }
      // Нижние стены и правые стены
      if (obj->space_[row][col].bottom_ == 1) {
        printw("_");
      } else {
        printw(" ");
      }

      if (obj->space_[row][col].right_ == 1) {
        printw("|");
      } else {
        printw(" ");
      }
    }
    printw("\n");
  }
}

// int main() {
//   initscr();
//   noecho();
//   clear();

//   // Создание и инициализация лабиринта
//   maze obj;
//   maze_constructor(&obj, 20, 20);
//   maze_save_to_file(&obj, "maze/");
//   // Вывод параметров лабиринта
//   printw("row = %d\n", obj.rows_);
//   printw("columns = %d\n", obj.columns_);

//   // Вывод полного лабиринта
//   printFullMaze(&obj);

//   // Завершение работы и освобождение ресурсов
//   // save_maze_to_file(&obj, "generated_maze.txt");

//   Position start = {5, 1};
//   Position end = {10, 19};
//   maze_find_shortest_path(&obj, start, end);
//   maze_destructor(&obj);
//   getch();
//   endwin();

//   return 0;
// }
int main() {
  srand(time(NULL));

  initscr();
  noecho();
  clear();

  // Создание и инициализация лабиринта
  maze obj;
  // maze_loading("./maze/examples/example_3.txt", &obj);
  maze_constructor(&obj, 33, 33);
  maze_save_to_file(&obj, "maze/");
  // // Вывод параметров лабиринта
  printw("row = %d\n", obj.rows_);
  printw("columns = %d\n", obj.columns_);

  // // Вывод полного лабиринта
  printFullMaze(&obj);

  Position start = {1, 1};
  Position end = {1, 1};

  // Проверка координат start и end
  ////////!!!!!!!!! почему то эта проверка в функциях не работает, валится на
  ///сохранении файла
  if (start.row < 1 || start.row >= obj.rows_ - 1 || start.col < 1 ||
      start.col >= obj.columns_ - 1) {
    endwin();  // Корректное завершение работы ncurses
    printf(ANSI_COLOR_RED "error: start position out of bounds" ANSI_COLOR_RESET
                          "\n");
    exit(EXIT_FAILURE);
  }
  if (end.row < 1 || end.row >= obj.rows_ - 1 || end.col < 1 ||
      end.col >= obj.columns_ - 1) {
    endwin();  // Корректное завершение работы ncurses
    printf(ANSI_COLOR_RED "error: end position out of bounds" ANSI_COLOR_RESET
                          "\n");
    exit(EXIT_FAILURE);
  }
  // Инициализация и обучение агента
  QLearningAgent agent;
  initialize_agent(&agent, obj.rows_, obj.columns_, 0.1, 0.9, 0.1);
  train_agent(&agent, &obj, end, 10000);  // Обучение агента

  // Использование обученного агента для нахождения пути
  find_path_with_agent(&agent, &obj, start, end);

  // Завершение работы и освобождение ресурсов
  maze_save_to_file(&obj, "generated_maze.txt");
  maze_find_shortest_path(&obj, start, end);
  maze_destructor(&obj);

  getch();
  endwin();

  return 0;
}
#endif  // A1_MAZE_INTERFACE_C