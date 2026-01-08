#include "Controls.h"

#include "../../text/Button.h"
#include "../../text/text.h"
#include "../../data/data_source.h"
#include "../../util/vector2.h"

move_change_t Controls(OpenFile* current_file, DataPlotState* state, move_change_t change) {
    if (change & MOVE_CHANGE_APPLY_OFFSET) {
        data_apply_offset(&current_file->data_source, state->plot_offset);
        state->plot_offset = VECTOR2_ZERO;
    }

    if (Button((Vector2) {10, 50}, "Odwroc y", 16, 0) == BUTTON_STATE_CLICKED) {
        data_scale_y(&current_file->data_source, -1);
        change |= MOVE_CHANGE_PLOT;
    }

    if (Button((Vector2) {100, 50}, "Odwroc x", 16, 0) == BUTTON_STATE_CLICKED) {
        data_flip_x(&current_file->data_source);
        change |= MOVE_CHANGE_PLOT;
    }

    if (!is_vec2_zero(current_file->data_source.data[0])) {
        if (Button((Vector2) {10, 100}, "Zeruj start", 16, 0) == BUTTON_STATE_CLICKED) {
            data_apply_offset(&current_file->data_source, (Vector2) {
                -current_file->data_source.data[0].x,
                current_file->data_source.data[0].y
            });
            state->plot_offset = VECTOR2_ZERO;
            change |= MOVE_CHANGE_PLOT;
        }
    }

    if (current_file->data_plot_state.selected_point > 0) {
        Text("Utnij", 10, 200, 16, BLACK);
        if (Button((Vector2) {70, 216}, "Lewo", 16, TEXTBOX_ALIGN_RIGHT) == BUTTON_STATE_CLICKED) {
            data_cut_left(&current_file->data_source, current_file->data_plot_state.selected_point);
            current_file->data_plot_state.selected_point = -1;
            change |= MOVE_CHANGE_PLOT;
        }
        if (Button((Vector2) {75, 216}, "Prawo", 16, 0) == BUTTON_STATE_CLICKED) {
            data_cut_right(&current_file->data_source, current_file->data_plot_state.selected_point);
            current_file->data_plot_state.selected_point = -1;
            change |= MOVE_CHANGE_PLOT;
        }
    }
    return change;
}