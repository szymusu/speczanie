#include "line.h"

#include "vector2.h"

float get_line_slope(const Vector2 p1, const Vector2 p2) {
    const Vector2 d = vec2_subtract(p1, p2);
    return d.y / d.x;
}
