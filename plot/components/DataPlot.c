#include "DataPlot.h"

#include "../../data/point_data.h"

void DataPlot(const Vector2* data, Vector2* points, const int count, const Bounds bounds) {
    translate_data_to_points(data, points, count, bounds);

    DrawSplineLinear(points, count, 2.f, DARKBLUE);
}
