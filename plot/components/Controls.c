#include "Controls.h"

#include "LineSetZero.h"
#include "../../text/Button.h"
#include "../../text/text.h"
#include "../../data/data_source.h"
#include "../../files/image_export.h"
#include "../../math/vector2.h"

void point_index_flip(int* index, const int count) {
    if (*index == -1) return;
    *index = count - *index - 1;
}

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
        props.current_file->data_plot_state.curve_linear.end_point.y *= -1;
        props.change |= MOVE_CHANGE_PLOT;
    }

    if (Button((Vector2) {100, 50}, "Odwróć x", 16, 0) == BUTTON_STATE_CLICKED) {
        data_flip_x(&props.current_file->data_source);
        const int count = props.current_file->data_source.count;
        point_index_flip(&props.current_file->data_plot_state.selected_point, count);
        point_index_flip(&props.current_file->data_plot_state.selected_second_point, count);
        point_index_flip(&props.current_file->data_plot_state.curve_linear.end_point_index, count);
        props.current_file->data_plot_state.curve_linear.end_point.x *= -1;

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
            data_operation_do(
                &props.current_file->data_source,
                &props.current_file->data_plot_state.operation_stack,
                (DataOperation) {
                    .op = { .cut_left = {.index = props.current_file->data_plot_state.selected_point} },
                    .type = OP_CUT_LEFT
                });
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

            const int cut_index = props.current_file->data_plot_state.curve_linear.end_point_index;
            if (cut_index != 0 && cut_index != props.current_file->data_source.count) {
                if (props.current_file->data_plot_state.curve_linear.end_point.x > 0) {
                    data_cut_left(&props.current_file->data_source, cut_index - 1);
                    data_replace(&props.current_file->data_source, 0, VECTOR2_ZERO);
                }
                else {
                    data_cut_right(&props.current_file->data_source, cut_index + 1);
                    data_replace(&props.current_file->data_source, cut_index + 1, VECTOR2_ZERO);
                }
            }
            props.current_file->data_plot_state.curve_linear = (CurveLinear) {0};
            props.current_file->data_plot_state.selected_point = -1;
            props.current_file->data_plot_state.selected_second_point = -1;
        }
    }

    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_Z)) {
        data_operation_undo(&props.current_file->data_source, &props.current_file->data_plot_state.operation_stack);
        props.change |= MOVE_CHANGE_PLOT;
    }

    return props.change;
}