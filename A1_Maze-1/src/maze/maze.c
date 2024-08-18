#ifndef A1_MAZE_MAZE_C
#define A1_MAZE_MAZE_C

#include "maze.h"

void maze_loading(char* file_name, maze* obj) {
  FILE* file = fopen(file_name, "r");
  if (file != NULL) {
    int check = fscanf(file, "%d %d", &obj->rows_, &obj->columns_);
    if (check == 2) {
      // Проверка количества строк и столбцов
      if (obj->columns_ > 50) {
        printf(ANSI_COLOR_RED "error: columns > 50" ANSI_COLOR_RESET "\n");
        fclose(file);
        exit(EXIT_FAILURE);
      }
      if (obj->rows_ > 50) {
        printf(ANSI_COLOR_RED "error: rows > 50" ANSI_COLOR_RESET "\n");
        fclose(file);
        exit(EXIT_FAILURE);
      }

      // Выделение памяти под лабиринт
      obj->space_ = (cell**)malloc(obj->rows_ * sizeof(cell*));
      for (int i = 0; i < obj->rows_; i++) {
        obj->space_[i] = (cell*)malloc(obj->columns_ * sizeof(cell));
      }

      // Чтение данных из файла
      for (int row = 0; row < obj->rows_; row++) {
        for (int col = 0; col < obj->columns_; col++) {
          fscanf(file, "%d", &obj->space_[row][col].right_);
        }
      }
      for (int row = 0; row < obj->rows_; row++) {
        for (int col = 0; col < obj->columns_; col++) {
          fscanf(file, "%d", &obj->space_[row][col].bottom_);
        }
      }
    }
    fclose(file);
  } else {
    perror("Failed to open file");
  }
}

void maze_constructor(maze* obj, int rows, int columns) {
  // Инициализация параметров лабиринта
  obj->rows_ = rows;
  obj->columns_ = columns;
  // Выделение памяти под лабиринт
  obj->space_ = (cell**)malloc(rows * sizeof(cell*));
  for (int i = 0; i < rows; i++) {
    obj->space_[i] = (cell*)malloc(columns * sizeof(cell));
  }
  // Инициализация лабиринта
  maze_initialization(obj);
}

void maze_initialization(maze* obj) {
  if (obj->columns_ > 50) {
    endwin();
    printf(ANSI_COLOR_RED "error: columns > 50" ANSI_COLOR_RESET "\n");
    exit(EXIT_FAILURE);
  }
  if (obj->rows_ > 50) {
    endwin();
    printf(ANSI_COLOR_RED "error: rows > 50" ANSI_COLOR_RESET "\n");
    exit(EXIT_FAILURE);
  }
  int nextSetId = 1;  // Используется для присваивания уникальных
                      // идентификаторов множеств ячейкам лабиринта.
  // Инициализация первой строки
  maze_initialize_row(obj->space_[0], obj->columns_, &nextSetId);
  maze_create_right_walls(obj->space_[0], obj->columns_);
  maze_create_bottom_walls(obj->space_[0], obj->columns_);
  // Обработка оставшихся строк
  for (int i = 1; i < obj->rows_; i++) {
    maze_move_to_next_row(obj->space_[i - 1], obj->space_[i], obj->columns_);
    maze_initialize_new_row_sets(obj->space_[i], obj->columns_, &nextSetId);
    maze_create_right_walls(obj->space_[i], obj->columns_);
    maze_create_bottom_walls(obj->space_[i], obj->columns_);
  }
  // Удаление всех правых стенок в последней строке и установка всех нижних
  // стенок в последней строке
  for (int j = 0; j < obj->columns_ - 1; j++) {
    if (obj->space_[obj->rows_ - 1][j].set_ !=
        obj->space_[obj->rows_ - 1][j + 1].set_) {
      obj->space_[obj->rows_ - 1][j].right_ = 0;
      maze_merge_sets(obj->space_[obj->rows_ - 1], obj->columns_,
                      obj->space_[obj->rows_ - 1][j + 1].set_,
                      obj->space_[obj->rows_ - 1][j].set_);
    }
  }
  for (int j = 0; j < obj->columns_; j++) {
    obj->space_[obj->rows_ - 1][j].bottom_ =
        1;  // Устанавливаем нижние стены в последней строке
  }
}

void maze_initialize_row(cell* row, int width, int* nextSetId) {
  for (int i = 0; i < width; i++) {
    row[i].set_ = (*nextSetId)++;
    row[i].right_ = 1;
    row[i].bottom_ = 1;
  }
}

void maze_initialize_new_row_sets(cell* row, int width, int* nextSetId) {
  for (int i = 0; i < width; i++) {
    if (row[i].set_ == 0) {
      row[i].set_ = (*nextSetId)++;
    }
  }
}

void maze_merge_sets(cell* row, int width, int fromSet, int toSet) {
  for (int i = 0; i < width; i++) {
    if (row[i].set_ == fromSet) {
      row[i].set_ = toSet;
    }
  }
}

void maze_create_right_walls(cell* row, int width) {
  for (int i = 0; i < width - 1; i++) {
    if (row[i].set_ != row[i + 1].set_ && rand() % 2 == 0) {
      row[i].right_ = 0;
      maze_merge_sets(row, width, row[i + 1].set_, row[i].set_);
    } else {
      row[i].right_ = 1;  // Устанавливаем стену, если они в одном множестве или
                          // случайное число не равно 0
    }
  }
  row[width - 1].right_ = 1;  // Последняя ячейка всегда имеет правую стену
}

void maze_create_bottom_walls(cell* row, int width) {
  int currentSet = row[0].set_;
  int hasOpenCell = 0;
  for (int i = 0; i < width; i++) {
    if (i > 0 && row[i].set_ != currentSet) {
      if (!hasOpenCell) {
        row[i - 1].bottom_ = 0;
      }
      currentSet = row[i].set_;
      hasOpenCell = 0;
    }
    if (rand() % 2 == 0) {
      row[i].bottom_ = 0;
      hasOpenCell = 1;
    }
  }
  if (!hasOpenCell) {
    row[width - 1].bottom_ = 0;
  }
}

void maze_move_to_next_row(cell* currentRow, cell* nextRow, int width) {
  for (int i = 0; i < width; i++) {
    if (currentRow[i].bottom_ == 0) {
      nextRow[i].set_ = currentRow[i].set_;
    } else {
      nextRow[i].set_ = 0;
    }
    nextRow[i].right_ = 1;
    nextRow[i].bottom_ = 1;
  }
}

// Генерация уникального имени файла на основе временной метки
void maze_generate_unique_filename(char* filename, size_t size) {
  time_t now = time(NULL);
  struct tm* t = localtime(&now);
  snprintf(filename, size, "generated_maze_%04d%02d%02d_%02d%02d%02d.txt",
           t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min,
           t->tm_sec);
}

// Сохранение лабиринта в файл
void maze_generate_unique_filename(char* filename, size_t size);
// Сохранение лабиринта в файл
char* maze_save_to_file(maze* obj, const char* path) {
  char temp_filename[256];
  maze_generate_unique_filename(temp_filename, sizeof(temp_filename));

  // Создание полного пути к файлу
  char full_path[512];
  snprintf(full_path, sizeof(full_path), "%s%s", path, temp_filename);

  // Отладочный вывод, показывающий полный путь
  printf("Saving maze to file: %s\n", full_path);

  FILE* file = fopen(full_path, "w");
  if (file == NULL) {
    perror("Failed to open file");
    return NULL;
  }

  fprintf(file, "%d %d\n", obj->rows_, obj->columns_);

  // Запись матрицы правых стен
  for (int i = 0; i < obj->rows_; i++) {
    for (int j = 0; j < obj->columns_; j++) {
      fprintf(file, "%d ", obj->space_[i][j].right_);
    }
    fprintf(file, "\n");
  }
  fprintf(file, "\n");

  // Запись матрицы нижних стен
  for (int i = 0; i < obj->rows_; i++) {
    for (int j = 0; j < obj->columns_; j++) {
      fprintf(file, "%d ", obj->space_[i][j].bottom_);
    }
    fprintf(file, "\n");
  }

  fclose(file);

  // Выделяем память для полного пути и возвращаем его
  char* result = (char*)malloc(strlen(full_path) + 1);
  if (result != NULL) {
    strcpy(result, full_path);
  }
  return result;
}

/*поиск наикратчайшего пути*/
int maze_validation(int row, int col, maze* obj) {
  return row >= 0 && row < obj->rows_ && col >= 0 && col < obj->columns_;
}
// Сохранение полного лабиринта с путем
void maze_save_full_with_path(maze* obj, Position* path, int path_length) {
  char filename[256];
  maze_generate_unique_filename(filename, sizeof(filename));
  FILE* file = fopen(filename, "w");
  if (file == NULL) {
    perror("Failed to open file");
    return;
  }
  // Визуализация пути на карте
  for (int i = 0; i < obj->rows_; i++) {
    for (int j = 0; j < obj->columns_; j++) {
      bool is_path = false;
      for (int k = 0; k < path_length; k++) {
        if (path[k].row == i && path[k].col == j) {
          is_path = true;
          break;
        }
      }
      if (is_path) {
        fprintf(file, " * ");
      } else {
        fprintf(file, " . ");
      }
    }
    fprintf(file, "\n");
  }

  fclose(file);
}

// Найти наикратчайший путь в лабиринте
void maze_find_shortest_path(maze* obj, Position start, Position end) {
  // Проверка корректности координат начальной и конечной точек
  if (start.row < 1 || start.row >= obj->rows_ || start.col < 1 ||
      start.col >= obj->columns_) {
    endwin();  // Корректное завершение работы ncurses
    printf(ANSI_COLOR_RED "error: start position out of bounds" ANSI_COLOR_RESET
                          "\n");
    exit(EXIT_FAILURE);
  }
  if (end.row < 1 || end.row >= obj->rows_ || end.col < 1 ||
      end.col >= obj->columns_) {
    endwin();  // Корректное завершение работы ncurses
    printf(ANSI_COLOR_RED "error: end position out of bounds" ANSI_COLOR_RESET
                          "\n");
    exit(EXIT_FAILURE);
  }
  int direction[4][2] = {{-1, 0},
                         {1, 0},
                         {0, -1},
                         {0, 1}};  // Направления: вверх, вниз, влево, вправо
  int** visited = (int**)malloc(obj->rows_ * sizeof(int*));
  Position** prev = (Position**)malloc(obj->rows_ * sizeof(Position*));
  for (int i = 0; i < obj->rows_; i++) {
    visited[i] = (int*)malloc(obj->columns_ * sizeof(int));
    prev[i] = (Position*)malloc(obj->columns_ * sizeof(Position));
    for (int j = 0; j < obj->columns_; j++) {
      visited[i][j] = 0;
      prev[i][j] = (Position){-1, -1};
    }
  }

  Position* queue =
      (Position*)malloc(obj->rows_ * obj->columns_ * sizeof(Position));
  int front = 0, rear = 0;
  queue[rear++] = start;
  visited[start.row][start.col] = 1;

  while (front < rear) {
    Position current = queue[front++];
    if (current.row == end.row && current.col == end.col) {
      break;
    }

    for (int i = 0; i < 4; i++) {
      int new_row = current.row + direction[i][0];
      int new_col = current.col + direction[i][1];

      if (maze_validation(new_row, new_col, obj) &&
          !visited[new_row][new_col]) {
        // Проверка наличия стен между текущей и новой позицией
        if ((direction[i][0] == -1 &&
             obj->space_[new_row][new_col].bottom_ == 0) ||  // Вверх
            (direction[i][0] == 1 &&
             obj->space_[current.row][current.col].bottom_ == 0) ||  // Вниз
            (direction[i][1] == -1 &&
             obj->space_[new_row][new_col].right_ == 0) ||  // Влево
            (direction[i][1] == 1 &&
             obj->space_[current.row][current.col].right_ == 0)) {  // Вправо
          queue[rear++] = (Position){new_row, new_col};
          visited[new_row][new_col] = 1;
          prev[new_row][new_col] = current;
        }
      }
    }
  }

  // Построение пути
  if (visited[end.row][end.col]) {
    Position path[obj->rows_ * obj->columns_];
    int length = 0;
    for (Position at = end; at.row != -1 && at.col != -1;
         at = prev[at.row][at.col]) {
      path[length++] = at;
    }

    // Вывод пути в консоль
    printf("Shortest path from (%d, %d) to (%d, %d):\n", start.row, start.col,
           end.row, end.col);
    for (int i = length - 1; i >= 0; i--) {
      printf("(%d, %d)\n", path[i].row, path[i].col);
    }

    maze_save_full_with_path(obj, path, length);

    // Пометить путь как посещенный в obj->space_
    for (int i = 0; i < length; i++) {
      obj->space_[path[i].row][path[i].col].visited = 1;
    }
  } else {
    printf(ANSI_COLOR_RED "error: no path found" ANSI_COLOR_RESET "\n");
  }

  // Освобождение памяти
  for (int i = 0; i < obj->rows_; i++) {
    free(visited[i]);
    free(prev[i]);
  }
  free(visited);
  free(prev);
  free(queue);
}

// Функция для выполнения действия агентом и возвращения нового состояния
Position take_action(Position pos, Action action, maze* m) {
  Position new_pos = pos;
  switch (action) {
    case UP:
      if (pos.row > 0 && m->space_[pos.row - 1][pos.col].bottom_ == 0) {
        new_pos.row -= 1;
      }
      break;
    case DOWN:
      if (pos.row < m->rows_ - 1 && m->space_[pos.row][pos.col].bottom_ == 0) {
        new_pos.row += 1;
      }
      break;
    case LEFT:
      if (pos.col > 0 && m->space_[pos.row][pos.col - 1].right_ == 0) {
        new_pos.col -= 1;
      }
      break;
    case RIGHT:
      if (pos.col < m->columns_ - 1 &&
          m->space_[pos.row][pos.col].right_ == 0) {
        new_pos.col += 1;
      }
      break;
    default:
      break;
  }
  return new_pos;
}

// Функция для вычисления награды
double get_reward(Position pos, Position goal) {
  return (pos.row == goal.row && pos.col == goal.col) ? 100.0 : -1.0;
}

// Функция для обновления Q-таблицы
void update_q_table(QLearningAgent* agent, Position current, Action action,
                    Position next, double reward) {
  double max_q = -1e9;
  for (int a = 0; a < ACTION_COUNT; a++) {
    if (agent->Q[next.row][next.col][a] > max_q) {
      max_q = agent->Q[next.row][next.col][a];
    }
  }

  agent->Q[current.row][current.col][action] =
      (1 - agent->alpha) * agent->Q[current.row][current.col][action] +
      agent->alpha * (reward + agent->gamma * max_q);
}

// Функция для выбора действия на основе стратегии epsilon-greedy
Action choose_action(QLearningAgent* agent, Position pos) {
  if ((double)rand() / RAND_MAX < agent->epsilon) {
    return rand() % ACTION_COUNT;  // Случайное действие
  } else {
    double max_q = -1e9;
    Action best_action = UP;
    for (int a = 0; a < ACTION_COUNT; a++) {
      if (agent->Q[pos.row][pos.col][a] > max_q) {
        max_q = agent->Q[pos.row][pos.col][a];
        best_action = a;
      }
    }
    return best_action;
  }
}

// Функция для инициализации агента
void initialize_agent(QLearningAgent* agent, int rows, int cols, double alpha,
                      double gamma, double epsilon) {
  agent->rows = rows;
  agent->cols = cols;
  agent->alpha = alpha;
  agent->gamma = gamma;
  agent->epsilon = epsilon;

  agent->Q = (double***)malloc(rows * sizeof(double**));
  for (int i = 0; i < rows; i++) {
    agent->Q[i] = (double**)malloc(cols * sizeof(double*));
    for (int j = 0; j < cols; j++) {
      agent->Q[i][j] = (double*)malloc(ACTION_COUNT * sizeof(double));
      for (int k = 0; k < ACTION_COUNT; k++) {
        agent->Q[i][j][k] = 0.0;
      }
    }
  }
}

// Функция для обучения агента
void train_agent(QLearningAgent* agent, maze* m, Position goal, int episodes) {
  for (int e = 0; e < episodes; e++) {
    Position pos = {rand() % m->rows_,
                    rand() % m->columns_};  // Начальная позиция
    while (!(pos.row == goal.row && pos.col == goal.col)) {
      Action action = choose_action(agent, pos);
      Position new_pos = take_action(pos, action, m);
      double reward = get_reward(new_pos, goal);
      update_q_table(agent, pos, action, new_pos, reward);
      pos = new_pos;
    }
  }
}

// Функция для нахождения пути с помощью обученного агента
void find_path_with_agent(QLearningAgent* agent, maze* m, Position start,
                          Position end) {
  // Проверка корректности координат начальной и конечной точек
  if (start.row < 1 || start.row >= m->rows_ || start.col < 1 ||
      start.col >= m->columns_) {
    endwin();  // Корректное завершение работы ncurses
    printf(ANSI_COLOR_RED "error: start position out of bounds" ANSI_COLOR_RESET
                          "\n");
    return;
  }
  if (end.row < 1 || end.row >= m->rows_ || end.col < 1 ||
      end.col >= m->columns_) {
    endwin();  // Корректное завершение работы ncurses
    printf(ANSI_COLOR_RED "error: end position out of bounds" ANSI_COLOR_RESET
                          "\n");
    return;
  }

  Position pos = start;
  while (!(pos.row == end.row && pos.col == end.col)) {
    Action action = choose_action(agent, pos);
    pos = take_action(pos, action, m);
    printw("(%d, %d)\n", pos.row, pos.col);
  }
}

void maze_destructor(maze* obj) {
  if (obj->space_ != NULL) {
    for (int row = 0; row < obj->rows_; row++) {
      if (obj->space_[row] != NULL) {
        free(obj->space_[row]);
      }
    }
    free(obj->space_);
    obj->space_ = NULL;  // Убедитесь, что указатель установлен в NULL
  }
  obj->rows_ = 0;
  obj->columns_ = 0;
}
#endif  // A1_MAZE_MAZE_C
