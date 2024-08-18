#ifndef A1_MAZE_MAZE_H
#define A1_MAZE_MAZE_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

#include "../struct/struct.h"

/**
 * @brief Выделяет память под лабиринт заданного размера и инициализирует его.
 *
 * @param obj Указатель на структуру лабиринта.
 * @param rows Количество строк в лабиринте.
 * @param columns Количество столбцов в лабиринте.
 */
void maze_constructor(maze* obj, int rows, int columns);

/**
 * @brief Освобождает память, выделенную под лабиринт, и сбрасывает его
 * параметры.
 *
 * @param obj Указатель на структуру лабиринта.
 */
void maze_destructor(maze* obj);

/**
 * @brief Инициализирует лабиринт, создавая уникальные множества для ячеек и
 * устанавливая стены между ними.
 *
 * @param obj Указатель на структуру лабиринта.
 */
void maze_initialization(maze* obj);

/**
 * @brief Загружает лабиринт из файла.
 *
 * @param file_name Имя файла с лабиринтом.
 * @param obj Указатель на структуру лабиринта.
 */
void maze_loading(char* file_name, maze* obj);

/**
 * @brief Сохраняет параметры и структуру лабиринта в файл, включая размеры и
 * информацию о стенах.
 *
 * @param obj Указатель на структуру лабиринта.
 * @param path Путь к директории, где будет сохранен файл.
 * @return Полный путь к сохраненному файлу.
 */
char* maze_save_to_file(maze* obj, const char* path);

/**
 * @brief Инициализирует каждую ячейку строки лабиринта, присваивая ей
 * уникальный идентификатор множества и устанавливая стены.
 *
 * @param row Указатель на строку ячеек лабиринта.
 * @param width Ширина строки (количество ячеек).
 * @param nextSetId Указатель на следующий уникальный идентификатор множества.
 */
void maze_initialize_row(cell* row, int width, int* nextSetId);

/**
 * @brief Объединяет два множества ячеек в строке, присваивая ячейкам из одного
 * множества идентификатор другого множества.
 *
 * @param row Указатель на строку ячеек лабиринта.
 * @param width Ширина строки (количество ячеек).
 * @param fromSet Идентификатор множества, из которого объединяются ячейки.
 * @param toSet Идентификатор множества, в которое объединяются ячейки.
 */
void maze_merge_sets(cell* row, int width, int fromSet, int toSet);

/**
 * @brief Случайным образом удаляет правые стены между ячейками разных множеств
 * в строке и объединяет их в одно множество.
 *
 * @param row Указатель на строку ячеек лабиринта.
 * @param width Ширина строки (количество ячеек).
 */
void maze_create_right_walls(cell* row, int width);

/**
 * @brief Случайным образом удаляет нижние стены в строке, гарантируя, что
 * каждая ячейка множества имеет хотя бы одну открытую ячейку.
 *
 * @param row Указатель на строку ячеек лабиринта.
 * @param width Ширина строки (количество ячеек).
 */
void maze_create_bottom_walls(cell* row, int width);

/**
 * @brief Переносит множества ячеек из текущей строки в следующую, сохраняя
 * идентификаторы для ячеек без нижних стен и инициализируя остальные ячейки.
 *
 * @param currentRow Указатель на текущую строку ячеек лабиринта.
 * @param nextRow Указатель на следующую строку ячеек лабиринта.
 * @param width Ширина строки (количество ячеек).
 */
void maze_move_to_next_row(cell* currentRow, cell* nextRow, int width);

/**
 * @brief Присваивает новые уникальные идентификаторы множествам ячеек в строке,
 * у которых идентификатор равен нулю.
 *
 * @param row Указатель на строку ячеек лабиринта.
 * @param width Ширина строки (количество ячеек).
 * @param nextSetId Указатель на следующий уникальный идентификатор множества.
 */
void maze_initialize_new_row_sets(cell* row, int width, int* nextSetId);

/**
 * @brief Проверяет, находятся ли указанные координаты внутри границ лабиринта.
 *
 * @param row Номер строки.
 * @param col Номер столбца.
 * @param obj Указатель на структуру лабиринта.
 * @return Возвращает 1, если координаты внутри границ лабиринта, иначе 0.
 */
int maze_validation(int row, int col, maze* obj);

/**
 * @brief Находит и сохраняет кратчайший путь от начальной до конечной позиции в
 * лабиринте, используя поиск в ширину (BFS).
 *
 * @param obj Указатель на структуру лабиринта.
 * @param start Начальная позиция.
 * @param end Конечная позиция.
 */
void maze_find_shortest_path(maze* obj, Position start, Position end);

/**
 * @brief Сохраняет полный лабиринт с путем.
 *
 * @param obj Указатель на структуру лабиринта.
 * @param path Указатель на массив с координатами пути.
 * @param path_length Длина пути.
 */
void maze_save_full_with_path(maze* obj, Position* path, int path_length);

/**
 * @brief Генерирует уникальное имя файла на основе временной метки.
 *
 * @param filename Указатель на строку, в которую будет записано имя файла.
 * @param size Размер строки.
 */
void maze_generate_unique_filename(char* filename, size_t size);

/**
 * @brief Находит путь с помощью обученного агента.
 *
 * @param agent Указатель на структуру агента.
 * @param m Указатель на структуру лабиринта.
 * @param start Начальная позиция.
 * @param goal Целевая позиция.
 */
void find_path_with_agent(QLearningAgent* agent, maze* m, Position start,
                          Position goal);

/**
 * @brief Обучает агента.
 *
 * @param agent Указатель на структуру агента.
 * @param m Указатель на структуру лабиринта.
 * @param goal Целевая позиция.
 * @param episodes Количество эпизодов для обучения.
 */
void train_agent(QLearningAgent* agent, maze* m, Position goal, int episodes);

/**
 * @brief Инициализирует агента.
 *
 * @param agent Указатель на структуру агента.
 * @param rows Количество строк в лабиринте.
 * @param cols Количество столбцов в лабиринте.
 * @param alpha Коэффициент обучения.
 * @param gamma Коэффициент дисконтирования.
 * @param epsilon Вероятность выбора случайного действия (epsilon-greedy).
 */
void initialize_agent(QLearningAgent* agent, int rows, int cols, double alpha,
                      double gamma, double epsilon);

/**
 * @brief Выбирает действие на основе стратегии epsilon-greedy.
 *
 * @param agent Указатель на структуру агента.
 * @param pos Текущая позиция агента.
 * @return Выбранное действие.
 */
Action choose_action(QLearningAgent* agent, Position pos);

/**
 * @brief Обновляет Q-таблицу.
 *
 * @param agent Указатель на структуру агента.
 * @param current Текущая позиция.
 * @param action Выбранное действие.
 * @param next Следующая позиция.
 * @param reward Награда за действие.
 */
void update_q_table(QLearningAgent* agent, Position current, Action action,
                    Position next, double reward);

/**
 * @brief Вычисляет награду.
 *
 * @param pos Текущая позиция.
 * @param goal Целевая позиция.
 * @return Награда.
 */
double get_reward(Position pos, Position goal);

/**
 * @brief Выполняет действие агентом и возвращает новое состояние.
 *
 * @param pos Текущая позиция.
 * @param action Действие.
 * @param m Указатель на структуру лабиринта.
 * @return Новая позиция после выполнения действия.
 */
Position take_action(Position pos, Action action, maze* m);
#endif  // A1_MAZE_MAZE_H