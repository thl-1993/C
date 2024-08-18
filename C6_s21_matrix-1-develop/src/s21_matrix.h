// 0 - OK
// 1 - Ошибка, некорректная матрица
// 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

#ifndef SRC_21_MATRIX_H_
#define SRC_21_MATRIX_H_
#include <math.h>
#include <stdlib.h>

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2
#endif
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

/*Создание матриц (create_matrix)*/
int s21_create_matrix(int rows, int columns, matrix_t *result);

/*Очистка матриц (remove_matrix)*/
void s21_remove_matrix(matrix_t *A);

/*Сравнение матриц (eq_matrix)*/
#define SUCCESS 1
#define FAILURE 0
int s21_eq_matrix(matrix_t *A, matrix_t *B);

/*Сложение (sum_matrix) и вычитание матриц (sub_matrix)*/
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
/*функция вычетания матриц, принцип тот же, что и у сложения кроме одного
 * знака*/
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/*Умножение матрицы на число (mult_number). Умножение двух матриц
 * (mult_matrix)*/
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/*Транспонирование матрицы (transpose)*/
int s21_transpose(matrix_t *A, matrix_t *result);

/*Минор матрицы и матрица алгебраических дополнений (calc_complements)*/
int s21_calc_complements(matrix_t *A, matrix_t *result);

/*Определитель матрицы (determinant)*/
int s21_determinant(matrix_t *A, double *result);

/*Обратная матрица (inverse_matrix)*/
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

////////////////*ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ*////////////////

/*функция для проверки имеют ли две матрицы одинаковый размер*/
int s21_equal_size(matrix_t *A, matrix_t *B);

/*функция для проверки на инфинити или нан*/
int s21_inf_or_nan(matrix_t *A);

/*функция для проверки валидности интовых значений*/
int s21_check_null_matrix(matrix_t *value);
int s21_double_validation(double value);
int s21_matrix_eq_size_for_mult(matrix_t *A, matrix_t *B);
int s21_buffer_result(long double *result, matrix_t *A, matrix_t *B, int row,
                      int column);
int s21_get_minor(matrix_t *value, matrix_t *result, int row, int column);
int s21_determinant_big(matrix_t *A, double *result);
////////////////////////////////////////////////////////////////

#define S21_NAN 0.0 / 0.0L
#define S21_INFINITY 1.0 / 0.0L
#define S21_INFINITY_NEGATIVE -1.0 / 0.0L
#define MAX_DOUBLE 1.7976931348623158e+308
#define MIN_DOUBLE -1.7976931348623158e+308
