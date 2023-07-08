#include "calc.h"

#include <math.h>
#include <stdlib.h>

#include "log/log.h"

float calc_mean(float* data, size_t data_size) {
  float sum = 0;
  for (size_t i = 0; i < data_size; i++) {
    sum += data[i];
  }

  float mean = sum / data_size;

  return mean;
}

int calc_deviations(float* data, size_t data_size, float mean,
                    float* deviations, size_t deviations_size) {
  for (size_t i = 0; i < data_size && i < deviations_size; i++) {
    deviations[i] = data[i] - mean;
  }

  return EXIT_SUCCESS;
}

float calc_variance(float* deviations, size_t deviations_size) {
  float sum = 0;
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

float calc_covariance(float* data1, float data1_mean, float* data2,
                      float data2_mean, size_t data_size) {
  float sum = 0;
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

float* calc_correlation_cofficient_from_data(float* data1, size_t data1_size,
                                             float* data2, size_t data2_size,
                                             size_t data_size,
                                             float* correlation_cofficient) {
  float data1_mean = calc_mean(data1, data1_size);
  float data2_mean = calc_mean(data2, data2_size);

  log_debug("data1_mean: %f", data1_mean);
  log_debug("data2_mean: %f", data2_mean);

  float* data1_deviations = (float*)malloc(sizeof(float) * data1_size);
  if (data1_deviations == NULL) {
    log_error("Failed to allocate memory for data1_deviations.");

    return NULL;
  }
  float* data2_deviations = (float*)malloc(sizeof(float) * data2_size);
  if (data2_deviations == NULL) {
    log_error("Failed to allocate memory for data2_deviations.");

    return NULL;
  }
  calc_deviations(data1, data1_size, data1_mean, data1_deviations, data1_size);
  calc_deviations(data2, data2_size, data2_mean, data2_deviations, data2_size);

  for (size_t i = 0; i < data1_size; i++) {
    log_debug("data1_deviations[%zu]: %f", i, data1_deviations[i]);
  }
  for (size_t i = 0; i < data2_size; i++) {
    log_debug("data2_deviations[%zu]: %f", i, data2_deviations[i]);
  }

  float data1_variance = calc_variance(data1_deviations, data1_size);
  float data2_variance = calc_variance(data2_deviations, data2_size);

  log_debug("data1_variance: %f", data1_variance);
  log_debug("data2_variance: %f", data2_variance);

  float data1_std_deviation = calc_std_deviation(data1_variance);
  float data2_std_deviation = calc_std_deviation(data2_variance);

  log_debug("data1_std_deviation: %f", data1_std_deviation);
  log_debug("data2_std_deviation: %f", data2_std_deviation);

  float covariance =
      calc_covariance(data1, data1_mean, data2, data2_mean, data_size);

  log_debug("covariance: %f", covariance);

  *correlation_cofficient = calc_correlation_cofficient(
      covariance, data1_std_deviation, data2_std_deviation);

  log_debug("correlation_cofficient: %f", *correlation_cofficient);

  free(data1_deviations);
  free(data2_deviations);

  return correlation_cofficient;
}
