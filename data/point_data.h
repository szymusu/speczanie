#ifndef POINT_DATA_H
#define POINT_DATA_H

#include <raylib.h>

#include "data_source.h"
#include "../plot/plot_math.h"

typedef struct {
    int count;
    int start;
} VisibleWindow;

VisibleWindow compute_visible_points(DataSource data_source, Vector2* point_buffer, Bounds bounds);
VisibleWindow compute_visible_points_offset(DataSource data_source, Vector2* point_buffer, Bounds bounds, Vector2 offset);
bool is_in_view(int point_index, VisibleWindow visible);

#endif //POINT_DATA_H
