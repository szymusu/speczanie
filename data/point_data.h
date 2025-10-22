#ifndef POINT_DATA_H
#define POINT_DATA_H

#include <raylib.h>

#include "data_source.h"
#include "../plot/plot_math.h"

typedef struct {
    int count;
    int start;
} VisiblePointsInfo;

VisiblePointsInfo compute_visible_points(DataSource data_source, Vector2* point_buffer, Bounds bounds, Vector2 offset);

#endif //POINT_DATA_H
