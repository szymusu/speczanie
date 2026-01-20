#include "Spline.h"

void Spline(const Vector2* points, const int count, const Color color) {
    Color ends_color = color;
    ends_color.a = 127;

    DrawSplineLinear(points, count, 2.f, color);

    DrawCircleV(points[0], 4, ends_color);
    DrawCircleV(points[count - 1], 4, ends_color);
}
