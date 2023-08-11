#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log/log.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    log_error(
        "Argument variable too short; expected to receive two or more, "
        "received one.\n"
        "format: <bin> [path to data file] [wanted data column]");

    return EXIT_FAILURE;
  }

  const char *file_path = argv[1];
  int wanted_column = atoi(argv[2]);

  FILE *file = fopen(file_path, "r");
  if (file == NULL) {
    log_error("Failed to open the file.");
    return EXIT_FAILURE;
  }

  int data_size;
  fscanf(file, "%d", &data_size);

  for (int i = 0; i < data_size; i++) {
    float x, y;
    if (fscanf(file, "%f %f", &x, &y) != 2) {
      log_error("Error reading data from the file.");
      fclose(file);
      return EXIT_FAILURE;
    }

    if (wanted_column == 1) {
      printf("%f\n", x);
    } else if (wanted_column == 2) {
      printf("%f\n", y);
    } else {
      log_error("Invalid column number.");
      fclose(file);
      return EXIT_FAILURE;
    }
  }

  fclose(file);
  return EXIT_SUCCESS;
}
