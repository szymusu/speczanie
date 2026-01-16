#include "DataPlot.h"

#include <stdlib.h>

#include "Arrow.h"
#include "Line.h"
#include "PointHoverTooltip.h"
#include "Polynomial.h"
#include "../../math/vector2.h"


void DataPlot(const DataPlotProps props, move_change_t change, DataPlotState* state) {
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
    const int hover_absolute_index = hover_index + state->visible.start;
    if (hover_index != -1) {
        PointHoverTooltip((PointHoverTooltipProps){
            .data = props.data_source.data,
            .points = state->point_buffer,
            .visible = state->visible,
            .index = hover_index
        });
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (state->input_mode == PLOT_INPUT_REGRESSION) {
                state->is_selected_flags[hover_absolute_index] = true;
            }
            else {
                state->selected_point = hover_absolute_index;
                state->input_mode = PLOT_INPUT_SELECT;
            }
        }
    }
    if (state->input_mode == PLOT_INPUT_SELECT) {
        const int second_point = hover_absolute_index;
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

    if (state->input_mode == PLOT_INPUT_REGRESSION) {
        int selected_count = 0;
        for (int i = 0; i < props.data_source.count; ++i) {
            if (state->is_selected_flags[i]) {
                state->regression_points[selected_count++] = props.data_source.data[i];
            }
        }
        if (selected_count > 2) {
            change |= MOVE_CHANGE_POLYNOMIAL;
            Polynomial(&state->curve_polynomial, state->regression_points, selected_count, change, props.bounds);
        }
    }
}

DataPlotState DataPlotState_create(const int data_count) {
    return (DataPlotState) {
        .point_buffer = malloc(sizeof(Vector2) * data_count),
        .shadow_point_buffer = malloc(sizeof(Vector2) * data_count),
        .selected_point = -1,
        .selected_second_point = -1,
        .is_selected_flags = calloc(data_count, sizeof(bool)),
        .zoom = 1.f,
        .scale_x = 1.f,
        .regression_points = malloc(sizeof(Vector2) * data_count),
        .curve_polynomial = {.coefficients = malloc(sizeof(float) * data_count)}
    };
}

void DataPlotState_destroy(DataPlotState* state) {
    free(state->point_buffer);
    free(state->shadow_point_buffer);
    free(state->is_selected_flags);
    free(state->regression_points);
    free(state->curve_polynomial.coefficients);
    // free(state->curve_polynomial.coefficients);
}
