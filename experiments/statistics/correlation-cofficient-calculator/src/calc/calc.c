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
