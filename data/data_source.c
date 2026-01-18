#include "data_source.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../math/line.h"
#include "../plot/plot_math.h"
#include "../plot/components/DataPlot.h"
#include "../plot/components/Polynomial.h"

void DrawCurveLinear(CurveLinear curve_linear, Bounds bounds);


DataSource data_source_columns(const BinaryFile* file, const int x_column, const int y_column) {
    const int count = file->header.row_count;
    const DataSource data_source = {
        .count = count,
        .data = malloc(sizeof(Vector2) * count)
    };

    const bool is_reverse = file->columns[x_column].data[0] > file->columns[x_column].data[count - 1];

    for (int i = 0; i < count; ++i) {
        const int data_index = is_reverse ? count - i - 1 : i;
        data_source.data[i].x = file->columns[x_column].data[data_index];
        data_source.data[i].y = file->columns[y_column].data[data_index];
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

void data_flip_x(DataSource* data_source) {
    const int mid_i = data_source->count / 2;
    for (int i = 0; i < mid_i; ++i) {
        const int j = data_source->count - i - 1;
        const Vector2 tmp = data_source->data[i];
        data_source->data[i] = data_source->data[j];
        data_source->data[j] = tmp;
        data_source->data[i].x = -data_source->data[i].x;
        data_source->data[j].x = -data_source->data[j].x;
    }
    if (data_source->count & 1) {
        data_source->data[mid_i].x = -data_source->data[mid_i].x;
    }
}

void data_convert(const DataSource* data_source, const float x_factor, const float y_factor) {
    for (int i = 0; i < data_source->count; ++i) {
        data_source->data[i].x *= x_factor;
        data_source->data[i].y *= y_factor;
    }
}

char* axis_label_trim(const BinaryFile* binary_file, const int column) {
    char* label = binary_file->columns[column].label;
    char* spaces = strchr(label, ' ');
    if (!spaces) return label;

    char* unit = spaces;
    while (*unit == ' ' && *unit) unit++;
    if (!*unit) {
        *spaces = 0;
        return label;
    }

    char* second_spaces = strchr(unit, ' ');
    if (!second_spaces) return label;

    second_spaces[0] = ']';
    second_spaces[1] = 0;
    strcpy(spaces + 2, unit);
    spaces[1] = '[';
    return label;
}
