#include "Arrow.h"

#include <math.h>

#include "../../util/vector2.h"

#define ARROW_PADDING 0.3f
#define ARROW_HEAD_ANGLE 0.6f

void Arrow(Vector2 origin, const Vector2 direction, const Bounds bounds) {
    const float magnitude = vec2_magnitude(direction);
    Vector2 end = { origin.x + direction.x, origin.y - direction.y };

    if (magnitude < ARROW_PADDING * 2) {
        DrawLineV(
        transform_v_to_pixel(origin, bounds),
        transform_v_to_pixel(end, bounds),
        RED);
        return;
    }
    const float inv_magnitude = 1 / magnitude;
    const Vector2 margin = { direction.x * inv_magnitude * ARROW_PADDING, direction.y * inv_magnitude * ARROW_PADDING };

    origin.x += margin.x;
    origin.y -= margin.y;
    end.x -= margin.x;
    end.y += margin.y;

    const float angle = vec2_angle(direction);
    Vector2 head_right = end;
    head_right.x -= cosf(angle - ARROW_HEAD_ANGLE) * ARROW_PADDING;
    head_right.y += sinf(angle - ARROW_HEAD_ANGLE) * ARROW_PADDING;
    Vector2 head_left = end;
    head_left.x -= cosf(angle + ARROW_HEAD_ANGLE) * ARROW_PADDING;
    head_left.y += sinf(angle + ARROW_HEAD_ANGLE) * ARROW_PADDING;

    DrawLineV(
        transform_v_to_pixel(origin, bounds),
        transform_v_to_pixel(end, bounds),
        RED);
    DrawLineV(
        transform_v_to_pixel(end, bounds),
        transform_v_to_pixel(head_right, bounds),
        RED);
    DrawLineV(
        transform_v_to_pixel(end, bounds),
        transform_v_to_pixel(head_left, bounds),
        RED);
}
