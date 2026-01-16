#include "data_source.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../math/line.h"
#include "../plot/plot_math.h"

DataSource data_source_columns(const BinaryFile* file, const int x_column, const int y_column) {
    const int count = file->header.row_count;
    const DataSource data_source = {
        .count = count,
        .data = malloc(sizeof(Vector2) * count)
    };
    for (int i = 0; i < count; ++i) {
        data_source.data[i].x = file->columns[x_column].data[i];
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

enum Segment {
    SEGMENT_STATIC,
    SEGMENT_CHAOS,
    SEGMENT_LINEAR,
    SEGMENT_NONLINEAR,
};

void data_find_segments(DataSource* data_source, const Bounds bounds) {
    enum Segment segment = SEGMENT_STATIC;
    if (data_source->count < 20) {
        printf("Data source too small: %d\n", data_source->count);
        return;
    }
    int static_chaos_border = -1;
    int linear_nonlinear_border = -1;
    for (int i = 1; i < data_source->count; ++i) {
        if (fabsf(data_source->data[i].y - data_source->data[i - 1].y) > .05f) {
            static_chaos_border = i - 1;
            break;
        }
    }
    if (static_chaos_border == -1) {
        puts("static_chaos_border NOT FOUND");
        return;
    }
    // printf("static_chaos_border index: %d, x: %f\n", static_chaos_border, data_source->data[static_chaos_border].x);
    DrawCircleV(transform_v_to_pixel(data_source->data[static_chaos_border], bounds), 10, YELLOW);

    // linia
    int chaos_linear_border = static_chaos_border + 1;
    const int falling_curve_middle = (static_chaos_border + data_source->count - 1) / 2;
    // float last_slope = get_line_slope(data_source->data[falling_curve_middle], data_source->data[falling_curve_middle - 1]);
    float min_slope = 0;
    for (int i = falling_curve_middle - 1; i > static_chaos_border + 2; --i) {
        DrawCircleV(transform_v_to_pixel(data_source->data[i], bounds), 3, GREEN);

        const float slope = get_line_slope(data_source->data[i], data_source->data[i - 1]);
        if (slope < min_slope) {
            chaos_linear_border = i - 1;
            min_slope = slope;
        }
    }
    DrawCircleV(transform_v_to_pixel(data_source->data[chaos_linear_border], bounds), 10, ORANGE);

    linear_nonlinear_border = chaos_linear_border + 2;

    DrawCircleV(transform_v_to_pixel(data_source->data[linear_nonlinear_border], bounds), 10, RED);
}
