#include "DataPlot.h"

#include "../../data/point_data.h"

void DataPlot(const Vector2* data, Vector2* points, int count, const Bounds bounds, const move_change_t change) {
    DrawSplineLinear(points, count, 2.f, DARKBLUE);
}
