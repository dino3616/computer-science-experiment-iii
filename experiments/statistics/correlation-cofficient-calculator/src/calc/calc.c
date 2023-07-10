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

double calc_correlation_cofficient(double covariance, double data1_std_deviation,
                                  double data2_std_deviation) {
  double correlation_cofficient =
      covariance / (data1_std_deviation * data2_std_deviation);

  return correlation_cofficient;
}
