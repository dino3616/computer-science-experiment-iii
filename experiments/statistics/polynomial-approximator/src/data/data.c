#include "data.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log/log.h"

int read_data(FILE *fp, Data_t *data_list, size_t data_list_size) {
  size_t data_size = 0;
  if (fscanf(fp, "%ld", (long int *)&data_size) != 1) {
    int error_number = errno;
    log_error("Faild to read data_size from file. cause: '%s'",
              strerror(error_number));

    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < data_list_size; i++) {
    data_list[i].data = malloc(sizeof(float) * data_size);
    if (data_list[i].data == NULL) {
      int error_number = errno;
      log_error("Failed to allocate memory for Data::data. cause: '%s'",
                strerror(error_number));

      return EXIT_FAILURE;
    }

    data_list[i].data_size = data_size;
  }

  for (size_t i = 0; i < data_size; i++) {
    for (size_t j = 0; j < data_list_size; j++) {
      float datum;
      if (fscanf(fp, "%f", &datum) != 1) {
        int error_number = errno;
        log_error("Faild to read datum from file. cause: '%s'",
                  strerror(error_number));

        return EXIT_FAILURE;
      }

      data_list[j].data[i] = datum;
    }

    while (fgetc(fp) != '\n') {
    }
  }

  return EXIT_SUCCESS;
}

int read_data_from_file(char *file_path, Data_t *data_list,
                        size_t data_list_size) {
  FILE *data_file = fopen(file_path, "r");
  if (data_file == NULL) {
    int error_number = errno;
    log_error("Failed to open '%s'. cause: '%s'", file_path,
              strerror(error_number));

    return EXIT_FAILURE;
  }

  if (read_data(data_file, data_list, data_list_size) != EXIT_SUCCESS) {
    log_error("Failed to read data from file.");

    return EXIT_FAILURE;
  }

  fclose(data_file);

  return EXIT_SUCCESS;
}
