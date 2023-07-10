#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc/calc.h"
#include "data/data.h"
#include "log/log.h"

#define DATA_LIST_SIZE 2

int calc_regression_curve(double *data1, size_t data1_size, double *data2,
                          size_t data2_size, size_t data_size);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    log_error(
        "Argument variable too short; expected to receive two or more, "
        "received one.\n"
        "format: <bin> [path to data file]");

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

  if (calc_regression_curve(data_list[0].data, data_list[0].data_size,
                            data_list[1].data, data_list[1].data_size,
                            data_list->data_size) != EXIT_SUCCESS) {
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
                          size_t data2_size, size_t data_size) {
  double data1_mean = calc_mean(data1, data1_size);
  double data2_mean = calc_mean(data2, data2_size);

  double *data1_deviations = (double *)malloc(sizeof(double) * data1_size);
  if (data1_deviations == NULL) {
    log_error("Failed to allocate memory for data1_deviations.");

    return EXIT_FAILURE;
  }
  double *data2_deviations = (double *)malloc(sizeof(double) * data2_size);
  if (data2_deviations == NULL) {
    log_error("Failed to allocate memory for data2_deviations.");

    return EXIT_FAILURE;
  }
  calc_deviations(data1, data1_size, data1_mean, data1_deviations, data1_size);
  calc_deviations(data2, data2_size, data2_mean, data2_deviations, data2_size);

  double data1_variance = calc_variance(data1_deviations, data1_size);

  double covariance =
      calc_covariance(data1, data1_mean, data2, data2_mean, data_size);

  double regression_coefficient = covariance / data1_variance;

  double intercept = data2_mean - regression_coefficient * data1_mean;

  log_info("regression curve: y = %lfx + (%lf)", regression_coefficient,
           intercept);

  double *predicted = malloc(sizeof(double) * data_size);
  for (size_t i = 0; i < data_size; i++) {
    predicted[i] = regression_coefficient * data1[i] + intercept;
  }

  double r_squared = calc_r_squared(data2, predicted, data_size);

  log_info("r-squared: R2 = %lf", r_squared);

  free(data1_deviations);
  free(data2_deviations);
  free(predicted);

  return EXIT_SUCCESS;
}
