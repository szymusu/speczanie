#include "Controls.h"

#include "LineSetZero.h"
#include "../../text/Button.h"
#include "../../text/text.h"
#include "../../data/data_source.h"
#include "../../files/image_export.h"
#include "../../math/vector2.h"

move_change_t Controls(ControlsProps props) {
    if (IsKeyPressed(KEY_R)) {
        if (props.current_file->data_plot_state.input_mode == PLOT_INPUT_REGRESSION)
            props.current_file->data_plot_state.input_mode = PLOT_INPUT_IDLE;
        else
            props.current_file->data_plot_state.input_mode = PLOT_INPUT_REGRESSION;
    }

    if (props.current_file->data_plot_state.input_mode == PLOT_INPUT_REGRESSION) {
        Text("Wybierz punkty do regresji", 400, 10, 20, BROWN);
    }

    if (props.change & MOVE_CHANGE_APPLY_OFFSET) {
        data_apply_offset(&props.current_file->data_source, props.current_file->data_plot_state.plot_offset);
        props.current_file->data_plot_state.plot_offset = VECTOR2_ZERO;
    }

    if (Button((Vector2) {10, 50}, "Odwróć y", 16, 0) == BUTTON_STATE_CLICKED) {
        data_scale_y(&props.current_file->data_source, -1);
        props.change |= MOVE_CHANGE_PLOT;
    }

    if (Button((Vector2) {100, 50}, "Odwróć x", 16, 0) == BUTTON_STATE_CLICKED) {
        data_flip_x(&props.current_file->data_source);
        props.change |= MOVE_CHANGE_PLOT;
    }

    const bool is_lock_y = props.current_file->data_plot_state.movement_lock == MOVEMENT_LOCK_Y;
    if (ButtonDefault((Vector2) {10, 150}, "Blokuj y", 16, is_lock_y & BUTTON_OPTION_ACTIVE) & BUTTON_STATE_CLICKED) {
        if (is_lock_y)  props.current_file->data_plot_state.movement_lock = MOVEMENT_LOCK_NONE;
        else            props.current_file->data_plot_state.movement_lock = MOVEMENT_LOCK_Y;
    }

    const bool is_lock_x = props.current_file->data_plot_state.movement_lock == MOVEMENT_LOCK_X;
    if (ButtonDefault((Vector2) {100, 150}, "Blokuj x", 16, is_lock_x & BUTTON_OPTION_ACTIVE) & BUTTON_STATE_CLICKED) {
        if (is_lock_x)  props.current_file->data_plot_state.movement_lock = MOVEMENT_LOCK_NONE;
        else            props.current_file->data_plot_state.movement_lock = MOVEMENT_LOCK_X;
    }

    if (!is_vec2_zero(props.current_file->data_source.data[0])) {
        if (Button((Vector2) {10, 100}, "Zeruj start", 16, 0) == BUTTON_STATE_CLICKED) {
            data_apply_offset(&props.current_file->data_source, (Vector2) {
                -props.current_file->data_source.data[0].x,
                props.current_file->data_source.data[0].y
            });
            props.current_file->data_plot_state.plot_offset = VECTOR2_ZERO;
            props.current_file->data_plot_state.pan = VECTOR2_ZERO;
            props.change |= MOVE_CHANGE_PLOT | MOVE_CHANGE_PAN;
        }
    }

    if (props.current_file->data_plot_state.selected_point > 0) {
        Text("Utnij", 10, 200, 16, BLACK);
        if (Button((Vector2) {70, 216}, "Lewo", 16, TEXTBOX_ALIGN_RIGHT) == BUTTON_STATE_CLICKED) {
            data_cut_left(&props.current_file->data_source, props.current_file->data_plot_state.selected_point);
            props.current_file->data_plot_state.selected_point = -1;
            props.change |= MOVE_CHANGE_PLOT;
        }
        if (Button((Vector2) {75, 216}, "Prawo", 16, 0) == BUTTON_STATE_CLICKED) {
            data_cut_right(&props.current_file->data_source, props.current_file->data_plot_state.selected_point);
            props.current_file->data_plot_state.selected_point = -1;
            props.change |= MOVE_CHANGE_PLOT;
        }
    }

    if (Button((Vector2) {1050, 550}, "Eksportuj CSV", 16, 0) == BUTTON_STATE_CLICKED) {
        file_export_csv(props.current_file);
    }

    if (Button((Vector2) {900, 550}, "Eksportuj PNG", 16, 0) == BUTTON_STATE_CLICKED) {
        image_export(props.current_file->data_source, "export.png");
    }

    if (Button((Vector2) {20, 400}, "Wykres σ = f(ε)", 16, 0) == BUTTON_STATE_CLICKED) {
        // float x = 50; // pole przekroju
        // float y = 100; // długość początkowa
        // if (!current_file->data_plot_state.is_strain) {
        //     x = 1 / x;
        //     y = 1 / y;
        //     current_file->data_plot_state.x_label = "σ";
        //     current_file->data_plot_state.y_label = "ε";
        // }
        // else {
        //     current_file->data_plot_state.x_label = "Stroke [mm]";
        //     current_file->data_plot_state.y_label = "Load [kN]";
        // }
        // data_convert(&current_file->data_source, x, y);
        // current_file->data_plot_state.is_strain = !current_file->data_plot_state.is_strain;
        // current_file->data_plot_state.zoom /= x;
        // current_file->data_plot_state.pan = (Vector2) {0, 0};

        props.multi_plot_state->enabled = !props.multi_plot_state->enabled;
        props.multi_plot_state->pan = props.current_file->data_plot_state.pan;
        props.multi_plot_state->scale_x = props.current_file->data_plot_state.scale_x;
        props.multi_plot_state->zoom = props.current_file->data_plot_state.zoom;
        props.change |= MOVE_CHANGE_PLOT;
    }

    const bool line_ready = props.current_file->data_plot_state.curve_linear.a && props.current_file->data_plot_state.input_mode != PLOT_INPUT_SELECT;
    if (line_ready) {
        const float applied_x = LineSetZero(props.current_file->data_plot_state.curve_linear, props.bounds);
        if (applied_x != 0) {
            data_apply_offset(&props.current_file->data_source, (Vector2) { -applied_x, 0 });
            props.current_file->data_plot_state.plot_offset = VECTOR2_ZERO;
            props.current_file->data_plot_state.pan = VECTOR2_ZERO;
            props.change |= MOVE_CHANGE_PLOT | MOVE_CHANGE_PAN;

            props.current_file->data_plot_state.curve_linear.b = 0;
            props.current_file->data_plot_state.curve_linear.end_point.x = 0;
        }
    }

    return props.change;
}