#include "DataPlot.h"

#include <stdlib.h>

#include "Arrow.h"
#include "Line.h"
#include "PointHoverTooltip.h"
#include "Polynomial.h"
#include "../../math/vector2.h"


void DataPlot(const DataPlotProps props, const move_change_t change, DataPlotState* state) {
    if (change) {
        state->visible = compute_visible_points(props.data_source, state->point_buffer, props.bounds);
        if (!is_vec2_zero(state->plot_offset)) {
            state->shadow_visible = compute_visible_points_offset(props.data_source, state->shadow_point_buffer, props.bounds, state->plot_offset);
        }
        else {
            state->shadow_visible.count = 0;
        }
    }
    DrawSplineLinear(state->point_buffer, state->visible.count, 2.f, DARKBLUE);
    DrawCircleV(state->point_buffer[0], 6, RED);
    DrawCircleV(state->point_buffer[state->visible.count - 1], 6, ORANGE);

    if (state->shadow_visible.count) {
        DrawSplineLinear(state->shadow_point_buffer, state->shadow_visible.count, 2.f, (Color){150, 150, 150, 200});
        Arrow(props.data_source.data[0], state->plot_offset, props.bounds);
    }

    const int hover_index = find_hover_point(state->point_buffer, state->visible.count);
    if (hover_index != -1) {
        PointHoverTooltip((PointHoverTooltipProps){
            .data = props.data_source.data,
            .points = state->point_buffer,
            .visible = state->visible,
            .index = hover_index
        });
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            state->selected_point = hover_index + state->visible.start;
            state->input_mode = PLOT_INPUT_SELECT;
        }
    }
    if (state->input_mode == PLOT_INPUT_SELECT) {
        const int second_point = hover_index + state->visible.start;
        if (second_point == state->selected_point || hover_index == -1) {
            state->selected_second_point = -1;
        }
        else {
            state->selected_second_point = second_point;
        }
    }

    if (is_in_view(state->selected_point, state->visible)) {
        DrawCircleV(state->point_buffer[state->selected_point - state->visible.start], 7, BLUE);
    }
    if (is_in_view(state->selected_second_point, state->visible)) {
        DrawCircleV(state->point_buffer[state->selected_second_point - state->visible.start], 7, SKYBLUE);
    }

    Line(state, props.data_source, props.bounds);
    Polynomial(&state->curve_polynomial, change, props.bounds);
}

DataPlotState DataPlotState_create(const int data_count) {
    return (DataPlotState) {
        .point_buffer = malloc(sizeof(Vector2) * data_count),
        .shadow_point_buffer = malloc(sizeof(Vector2) * data_count),
        .selected_point = -1,
        .selected_second_point = -1,
        .zoom = 1.f,
    };
}

void DataPlotState_destroy(DataPlotState* state) {
    free(state->point_buffer);
    // free(state->curve_polynomial.coefficients);
}
