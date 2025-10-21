#include "DataPlot.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../data/point_data.h"
#include "../../text/text.h"
#include "../../diagnostics/components/Clock.h"

int find_hover_point(const Vector2* points, const int count) {
    const Vector2 mouse = GetMousePosition();
    for (int i = 0; i < count; ++i) {
        const float diff_x = mouse.x - points[i].x;
        const float diff_y = mouse.y - points[i].y;
        if (diff_x*diff_x + diff_y*diff_y < 100) {
            return i;
        }
    }
    return -1;
}

void DataPlot(const DataPlotProps props, const move_change_t change, DataPlotState* state) {
    if (change) {
        clock_start();
        const VisiblePointInfo visible = compute_visible_points(props.data_source, state->point_buffer, props.bounds, props.plot_offset);
        clock_end();
        state->visible_count = visible.count;
        state->visible_start = visible.start;
    }
    Clock();
    sprintf(state->count_text, "C: %d", state->visible_count);
    Text(state->count_text, 700, 430, 20, RED);
    DrawSplineLinear(state->point_buffer, state->visible_count, 2.f, DARKBLUE);
    DrawCircleV(state->point_buffer[0], 10.f, RED);
    DrawCircleV(state->point_buffer[state->visible_count - 1], 10.f, ORANGE);

    const int hover_index = find_hover_point(state->point_buffer, state->visible_count);
    char hover_text[32];
    if (hover_index != -1) {
        const Vector2 data_point = props.data_source.data[hover_index - state->visible_start];
        Vector2 pixel_point = state->point_buffer[hover_index];
        DrawCircleV(pixel_point, 6.f, DARKBLUE);
        pixel_point.x += 10;
        pixel_point.y -= 44;
        sprintf(hover_text, "x: %.3f\ny: %.3f", data_point.x, data_point.y);
        DrawRectangleV(pixel_point, (Vector2){80, 34}, WHITE);
        DrawRectangleLines(pixel_point.x, pixel_point.y, 80, 34, DARKBLUE);
        pixel_point.x += 5;
        pixel_point.y += 2;
        TextV(hover_text, pixel_point, 15, BLACK);
    }
}

DataPlotState DataPlotState_create(const int data_count) {
    return (DataPlotState) { .point_buffer = malloc(sizeof(Vector2) * data_count) };
}

void DataPlotState_destroy(DataPlotState* state) {
    free(state->point_buffer);
}
