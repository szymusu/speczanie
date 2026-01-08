#include "Line.h"

void Line(const DataPlotState* state, const DataSource data_source, const Bounds bounds) {
    if (state->input_mode != PLOT_INPUT_SELECT) return;
    if (state->selected_point == -1) return;

    const Vector2 p1 = transform_v_to_pixel(data_source.data[state->selected_point], bounds);
    Vector2 p2;
    if (state->selected_second_point == -1) {
        p2 = state->mouse_position;
    }
    else {
        p2 = transform_v_to_pixel(data_source.data[state->selected_second_point], bounds);
    }

    DrawLineEx(p1, p2, 2, ORANGE);
}
