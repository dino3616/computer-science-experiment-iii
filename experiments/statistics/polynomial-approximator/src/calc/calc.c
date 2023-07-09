#include "calc.h"

#include <math.h>
#include <stdlib.h>

#include "log/log.h"

float calc_mean(float *data, size_t data_size) {
  float sum = 0.0;
  for (size_t i = 0; i < data_size; i++) {
    sum += data[i];
  }

  float mean = sum / data_size;

  return mean;
}

int calc_deviations(float *data, size_t data_size, float mean,
                    float *deviations, size_t deviations_size) {
  for (size_t i = 0; i < data_size && i < deviations_size; i++) {
    deviations[i] = data[i] - mean;
  }

  return EXIT_SUCCESS;
}

float calc_variance(float *deviations, size_t deviations_size) {
  float sum = 0.0;
  for (size_t i = 0; i < deviations_size; i++) {
    sum += pow(deviations[i], 2);
  }

  float variance = sum / deviations_size;

  return variance;
}

float calc_std_deviation(float variance) {
  float std_deviation = sqrt(variance);

  return std_deviation;
}

float calc_covariance(float *data1, float data1_mean, float *data2,
                      float data2_mean, size_t data_size) {
  float sum = 0.0;
  for (size_t i = 0; i < data_size; i++) {
    sum += (data1[i] - data1_mean) * (data2[i] - data2_mean);
  }

  float covariance = sum / data_size;

  return covariance;
}

float calc_correlation_cofficient(float covariance, float data1_std_deviation,
                                  float data2_std_deviation) {
  float correlation_cofficient =
      covariance / (data1_std_deviation * data2_std_deviation);

  return correlation_cofficient;
}

int solve_linear_system(float **matrix, float *vector, float *solution,
                        size_t size) {
  for (size_t k = 0; k < size - 1; k++) {
    if (matrix[k][k] == 0.0) {
      log_debug("Failed to solve linear system; matrix[%d][%d] is zero.", k, k);

      return EXIT_FAILURE;
    }

    for (size_t i = k + 1; i < size; i++) {
      float factor = matrix[i][k] / matrix[k][k];

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

    float sum = 0.0;
    for (size_t j = i + 1; j < size; j++) {
      sum += matrix[i][j] * solution[j];
    }

    solution[i] = (vector[i] - sum) / matrix[i][i];
  }

  return EXIT_SUCCESS;
}

float calc_r_squared(float *observed, float *predicted, int n) {
  float sum_observed = 0.0;
  for (int i = 0; i < n; i++) {
    sum_observed += observed[i];
  }

  float mean_observed = sum_observed / n;

  float sum_squared_errors = 0.0;
  float sum_squared_total = 0.0;
  for (int i = 0; i < n; i++) {
    float error = observed[i] - predicted[i];
    sum_squared_errors += error * error;

    float total_deviation = observed[i] - mean_observed;
    sum_squared_total += total_deviation * total_deviation;
  }

  float r_squared = 1 - (sum_squared_errors / sum_squared_total);

  return r_squared;
}
