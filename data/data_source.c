#include "data_source.h"

#include <stdlib.h>
#include <stdint.h>

DataSource data_source_columns(const BinaryFile* file, const int x_column, const int y_column, const float scale_x) {
    const int count = file->header.row_count;
    const DataSource data_source = {
        .count = count,
        .data = malloc(sizeof(Vector2) * count)
    };
    for (int i = 0; i < count; ++i) {
        data_source.data[i].x = file->columns[x_column].data[i] * scale_x;
        data_source.data[i].y = file->columns[y_column].data[i];
    }
    return data_source;
}

void data_source_destroy(DataSource* data_source) {
    free(data_source->data);
}
