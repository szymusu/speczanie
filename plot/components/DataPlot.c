#include "DataPlot.h"

#include <stdlib.h>

#include "Line.h"
#include "PointHoverTooltip.h"
#include "Polynomial.h"
#include "Spline.h"
#include "../../math/vector2.h"
#include "../../math/regression.h"


void DataPlot(const DataPlotProps props, move_change_t change, DataPlotState* state) {
    if (change) {
        state->point_cache.visible = compute_visible_points(props.data_source, state->point_cache.buffer, props.bounds);
        if (!is_vec2_zero(state->plot_move.plot_offset)) {
            state->shadow_cache.visible = compute_visible_points_offset(
                props.data_source,
                state->shadow_cache.buffer,
                props.bounds,
                state->plot_move.plot_offset
                );
        }
        else {
            state->shadow_cache.visible.count = 0;
        }
    }
    if (state->point_cache.visible.count) {
        Spline(state->point_cache.buffer, state->point_cache.visible.count, props.color);
    }

    if (state->shadow_cache.visible.count) {
        DrawSplineLinear(state->shadow_cache.buffer, state->shadow_cache.visible.count, 2.f, (Color){150, 150, 150, 200});
    }

    const int hover_index = PointHoverTooltip((PointHoverTooltipProps){
        .data = props.data_source.data,
        .points = state->point_cache.buffer,
        .visible = state->point_cache.visible,
        .color = props.color
    });
    if (hover_index != -1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (state->input_mode == PLOT_INPUT_REGRESSION) {
            state->regression_points_count = 0;
            if (state->selected_point != -1 && state->selected_point != hover_index) {
                state->selected_second_point = hover_index;
            }
            else state->selected_point = hover_index;
        }
        else {
            state->selected_point = hover_index;
            state->selected_second_point = -1;
            state->curve_linear = (CurveLinear) {0};
            state->input_mode = PLOT_INPUT_SELECT;
        }
    }
    if (state->input_mode == PLOT_INPUT_SELECT) {
        const int second_point = hover_index;
        if (second_point == state->selected_point || hover_index == -1) {
            state->selected_second_point = -1;
        }
        else {
            state->selected_second_point = second_point;
        }
    }

    if (is_in_view(state->selected_point, state->point_cache.visible)) {
        DrawCircleV(state->point_cache.buffer[state->selected_point - state->point_cache.visible.start], 7, BLUE);
    }
    if (is_in_view(state->selected_second_point, state->point_cache.visible)) {
        DrawCircleV(state->point_cache.buffer[state->selected_second_point - state->point_cache.visible.start], 7, SKYBLUE);
    }


    if (state->input_mode == PLOT_INPUT_REGRESSION) {
        const int i1 = state->selected_point;
        const int i2 = state->selected_second_point;
        if (i1 != -1 && i2 != -1) {
            int start, end;
            if (i1 < i2) {
                start = i1, end = i2;
            }
            else {
                start = i2, end = i1;
            }
            int count = 0;
            for (int i = start; i <= end; ++i, ++count) {
                state->regression_points[count] = props.data_source.data[i];
            }
            state->curve_polynomial.normal_offset_x = normalize(state->regression_points, count);
            state->regression_points_count = count;
            state->selected_point = -1;
            state->selected_second_point = -1;
            change |= MOVE_CHANGE_POLYNOMIAL;
        }
        if (state->regression_points_count) {
            Polynomial(&state->curve_polynomial, state->regression_points, state->regression_points_count, change, props.bounds);
        }
    }
    else {
        Line(state, props.data_source, props.bounds);
    }
}

DataPlotState DataPlotState_create(const int data_count) {
    char* equation = malloc(256);
    equation[0] = 0;
    return (DataPlotState) {
        .x_label = "",
        .y_label = "",
        .point_cache = { .buffer = malloc(sizeof(Vector2) * data_count) },
        .shadow_cache = { .buffer = malloc(sizeof(Vector2) * data_count) },
        .selected_point = -1,
        .selected_second_point = -1,
        .view_move = { .scale_x = 100, .zoom = 1 },
        .regression_points = malloc(sizeof(Vector2) * data_count),
        .operation_stack = data_operation_stack_init(),
        .curve_polynomial = {
            .order = 4,
            .coefficients = malloc(sizeof(float) * POLYNOMIAL_MAX_DEGREE),
            .point_buffer = malloc(sizeof (Vector2) * POLYNOMIAL_POINT_COUNT),
            .equation = equation
        },
    };
}

void DataPlotState_destroy(DataPlotState* state) {
    free(state->point_cache.buffer);
    free(state->shadow_cache.buffer);
    free(state->regression_points);
    free(state->curve_polynomial.coefficients);
    free(state->curve_polynomial.point_buffer);
    free(state->curve_polynomial.equation);
    data_operation_stack_free(&state->operation_stack);
}
