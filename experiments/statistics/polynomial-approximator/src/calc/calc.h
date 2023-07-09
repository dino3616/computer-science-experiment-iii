#ifndef CALC_CALC_H
#define CALC_CALC_H

#include <stddef.h>

extern float calc_mean(float *data, size_t data_size);
extern int calc_deviations(float *data, size_t data_size, float mean,
                           float *deviations, size_t deviations_size);
extern float calc_variance(float *deviation, size_t deviation_size);
extern float calc_std_deviation(float variance);
extern float calc_covariance(float *data1, float data1_mean, float *data2,
                             float data2_mean, size_t data_size);
extern float calc_correlation_cofficient(float covariance,
                                         float data1_std_deviation,
                                         float data2_std_deviation);
extern int solve_linear_system(float **matrix, float *vector, float *solution,
                               size_t size);
extern float calc_r_squared(float *observed, float *predicted, int n);

#endif
