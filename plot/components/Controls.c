#include "Controls.h"

#include "../../text/Button.h"
#include "../../text/text.h"
#include "../../data/data_source.h"
#include "../../files/image_export.h"
#include "../../math/vector2.h"

move_change_t Controls(OpenFile* current_file, DataPlotState* state, move_change_t change) {
    if (IsKeyPressed(KEY_R)) {
        if (state->input_mode == PLOT_INPUT_REGRESSION)
            state->input_mode = PLOT_INPUT_IDLE;
        else
            state->input_mode = PLOT_INPUT_REGRESSION;
    }

    if (state->input_mode == PLOT_INPUT_REGRESSION) {
        Text("Wybierz punkty do regresji", 400, 10, 20, BROWN);
    }

    if (change & MOVE_CHANGE_APPLY_OFFSET) {
        data_apply_offset(&current_file->data_source, state->plot_offset);
        state->plot_offset = VECTOR2_ZERO;
    }

    if (Button((Vector2) {10, 50}, "Odwróć y", 16, 0) == BUTTON_STATE_CLICKED) {
        data_scale_y(&current_file->data_source, -1);
        change |= MOVE_CHANGE_PLOT;
    }

    if (Button((Vector2) {100, 50}, "Odwróć x", 16, 0) == BUTTON_STATE_CLICKED) {
        data_flip_x(&current_file->data_source);
        change |= MOVE_CHANGE_PLOT;
    }

    if (Button((Vector2) {10, 150}, "Zablokuj y", 16, 0) == BUTTON_STATE_CLICKED) {
        current_file->data_plot_state.movement_lock = MOVEMENT_LOCK_Y;
    }

    if (Button((Vector2) {100, 150}, "Zablokuj x", 16, 0) == BUTTON_STATE_CLICKED) {
        current_file->data_plot_state.movement_lock = MOVEMENT_LOCK_X;
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

    if (Button((Vector2) {1050, 550}, "Eksportuj CSV", 16, 0) == BUTTON_STATE_CLICKED) {
        file_export_csv(current_file);
    }

    if (Button((Vector2) {900, 550}, "Eksportuj PNG", 16, 0) == BUTTON_STATE_CLICKED) {
        image_export(current_file->data_source, "export.png");
    }

    if (Button((Vector2) {20, 400}, "Wykres σ = f(ε)", 16, 0) == BUTTON_STATE_CLICKED) {
        float x = 50; // pole przekroju
        float y = 100; // długość początkowa
        if (!current_file->data_plot_state.is_strain) {
            x = 1 / x;
            y = 1 / y;
            current_file->data_plot_state.x_label = "σ";
            current_file->data_plot_state.y_label = "ε";
        }
        else {
            current_file->data_plot_state.x_label = "Stroke [mm]";
            current_file->data_plot_state.y_label = "Load [kN]";
        }
        data_convert(&current_file->data_source, x, y);
        current_file->data_plot_state.is_strain = !current_file->data_plot_state.is_strain;
        current_file->data_plot_state.zoom /= x;
        current_file->data_plot_state.pan = (Vector2) {0, 0};
        change |= MOVE_CHANGE_PLOT;
    }

    return change;
}