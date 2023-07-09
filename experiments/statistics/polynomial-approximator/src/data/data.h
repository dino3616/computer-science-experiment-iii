#ifndef DATA_DATA_H
#define DATA_DATA_H

#include <stdio.h>

typedef struct Data {
  float *data;
  size_t data_size;
} Data_t;

extern int read_data(FILE *fp, Data_t *data_list,
                               size_t data_list_size);
extern int read_data_from_file(char *file_path, Data_t *data_list,
                        size_t data_list_size);

#endif
