#include "SplinePlot.h"

#include <math.h>
#include <raylib.h>

#include "../plot_math.h"

#define COUNT 200

void compute(Vector2* points, const Bounds bounds) {
    const double step = (bounds.end_x - bounds.start_x) / COUNT;

    for (int i = 0; i < COUNT; ++i) {
        const double x = bounds.start_x + step * i;
        points[i].x = transform_x_to_pixelf(x, bounds.start_x, bounds.end_x);
        points[i].y = transform_y_to_pixelf(sin(x), bounds.start_y, bounds.end_y);
    }
}

void SplinePlot(const Bounds bounds) {
    static Vector2 points[COUNT];
    compute(points, bounds);

    DrawSplineLinear(points, COUNT, 2.f, DARKGREEN);
}