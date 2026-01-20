#include "Line.h"

#include <math.h>

#include "../input_mode.h"
#include "../../text/TextBox.h"

#include "../../math/vector2.h"

void DrawLineWithTransform(Vector2 p1, Vector2 p2, const Bounds bounds, const Color color) {
    p1 = transform_v_to_pixel(p1, bounds);
    p2 = transform_v_to_pixel(p2, bounds);
    DrawLineEx(p1, p2, 2, color);
}

void DrawCurveLinear(const CurveLinear curve_linear, const Bounds bounds) {
    const Vector2 p0 = { -curve_linear.b / curve_linear.a, 0 };
    DrawLineWithTransform(p0, curve_linear.end_point, bounds, GREEN);
}

void Line(DataPlotState* state, const DataSource data_source, const Bounds bounds) {
    if (state->curve_linear.a && !is_input_mode(INPUT_MODE_SELECT)) {
        DrawCurveLinear(state->curve_linear, bounds);
    }

    if (state->selected_point == -1) return;

    Vector2 p1 = data_source.data[state->selected_point];
    if (state->selected_second_point == -1) {
        if (is_input_mode(INPUT_MODE_SELECT)) {
            DrawLineEx(transform_v_to_pixel(p1, bounds), state->view_move.mouse_position, 2, ORANGE);
        }
        return;
    }
    int point_index = state->selected_second_point;
    Vector2 p2 = data_source.data[point_index];

    if (fabsf(p1.x) > fabsf(p2.x)) {
        const Vector2 tmp = p1;
        p1 = p2;
        p2 = tmp;
        point_index = state->selected_point;
    }

    const Vector2 d = vec2_subtract(p1, p2);
    if (fabsf(d.y) < .01) {
        DrawLineWithTransform(p1, p2, bounds, RED);
        return;
    }

    const float a = d.y / d.x;
    const float b = p1.y - p1.x*a;
    state->curve_linear = (CurveLinear) {
        .end_point = p2,
        .end_point_index = point_index,
        .a = a,
        .b = b
    };
    DrawCurveLinear(state->curve_linear, bounds);
}
