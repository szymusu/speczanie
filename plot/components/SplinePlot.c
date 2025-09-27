#include "SplinePlot.h"

#include <math.h>
#include <raylib.h>

#include "../plot_math.h"

#define COUNT 200

double init(Vector2* points) {
    for (int i = 0; i < COUNT; ++i) {
        const float x = (float) i / COUNT * 20.f - 10.f;
        points[i].x = (x + 10.f) / 20.f * PLOT_WIDTH + PLOT_OFFSET_X;
        points[i].y = (sinf(x)*2 + 10.f) / 20.f * PLOT_HEIGHT + PLOT_OFFSET_Y;
    }
    return GetTime();
}

void SplinePlot() {
    static Vector2 points[COUNT];
    static bool first = true;
    if (first) {
        init(points);
        first = false;
    }

    DrawSplineLinear(points, COUNT, 2.f, DARKGREEN);
}