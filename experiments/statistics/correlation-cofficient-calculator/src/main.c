#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc/calc.h"
#include "data/data.h"
#include "log/log.h"

#define DATA_LIST_SIZE 2

int main(int argc, char *argv[]) {
  if (argc < 2) {
    log_error(
        "Argument variable too short; expected to receive two or more, "
        "received one.\nformat: <bin> [path to data file]");

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

  float *correlation_cofficient = (float *)malloc(sizeof(float));
  if (correlation_cofficient == NULL) {
    int error_number = errno;
    log_error(
        "Failed to allocate memory for correlation_cofficient. cause: '%s'",
        strerror(error_number));

    return EXIT_FAILURE;
  }

  if (calc_correlation_cofficient_from_data(
          data_list[0].data, data_list[0].data_size, data_list[1].data,
          data_list[1].data_size, data_list->data_size,
          correlation_cofficient) == NULL) {
    log_error("Failed to calculate correlation cofficient from data.");

    return EXIT_FAILURE;
  }

  log_info("correlation cofficient: %f", *correlation_cofficient);

  free(correlation_cofficient);

  for (size_t i = 0; i < DATA_LIST_SIZE; i++) {
    free(data_list[i].data);
  }
  free(data_list);

  return EXIT_SUCCESS;
}
