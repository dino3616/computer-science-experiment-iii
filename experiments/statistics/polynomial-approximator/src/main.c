#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc/calc.h"
#include "data/data.h"
#include "log/log.h"

#define DATA_LIST_SIZE 2

int polynomial_regression(double *data1, size_t data1_size, double *data2,
                          double *coefficients, size_t degree);
int calc_regression_curve(double *data1, size_t data1_size, double *data2,
                          size_t data_size, int degree);

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    log_error(
        "Argument variable too short; expected to receive two or more, "
        "received one.\n"
        "format: <bin> [path to data file] [degree of polynomial]");

    return EXIT_FAILURE;
  }

  Data_t *data_list = (Data_t *)malloc(sizeof(Data_t) * DATA_LIST_SIZE);
  if (data_list == NULL) {
    int error_number = errno;
    log_error("Failed to allocate memory for data. cause: '%s'",
              strerror(error_number));

    return EXIT_FAILURE;
  }

  if (read_data_from_file(argv[1], data_list, DATA_LIST_SIZE) != EXIT_SUCCESS) {
    log_error("Failed to read data from file.");

    return EXIT_FAILURE;
  }

  size_t degree = atoi(argv[2]);
  if (calc_regression_curve(data_list[0].data, data_list[0].data_size,
                            data_list[1].data, data_list->data_size,
                            degree) != EXIT_SUCCESS) {
    log_error("Failed to calculate regression curve from data.");

    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < DATA_LIST_SIZE; i++) {
    free(data_list[i].data);
  }
  free(data_list);

  return EXIT_SUCCESS;
}

int calc_regression_curve(double *data1, size_t data1_size, double *data2,
                          size_t data_size, int degree) {
  double *coefficients = (double *)malloc(sizeof(double) * (degree + 1));
  if (coefficients == NULL) {
    log_error("Failed to allocate memory for coefficients.");

    return EXIT_FAILURE;
  }

  if (polynomial_regression(data1, data1_size, data2, coefficients, degree) !=
      EXIT_SUCCESS) {
    log_error("Failed to calculate polynomial regression.");

    free(coefficients);
    return EXIT_FAILURE;
  }

  log_info("Polynomial regression curve:");
  log_info("y = %lf", coefficients[0]);
  for (int i = 1; i <= degree; i++) {
    log_info(" + (%lf * x^%d)", coefficients[i], i);
  }

  double *predicted = malloc(sizeof(double) * data_size);
  if (predicted == NULL) {
    log_error("Failed to allocate memory for predicted values.");

    free(coefficients);

    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < data_size; i++) {
    double x = data1[i];
    double y = coefficients[0];

    for (int j = 1; j <= degree; j++) {
      y += coefficients[j] * pow(x, j);
    }

    predicted[i] = y;
  }

  double r_squared = calc_r_squared(data2, predicted, data_size);

  log_info("r-squared: R2 = %lf", r_squared);

  free(coefficients);
  free(predicted);

  return EXIT_SUCCESS;
}

int polynomial_regression(double *data1, size_t data1_size, double *data2,
                          double *coefficients, size_t degree) {
  double **matrix = (double **)malloc(sizeof(double *) * (degree + 1));
  if (matrix == NULL) {
    log_error("Failed to allocate memory for matrix rows.");

    return EXIT_FAILURE;
  }

  for (size_t i = 0; i <= degree; i++) {
    matrix[i] = (double *)malloc(sizeof(double) * (degree + 1));
    if (matrix[i] == NULL) {
      log_error("Failed to allocate memory for matrix columns.");

      for (size_t j = 0; j < i; j++) {
        free(matrix[j]);
      }
      free(matrix);

      return EXIT_FAILURE;
    }

    for (size_t j = 0; j <= degree; j++) {
      matrix[i][j] = 0.0;
    }
  }

  double *vector = (double *)malloc(sizeof(double) * (degree + 1));
  if (vector == NULL) {
    log_error("Failed to allocate memory for vector.");

    for (size_t i = 0; i <= degree; i++) {
      free(matrix[i]);
    }
    free(matrix);

    return EXIT_FAILURE;
  }

  for (size_t i = 0; i <= degree; i++) {
    vector[i] = 0.0;
  }

  for (size_t i = 0; i < data1_size; i++) {
    double x = data1[i];
    double y = data2[i];

    for (size_t j = 0; j <= degree; j++) {
      for (size_t k = 0; k <= degree; k++) {
        matrix[j][k] += pow(x, j + k);
      }

      vector[j] += y * pow(x, j);
    }
  }

  if (solve_linear_system(matrix, vector, coefficients, degree + 1) !=
      EXIT_SUCCESS) {
    log_error("Failed to solve linear system.");

    for (size_t i = 0; i <= degree; i++) {
      free(matrix[i]);
    }
    free(matrix);
    free(vector);

    return EXIT_FAILURE;
  }

  for (size_t i = 0; i <= degree; i++) {
    free(matrix[i]);
  }
  free(matrix);
  free(vector);

  return EXIT_SUCCESS;
}
