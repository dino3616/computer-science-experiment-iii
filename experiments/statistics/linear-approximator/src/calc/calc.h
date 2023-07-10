#ifndef CALC_CALC_H
#define CALC_CALC_H

#include <stddef.h>

extern double calc_mean(double *data, size_t data_size);
extern int calc_deviations(double *data, size_t data_size, double mean,
                           double *deviations, size_t deviations_size);
extern double calc_variance(double *deviation, size_t deviation_size);
extern double calc_std_deviation(double variance);
extern double calc_covariance(double *data1, double data1_mean, double *data2,
                             double data2_mean, size_t data_size);
extern double calc_correlation_cofficient(double covariance,
                                         double data1_std_deviation,
                                         double data2_std_deviation);
extern double calc_r_squared(double *observed, double *predicted, int n);

#endif
