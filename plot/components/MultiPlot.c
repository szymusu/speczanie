#include "MultiPlot.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ConstantsInput.h"
#include "PointHoverTooltip.h"
#include "Polynomial.h"
#include "Spline.h"
#include "../input_mode.h"
#include "../../files/open_files.h"
#include "../../math/regression.h"

void MultiPlot_set(MultiPlotState* state) {
    float min_x = INFINITY, max_x = -INFINITY;

    for (int i = 0; i < state->plot_count; ++i) {
        const DataSource* source = &state->plots[i].data_source;
        for (int j = 0; j < source->count; ++j) {
            const float x = source->data[j].x / state->L0;
            source->data[j].x = x;
            source->data[j].y /= state->S0 / 1000.f; // GPa -> MPa

            if (x < min_x) min_x = x;
            if (x > max_x) max_x = x;
        }
    }
    printf("min %f, max %f\n", min_x, max_x);
    state->view_move.scale_x = fit_scale(min_x, max_x) * 1000.f / state->S0;
    state->view_move.pan = (Vector2){0,0};
    state->view_move.zoom /= 1000.f / state->S0;
    snprintf(state->constants_text, 64, "S₀ = %f\nL₀ = %f", state->S0, state->L0);
}

void MultiPlot(MultiPlotProps props, MultiPlotState* state, move_change_t* change) {
    if (!get_count()) MultiPlot_disable(state);

    if (!state->S0 || !state->L0) {
        set_input_mode(INPUT_MODE_TEXT);
        if (ConstantsInput(state)) {
            set_input_mode(INPUT_MODE_IDLE);
            MultiPlot_set(state);
            *change |= MOVE_CHANGE_PLOT | MOVE_CHANGE_ZOOM | MOVE_CHANGE_PAN;
            props.bounds = compute_bounds(state->view_move);
        }
        else return;
    }

    const bool is_regression = is_input_mode(INPUT_MODE_REGRESSION);

    for (int i = 0; i < state->plot_count; ++i) {
        const Color color = COLORS[i & 7];
        const DataSource source = state->plots[i].data_source;
        PointCache* cache = &state->plots[i].point_cache;

        if (*change) {
            cache->visible = compute_visible_points(source, cache->buffer, props.bounds);
        }

        if (cache->visible.count) {
            const bool is_shown = state->selected_plot == -1 || state->selected_plot == i || !is_regression;
            Spline(cache->buffer, cache->visible.count, is_shown ? color : (Color) {150, 150, 150, 255});
        }
        const int hover_index = PointHoverTooltip((PointHoverTooltipProps) {
            .data = source.data,
            .points = cache->buffer,
            .visible = cache->visible,
            .color = color
        });

        if (!is_regression) {
            state->selected_plot = -1;
            continue;
        }
        if (hover_index != -1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            state->regression_points_count = 0;
            if (state->selected_plot != i) {
                state->selected1 = hover_index;
                state->selected2 = -1;
                state->selected_plot = i;
            }
            else if (state->selected1 == -1) {
                state->selected1 = hover_index;
            }
            else {
                if (state->selected2 == -1) {
                    state->selected2 = hover_index;
                }
                else {
                    state->selected1 = hover_index;
                    state->selected2 = -1;
                }
            }
        }

        if (state->selected_plot == i) {
            const int i1 = state->selected1;
            const int i2 = state->selected2;
            if (i1 != -1) {
                DrawCircleV(transform_v_to_pixel(source.data[i1], props.bounds), 7, color);
            }
            if (i2 != -1) {
                DrawCircleV(transform_v_to_pixel(source.data[i2], props.bounds), 7, color);
            }

            if (i1 != -1 && i2 != -1 && i1 != i2) {
                state->regression_points_count = prepare_points_between(i1, i2, source, state->regression_points, &state->curve);
                state->selected1 = -1;
                state->selected2 = -1;
                *change |= MOVE_CHANGE_POLYNOMIAL;
            }
            if (state->regression_points_count) {
                Polynomial(&state->curve, state->regression_points, state->regression_points_count, *change, props.bounds);
            }
        }
    }
}

#define TEXT_MAX_LEN 14 // max length of one (of 2) text buffers, excluding cursor and null terminator
void MultiPlot_enable(MultiPlotState* state, const ViewMove view_move) {
    const int count = get_count();

    char* text_buffer = calloc((TEXT_MAX_LEN + 2) * 2, 1);
    state->text_max_len = TEXT_MAX_LEN;
    state->text_buffers[0] = text_buffer;
    state->text_buffers[1] = &text_buffer[TEXT_MAX_LEN + 2];

    if (state->S0_tmp != 0 && state->L0_tmp != 0) {
        state->text_lengths[0] = snprintf(state->text_buffers[0], TEXT_MAX_LEN, "%f", state->S0_tmp) - 1;
        state->text_lengths[1] = snprintf(state->text_buffers[1], TEXT_MAX_LEN, "%f", state->L0_tmp) - 1;
    }
    else {
        state->text_lengths[0] = 0;
        state->text_lengths[1] = 0;
        state->text_buffers[0][0] = '_';
        state->text_buffers[1][0] = '_';
    }

    state->input_focus = 1;
    state->selected1 = -1;
    state->selected2 = -1;
    state->selected_plot = -1;

    state->plots = malloc(count * sizeof(SinglePlot));
    state->plot_count = 0;
    state->view_move = view_move;
    state->enabled = true;

    const OpenFile* files = get_files();
    int biggest_source = 0;
    for (int i = 0; i < count; ++i) {
        if (!is_imported(&files[i])) continue;

        const DataSource source = files[i].data_source;
        if (source.count > biggest_source) biggest_source = source.count;

        const SinglePlot plot = {
            .point_cache = { .buffer = malloc(source.count * sizeof(Vector2)) },
            .data_source = { .data = malloc(source.count * sizeof(Vector2)), .count = source.count }
        };

        memcpy(plot.data_source.data, source.data, source.count * sizeof source.data[0]);
        state->plots[state->plot_count++] = plot;
    }

    state->curve = (CurvePolynomial) { .order = 4 };
    state->regression_points = malloc(biggest_source * sizeof state->regression_points[0]);
}

ViewMove MultiPlot_disable(MultiPlotState* state) {
    for (int i = 0; i < state->plot_count; ++i) {
        free(state->plots[i].point_cache.buffer);
        free(state->plots[i].data_source.data);
    }
    free(state->plots);
    free(state->text_buffers[0]);
    free(state->regression_points);

    state->enabled = false;
    state->S0 = 0;
    state->L0 = 0;
    return state->view_move;
}
