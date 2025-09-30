#include "SplinePlot.h"

#include <math.h>
#include <raylib.h>

#include "../plot_math.h"

#define COUNT 200

void compute(Vector2* points, const double start_x, const double end_x, const double start_y, const double end_y) {
    const double step = (end_x - start_x) / COUNT;

    for (int i = 0; i < COUNT; ++i) {
        const double x = start_x + step * i;
        points[i].x = transform_x_to_pixelf(x, start_x, end_x);
        points[i].y = transform_y_to_pixelf(sin(x), start_y, end_y);
    }
}

void SplinePlot(const double start_x, const double end_x, const double start_y, const double end_y) {
    static Vector2 points[COUNT];
    static bool first = true;
    if (first) {
        compute(points, start_x, end_x, start_y, end_y);
        first = false;
    }

    DrawSplineLinear(points, COUNT, 2.f, DARKGREEN);
}