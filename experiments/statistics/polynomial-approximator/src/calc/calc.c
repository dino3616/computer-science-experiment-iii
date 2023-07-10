#include "calc.h"

#include <math.h>
#include <stdlib.h>

#include "log/log.h"

double calc_mean(double *data, size_t data_size) {
  double sum = 0.0;
  for (size_t i = 0; i < data_size; i++) {
    sum += data[i];
  }

  double mean = sum / data_size;

  return mean;
}

int calc_deviations(double *data, size_t data_size, double mean,
                    double *deviations, size_t deviations_size) {
  for (size_t i = 0; i < data_size && i < deviations_size; i++) {
    deviations[i] = data[i] - mean;
  }

  return EXIT_SUCCESS;
}

double calc_variance(double *deviations, size_t deviations_size) {
  double sum = 0.0;
  for (size_t i = 0; i < deviations_size; i++) {
    sum += pow(deviations[i], 2);
  }

  double variance = sum / deviations_size;

  return variance;
}

double calc_std_deviation(double variance) {
  double std_deviation = sqrt(variance);

  return std_deviation;
}

double calc_covariance(double *data1, double data1_mean, double *data2,
                       double data2_mean, size_t data_size) {
  double sum = 0.0;
  for (size_t i = 0; i < data_size; i++) {
    sum += (data1[i] - data1_mean) * (data2[i] - data2_mean);
  }

  double covariance = sum / data_size;

  return covariance;
}

double calc_correlation_cofficient(double covariance,
                                   double data1_std_deviation,
                                   double data2_std_deviation) {
  double correlation_cofficient =
      covariance / (data1_std_deviation * data2_std_deviation);

  return correlation_cofficient;
}

int solve_linear_system(double **matrix, double *vector, double *solution,
                        size_t size) {
  for (size_t k = 0; k < size - 1; k++) {
    if (matrix[k][k] == 0.0) {
      log_debug("Failed to solve linear system; matrix[%d][%d] is zero.", k, k);

      return EXIT_FAILURE;
    }

    for (size_t i = k + 1; i < size; i++) {
      double factor = matrix[i][k] / matrix[k][k];

      for (size_t j = k; j < size; j++) {
        matrix[i][j] -= factor * matrix[k][j];
      }

      vector[i] -= factor * vector[k];
    }
  }

  for (int i = size - 1; i >= 0; i--) {
    if (matrix[i][i] == 0.0) {
      log_debug("Failed to solve linear system; matrix[%d][%d] is zero.", i, i);

      return EXIT_FAILURE;
    }

    double sum = 0.0;
    for (size_t j = i + 1; j < size; j++) {
      sum += matrix[i][j] * solution[j];
    }

    solution[i] = (vector[i] - sum) / matrix[i][i];
  }

  return EXIT_SUCCESS;
}

double calc_r_squared(double *observed, double *predicted, int n) {
  double sum_observed = 0.0;
  for (int i = 0; i < n; i++) {
    sum_observed += observed[i];
  }

  double mean_observed = sum_observed / n;

  double sum_squared_errors = 0.0;
  double sum_squared_total = 0.0;
  for (int i = 0; i < n; i++) {
    double error = observed[i] - predicted[i];
    sum_squared_errors += error * error;

    double total_deviation = observed[i] - mean_observed;
    sum_squared_total += total_deviation * total_deviation;
  }

  double r_squared = 1 - (sum_squared_errors / sum_squared_total);

  return r_squared;
}
