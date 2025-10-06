#include "DataPlot.h"

void DataPlot(const Vector2* data, Vector2* points, const int count, const Bounds bounds) {
    for (int i = 0; i < count; ++i) {
        points[i] = transform_v_to_pixel(data[i], bounds);
    }

    DrawSplineLinear(points, count, 2.f, DARKBLUE);
}