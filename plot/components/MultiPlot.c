#include "MultiPlot.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ConstantsInput.h"
#include "PointHoverTooltip.h"
#include "Spline.h"
#include "../input_mode.h"
#include "../../files/open_files.h"
#include "../../text/text.h"

void MultiPlot_set(MultiPlotState* state) {
    for (int i = 0; i < state->plot_count; ++i) {
        const DataSource* source = &state->plots[i].data_source;
        for (int j = 0; j < source->count; ++j) {
            source->data[j].x /= state->L0;
            source->data[j].y /= state->S0 / 1000.f; // GPa -> MPa
        }
    }
    snprintf(state->constants_text, 64, "S₀ = %f\nL₀ = %f", state->S0, state->L0);
}

void MultiPlot(const MultiPlotProps props, MultiPlotState* state, move_change_t change) {
    if (!get_count()) MultiPlot_disable(state);

    if (!state->S0 || !state->L0) {
        set_input_mode(INPUT_MODE_TEXT);
        if (ConstantsInput(state)) {
            set_input_mode(INPUT_MODE_IDLE);
            MultiPlot_set(state);
            change |= MOVE_CHANGE_PLOT | MOVE_CHANGE_ZOOM;
        }
        else return;
    }

    Text(state->constants_text, 10, 50, 20, BLACK);

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

#define TEXT_MAX_LEN 14 // max length of one (of 2) text buffers, excluding cursor and null terminator
void MultiPlot_enable(MultiPlotState* state, const ViewMove view_move) {
    const int count = get_count();

    char* text_buffer = calloc((TEXT_MAX_LEN + 2) * 2, 1);
    state->text_max_len = TEXT_MAX_LEN;
    state->text_buffers[0] = text_buffer;
    state->text_buffers[1] = &text_buffer[TEXT_MAX_LEN + 2];
    state->text_lengths[0] = 0;
    state->text_lengths[1] = 0;
    state->text_buffers[0][0] = '_';
    state->text_buffers[1][0] = '_';

    state->input_focus = 1;

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
    free(state->text_buffers[0]);

    state->enabled = false;
    return state->view_move;
}
