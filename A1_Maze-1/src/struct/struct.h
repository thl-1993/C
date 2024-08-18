#ifndef A1_MAZE_STRUCT_H
#define A1_MAZE_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
// #include "../cave/cave.h"
// #include "../interface/interface.h"
// #include "../maze/maze.h"

typedef struct cell {
    int set_;    // Идентификатор множества (не используется в данном алгоритме)
    int bottom_; // Наличие нижней стены
    int right_;  // Наличие правой стены
    int visited; // Флаг посещения
} cell;

typedef struct maze {
    int rows_;
    int columns_;
    cell** space_;
} maze;

// Структура для хранения координат ячеек
typedef struct {
    int row;
    int col;
} Position;

typedef struct cave {
  int rows_;
  int columns_;
  int** space_;
} cave;

/* структура для хранения Q-таблицы и другой необходимой информации.*/
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ACTION_COUNT // Количество действий
} Action;

typedef struct {
    int rows;
    int cols;
    double*** Q;  // Q-таблица: Q[row][col][action]
    double alpha; // Коэффициент обучения
    double gamma; // Коэффициент дисконтирования
    double epsilon; // Вероятность выбора случайного действия (epsilon-greedy)
} QLearningAgent;

#endif  // A1_MAZE_STRUCT_H