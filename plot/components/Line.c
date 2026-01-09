#include "Line.h"

#include <math.h>

#include "../../util/vector2.h"

void DrawLineWithTransform(Vector2 p1, Vector2 p2, const Bounds bounds, const Color color) {
    p1 = transform_v_to_pixel(p1, bounds);
    p2 = transform_v_to_pixel(p2, bounds);
    DrawLineEx(p1, p2, 2, color);
}

void Line(const DataPlotState* state, const DataSource data_source, const Bounds bounds) {
    if (state->selected_point == -1) return;

    Vector2 p1 = data_source.data[state->selected_point];
    if (state->selected_second_point == -1) {
        if (state->input_mode == PLOT_INPUT_SELECT)
            DrawLineEx(transform_v_to_pixel(p1, bounds), state->mouse_position, 2, ORANGE);
        return;
    }
    Vector2 p2 = data_source.data[state->selected_second_point];

    if (fabsf(p1.x) > fabsf(p2.x)) {
        const Vector2 tmp = p1;
        p1 = p2;
        p2 = tmp;
    }

    const Vector2 d = vec2_subtract(p1, p2);
    if (fabsf(d.y) < .01) {
        DrawLineWithTransform(p1, p2, bounds, RED);
        return;
    }

    const float a = d.y / d.x;
    const float b = p1.y - p1.x*a;

    const float x0 = -b / a;
    const Vector2 p0 = { x0, 0 };
    DrawLineWithTransform(p0, p2, bounds, GREEN);
}
