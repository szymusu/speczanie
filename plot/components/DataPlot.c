#include "DataPlot.h"

#include <stdio.h>
#include <stdlib.h>

#include "Arrow.h"
#include "../../text/text.h"
#include "../../diagnostics/components/Clock.h"
#include "PointHoverTooltip.h"
#include "../../util/vector2.h"


void DataPlot(const DataPlotProps props, const move_change_t change, DataPlotState* state) {
    if (change) {
        state->visible = compute_visible_points(props.data_source, state->point_buffer, props.bounds);
        if (!is_vec2_zero(props.plot_offset)) {
            state->shadow_visible = compute_visible_points_offset(props.data_source, state->shadow_point_buffer, props.bounds, props.plot_offset);
        }
        else {
            state->shadow_visible.count = 0;
        }
    }
    sprintf(state->count_text, "C: %d", state->visible.count);
    Text(state->count_text, PLOT_WIDTH - 100, PLOT_HEIGHT - 20, 20, RED);
    DrawSplineLinear(state->point_buffer, state->visible.count, 2.f, DARKBLUE);
    DrawCircleV(state->point_buffer[0], 10.f, RED);
    DrawCircleV(state->point_buffer[state->visible.count - 1], 10.f, ORANGE);

    if (state->shadow_visible.count) {
        DrawSplineLinear(state->shadow_point_buffer, state->shadow_visible.count, 2.f, (Color){150, 150, 150, 200});
        Arrow(props.data_source.data[0], props.plot_offset, props.bounds);
    }

    const int hover_index = find_hover_point(state->point_buffer, state->visible.count);
    if (hover_index != -1) {
        PointHoverTooltip((PointHoverTooltipProps) {
           .data = props.data_source.data,
           .points = state->point_buffer,
           .visible = state->visible,
           .index = hover_index
       });
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            state->selected_point = hover_index + state->visible.start;
        }
    }

    if (state->selected_point >= state->visible.start && state->selected_point < state->visible.start + state->visible.count) {
        DrawCircleV(state->point_buffer[state->selected_point - state->visible.start], 7, BLUE);
    }
}

DataPlotState DataPlotState_create(const int data_count) {
    return (DataPlotState) {
        .point_buffer = malloc(sizeof(Vector2) * data_count),
        .shadow_point_buffer = malloc(sizeof(Vector2) * data_count),
        .selected_point = -1
    };
}

void DataPlotState_destroy(DataPlotState* state) {
    free(state->point_buffer);
}
