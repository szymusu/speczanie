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

    PointHoverTooltip((PointHoverTooltipProps) {
        .data = props.data_source.data,
        .points = state->point_buffer,
        .visible = state->visible
    });
}

DataPlotState DataPlotState_create(const int data_count) {
    return (DataPlotState) { .point_buffer = malloc(sizeof(Vector2) * data_count) };
}

void DataPlotState_destroy(DataPlotState* state) {
    free(state->point_buffer);
}
