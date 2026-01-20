#include "MultiPlot.h"

#include <stdlib.h>

#include "PointHoverTooltip.h"
#include "Spline.h"
#include "../../files/open_files.h"

void MultiPlot(const MultiPlotProps props, MultiPlotState* state, const move_change_t change) {
    for (int i = 0; i < state->plot_count; ++i) {
        const Color color = COLORS[i & 7];
        const DataSource source = state->plots[i].data_source;
        PointCache* cache = &state->plots[i].point_cache;

        if (change) {
            cache->visible = compute_visible_points(source, cache->buffer, props.bounds);
        }

        if (cache->visible.count) {
            Spline(cache->buffer, cache->visible.count, color);
        }
        const int hover_index = PointHoverTooltip((PointHoverTooltipProps) {
            .data = source.data,
            .points = cache->buffer,
            .visible = cache->visible,
            .color = color
        });
    }
}

void MultiPlot_enable(MultiPlotState* state, const ViewMove view_move) {
    const int count = get_count();
    const float xx = 2, yy = 3;

    state->plots = malloc(count * sizeof(SinglePlot));
    state->plot_count = 0;
    state->view_move = view_move;
    state->enabled = true;

    const OpenFile* files = get_files();
    for (int i = 0; i < count; ++i) {
        if (!is_imported(&files[i])) continue;

        const DataSource source = files[i].data_source;

        const SinglePlot plot = {
            .point_cache = { .buffer = malloc(source.count * sizeof(Vector2)) },
            .data_source = { .data = malloc(source.count * sizeof(Vector2)), .count = source.count }
        };

        for (int j = 0; j < source.count; ++j) {
            plot.data_source.data[j].x = source.data[j].x / xx;
            plot.data_source.data[j].y = source.data[j].y / yy;
        }
        state->plots[state->plot_count++] = plot;
    }
}

ViewMove MultiPlot_disable(MultiPlotState* state) {
    for (int i = 0; i < state->plot_count; ++i) {
        free(state->plots[i].point_cache.buffer);
        free(state->plots[i].data_source.data);
    }
    free(state->plots);

    state->enabled = false;
    return state->view_move;
}
