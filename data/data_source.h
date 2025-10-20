#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include <raylib.h>

#include "parse_binary.h"

typedef struct {
    Vector2*  data;
    int count;

} DataSource;

DataSource data_source_columns(const BinaryFile* file, int x_column, int y_column, float scale_x);
void data_source_destroy(DataSource* data_source);

#endif //DATA_SOURCE_H
