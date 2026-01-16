#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include <raylib.h>

#include "parse_binary.h"
#include "../plot/plot_math.h"

typedef struct {
    Vector2*  data;
    int count;

} DataSource;

DataSource data_source_columns(const BinaryFile* file, int x_column, int y_column);
void data_source_destroy(DataSource* data_source);
void data_apply_offset(DataSource* data_source, Vector2 offset);
void data_scale_y(DataSource* data_source, float scale_y);
void data_cut_left(DataSource* data_source, int index);
void data_cut_right(DataSource* data_source, int index);
void data_flip_x(DataSource* data_source);
void data_find_segments(DataSource* data_source, Bounds bounds);

#endif //DATA_SOURCE_H
