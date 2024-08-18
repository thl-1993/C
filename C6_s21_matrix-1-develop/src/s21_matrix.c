#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (result != NULL && rows > 0 && columns > 0) {
    res = OK;
    result->rows = rows;
    result->columns = columns;
  }
  if (res == OK) {
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (result->matrix == NULL) {
      res = INCORRECT_MATRIX;
    }
    if (res == OK) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)malloc(columns * sizeof(double));
        if (result->matrix[i] == NULL) {
          res = INCORRECT_MATRIX;
        } else {
          result->rows = rows;
          result->columns = columns;
          for (int j = 0; j < columns; j++) {
            result->matrix[i][j] = OK;
          }
        }
      }
    }
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    for (int row = 0; row < A->rows; row++) {
      free(A->matrix[row]);
    }
    free(A->matrix);
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (s21_check_null_matrix(A) && s21_check_null_matrix(B) && result != NULL)
    res = CALCULATION_ERROR;
  if (s21_equal_size(A, B)) {
    res = OK;
  }
  if (res == OK) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        if (s21_double_validation(A->matrix[i][j]) &&
            s21_double_validation(B->matrix[i][j])) {
          double buffer = A->matrix[i][j] + B->matrix[i][j];
          if (buffer <= MAX_DOUBLE) {
            result->matrix[i][j] = (double)buffer;
          } else {
            res = CALCULATION_ERROR;
          }
        } else {
          res = CALCULATION_ERROR;
        }
      }
      if (res == CALCULATION_ERROR) break;
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (s21_check_null_matrix(A) && s21_check_null_matrix(B) && result != NULL)
    res = CALCULATION_ERROR;
  if (s21_equal_size(A, B)) res = OK;
  if (res == OK) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        if (s21_double_validation(A->matrix[i][j]) &&
            s21_double_validation(B->matrix[i][j])) {
          long double buffer = A->matrix[i][j] - B->matrix[i][j];
          if (buffer >= MIN_DOUBLE) {
            result->matrix[i][j] = (double)buffer;
          } else {
            res = CALCULATION_ERROR;
          }
        } else {
          res = CALCULATION_ERROR;
        }
      }
      if (res == CALCULATION_ERROR) break;
    }
  }
  return res;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if ((s21_check_null_matrix(A) && s21_check_null_matrix(B)) &&
      (s21_equal_size(A, B))) {
    for (int i = 0; i < A->rows && res; i++) {
      for (int j = 0; j < A->columns && res; j++) {
        if (fabs((A->matrix[i][j]) - (B->matrix[i][j])) > 1e-7) {
          res = FAILURE;
        }
      }
    }
  } else {
    res = FAILURE;
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (s21_check_null_matrix(A) && result != NULL) {
    res = CALCULATION_ERROR;
  }
  if (s21_double_validation(number) && res == CALCULATION_ERROR) {
    res = OK;
  }
  if (res == OK) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        if (s21_double_validation(A->matrix[i][j])) {
          double buffer = A->matrix[i][j] * number;
          if (buffer >= MIN_DOUBLE && buffer <= MAX_DOUBLE) {
            result->matrix[i][j] = (double)buffer;
          } else {
            res = CALCULATION_ERROR;
          }
        } else {
          res = CALCULATION_ERROR;
        }
      }
      if (res == CALCULATION_ERROR) {
        break;
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (s21_check_null_matrix(A) && s21_check_null_matrix(B) && result != NULL)
    res = CALCULATION_ERROR;
  if (s21_matrix_eq_size_for_mult(A, B)) res = OK;
  if (res == OK) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        long double buffer = 0;
        if (s21_buffer_result(&buffer, A, B, i, j)) {
          result->matrix[i][j] = (double)buffer;
        } else {
          res = CALCULATION_ERROR;
        }
      }
      if (res == CALCULATION_ERROR) break;
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (s21_check_null_matrix(A) && result != NULL) {
    res = OK;
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (s21_double_validation(A->matrix[i][j])) {
          result->matrix[j][i] = A->matrix[i][j];
        } else {
          res = CALCULATION_ERROR;
        }
      }
    }
    if (res == CALCULATION_ERROR) s21_remove_matrix(result);
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (s21_check_null_matrix(A) && result != NULL) {
    res = CALCULATION_ERROR;
  }
  if (res == CALCULATION_ERROR && A->rows == A->columns && A->rows > 1) {
    res = OK;
    s21_create_matrix(A->rows, A->columns, result);
    for (int row = 0; row < A->rows; row++) {
      if (res == CALCULATION_ERROR) break;
      for (int column = 0; column < A->columns; column++) {
        if (res == CALCULATION_ERROR) break;
        int sign = pow(-1.0, (double)(row + column));
        matrix_t minor;
        s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
        if (s21_get_minor(A, &minor, row, column)) {
          double det;
          s21_determinant(&minor, &det);
          result->matrix[row][column] = det * sign;
        } else
          res = CALCULATION_ERROR;
        s21_remove_matrix(&minor);
      }
    }
    if (res == CALCULATION_ERROR) s21_remove_matrix(result);
  } else if (res == CALCULATION_ERROR && A->rows == A->columns &&
             A->rows == 1 && s21_double_validation(A->matrix[0][0])) {
    res = OK;
    s21_create_matrix(A->rows, A->columns, result);
    result->matrix[0][0] = A->matrix[0][0];
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = INCORRECT_MATRIX;
  if (s21_check_null_matrix(A) && result != NULL) {
    res = CALCULATION_ERROR;
  }
  if (res == CALCULATION_ERROR && A->rows == A->columns) {
    res = OK;
    if (A->rows == 1) {
      if (s21_double_validation(A->matrix[0][0])) {
        *result = A->matrix[0][0];
      } else {
        res = CALCULATION_ERROR;
      }
    } else if (A->rows == 2) {
      if (s21_double_validation(A->matrix[0][0]) &&
          s21_double_validation(A->matrix[0][1]) &&
          s21_double_validation(A->matrix[1][0]) &&
          s21_double_validation(A->matrix[1][1])) {
        double buffer = ((A->matrix[0][0] * A->matrix[1][1]) -
                         (A->matrix[0][1] * A->matrix[1][0]));
        if (buffer >= MIN_DOUBLE && buffer <= MAX_DOUBLE) *result = buffer;
      } else
        res = CALCULATION_ERROR;
    } else {
      res = s21_determinant_big(A, result);
    }
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  double det = 0.;
  if (!s21_check_null_matrix(A) && !s21_check_null_matrix(result)) {
    res = CALCULATION_ERROR;
  }
  if (A->rows == A->columns && !s21_inf_or_nan(A)) {
    res = OK;
  }
  if (A->rows > 1 && A->columns > 1 && res == OK) {
    s21_determinant(A, &det);

    if (det) {
      matrix_t complements = {0}, transpose = {0};

      s21_calc_complements(A, &complements);
      s21_transpose(&complements, &transpose);

      det = 1 / det;
      s21_mult_number(&transpose, det, result);
      s21_remove_matrix(&complements);
      s21_remove_matrix(&transpose);
    } else {
      res = CALCULATION_ERROR;
    }
  } else if (A->matrix[0][0] != 0 && A->rows == 1 && A->columns == 1 &&
             res == OK) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = 1 / A->matrix[0][0];
  } else {
    res = CALCULATION_ERROR;
  }
  return res;
}
//////////////////////////////////////////////////////////////////////////////

/*функция для проверки на инфинити или нан*/
int s21_inf_or_nan(matrix_t *A) {
  int res = OK;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (isinf(A->matrix[i][j]) || isnan(A->matrix[i][j])) {
        res = CALCULATION_ERROR;
        i = A->columns;
        j = A->rows;
      }
    }
  }
  return res;
}

////////////////////////
/*функция для проверки матрицы на NULL или имеет недопустимые размеры*/
int s21_check_null_matrix(matrix_t *value) {
  int res = SUCCESS;
  if (value == NULL || value->matrix == NULL) {
    res = FAILURE;
  } else if (value->matrix == NULL || value->rows <= 0 || value->columns <= 0) {
    res = FAILURE;
  }
  return res;
}

/*функция для сравнения размеров двух матриц */
int s21_equal_size(matrix_t *A, matrix_t *B) {
  int res = FAILURE;
  if (A->rows == B->rows && A->columns == B->columns) res = SUCCESS;
  return res;
}

int s21_double_validation(double value) {
  int res = SUCCESS;
  if (value == S21_INFINITY || value == S21_INFINITY_NEGATIVE || isnan(value)) {
    res = FAILURE;
  }
  return res;
}

int s21_matrix_eq_size_for_mult(matrix_t *A, matrix_t *B) {
  int res = FAILURE;
  if (s21_check_null_matrix(A) && s21_check_null_matrix(B)) {
    res = SUCCESS;
  }
  if (res && A->rows != B->columns) {
    res = FAILURE;
  }
  if (res && A->columns != B->rows) {
    res = FAILURE;
  }
  return res;
}

int s21_buffer_result(long double *result, matrix_t *A, matrix_t *B, int row,
                      int column) {
  int res = SUCCESS;
  for (int i = 0; i < A->columns; i++) {
    if (s21_double_validation(A->matrix[row][i]) &&
        s21_double_validation(B->matrix[i][column])) {
      *result += (long double)(A->matrix[row][i] * B->matrix[i][column]);
    } else {
      res = FAILURE;
    }
    if (*result <= MIN_DOUBLE || *result >= MAX_DOUBLE) {
      res = FAILURE;
    }
    if (res == FAILURE) {
      break;
    }
  }
  return res;
}

int s21_get_minor(matrix_t *value, matrix_t *result, int row, int column) {
  int res = SUCCESS;
  int r_r = 0;
  int c_r = 0;
  for (int r = 0; r < value->rows; r++) {
    if (r != row) {
      for (int c = 0; c < value->columns; c++) {
        if (c != column) {
          if (s21_double_validation(value->matrix[r][c])) {
            result->matrix[r_r][c_r] = value->matrix[r][c];
            c_r++;
          } else
            res = FAILURE;
        }
      }
      c_r = 0;
      r_r++;
    }
  }
  return res;
}

int s21_determinant_big(matrix_t *A, double *result) {
  int res = OK;
  double result_buffer = 0;
  for (int column = 0; column < A->columns; column++) {
    double sign = pow(-1.0, (double)column);
    matrix_t minor;
    s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
    if (s21_get_minor(A, &minor, 0, column)) {
      double minor_determinant;
      s21_determinant(&minor, &minor_determinant);
      result_buffer += minor_determinant * sign * A->matrix[0][column];
    } else
      res = CALCULATION_ERROR;
    s21_remove_matrix(&minor);
    if (res != OK) break;
  }
  if (res == OK) *result = result_buffer;
  return res;
}
