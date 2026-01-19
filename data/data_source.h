#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include <raylib.h>

#include "parse_binary.h"

typedef struct {
    Vector2* data;
    Vector2* base;
    int count;

} DataSource;

DataSource data_source_columns(const BinaryFile* file, int x_column, int y_column);
void data_source_destroy(DataSource* data_source);
char* axis_label_trim(const BinaryFile* binary_file, int column);

#endif //DATA_SOURCE_H
