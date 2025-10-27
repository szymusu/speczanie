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

void data_apply_offset(DataSource* data_source, const Vector2 offset) {
    for (int i = 0; i < data_source->count; ++i) {
        data_source->data[i].x += offset.x;
        data_source->data[i].y -= offset.y;
    }
}

void data_scale_y(DataSource* data_source, const float scale_y) {
    for (int i = 0; i < data_source->count; ++i) {
        data_source->data[i].y *= scale_y;
    }
}

void data_cut_left(DataSource* data_source, const int index) {
    data_source->count -= index;
    for (int i = 0; i < data_source->count; ++i) {
        data_source->data[i] = data_source->data[i + index];
    }
}

void data_cut_right(DataSource* data_source, const int index) {
    if (index + 1 >= data_source->count) return;
    data_source->count = index + 1;
}
