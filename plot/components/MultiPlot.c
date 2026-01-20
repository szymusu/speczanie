#include "MultiPlot.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ConstantsInput.h"
#include "PointHoverTooltip.h"
#include "Spline.h"
#include "../../files/open_files.h"

void MultiPlot_set(MultiPlotState* state) {
    for (int i = 0; i < state->plot_count; ++i) {
        const DataSource* source = &state->plots[i].data_source;
        for (int j = 0; j < source->count; ++j) {
            source->data[j].x /= state->L0;
            source->data[j].y /= state->S0 / 1000.f; // GPa -> MPa
        }
    }
}

void MultiPlot(const MultiPlotProps props, MultiPlotState* state, move_change_t change) {
    if (!state->S0 || !state->L0) {
        if (ConstantsInput(&state->S0, &state->L0)) {
            MultiPlot_set(state);
            change |= MOVE_CHANGE_PLOT | MOVE_CHANGE_ZOOM;
        }
        else return;
    }

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

        memcpy(plot.data_source.data, source.data, source.count * sizeof source.data[0]);
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
