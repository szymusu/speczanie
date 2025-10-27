#include "DataPlot.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../text/text.h"
#include "../../diagnostics/components/Clock.h"
#include "PointHoverTooltip.h"


void DataPlot(const DataPlotProps props, const move_change_t change, DataPlotState* state) {
    if (change) {
        clock_start();
        state->visible = compute_visible_points(props.data_source, state->point_buffer, props.bounds, props.plot_offset);
        clock_end();
    }
    Clock();
    sprintf(state->count_text, "C: %d", state->visible.count);
    Text(state->count_text, 700, 430, 20, RED);
    DrawSplineLinear(state->point_buffer, state->visible.count, 2.f, DARKBLUE);
    DrawCircleV(state->point_buffer[0], 10.f, RED);
    DrawCircleV(state->point_buffer[state->visible.count - 1], 10.f, ORANGE);

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
        .selected_point = -1
    };
}

void DataPlotState_destroy(DataPlotState* state) {
    free(state->point_buffer);
}
