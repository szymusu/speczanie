#include "Arrow.h"

#include "../../util/vector2.h"

#define ARROW_PADDING 0.3f

void Arrow(Vector2 origin, const Vector2 direction, const Bounds bounds) {
    const float inv_magnitude = 1 / vec2_magnitude(direction);
    Vector2 end = { origin.x + direction.x, origin.y - direction.y };
    const Vector2 margin = { direction.x * inv_magnitude * ARROW_PADDING, direction.y * inv_magnitude * ARROW_PADDING };

    origin.x += margin.x;
    origin.y -= margin.y;
    end.x -= margin.x;
    end.y += margin.y;

    DrawLineV(
        transform_v_to_pixel(origin, bounds),
        transform_v_to_pixel(end, bounds),
        RED);
}
