#include "Controls.h"

#include "BottomHelp.h"
#include "LineSetZero.h"
#include "../input_mode.h"
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
    if (props.change & MOVE_CHANGE_APPLY_OFFSET) {
        data_operation_do(
            &props.current_file->data_source,
            &props.current_file->data_plot_state.operation_stack,
            (DataOperation) {
                .type = OP_OFFSET,
                .op = { .offset = { .offset = props.current_file->data_plot_state.plot_move.plot_offset } }
            }
            );
        props.current_file->data_plot_state.plot_move.plot_offset = VECTOR2_ZERO;
    }


    if (ButtonDefault((Vector2) {10, 10}, "Wykres σ = f(ε)", 16, 0) == BUTTON_STATE_CLICKED) {
        const bool enabled = props.multi_plot_state->enabled;
        if (enabled) {
            props.current_file->data_plot_state.view_move = MultiPlot_disable(props.multi_plot_state);
        }
        else {
            MultiPlot_enable(props.multi_plot_state, props.current_file->data_plot_state.view_move);
        }
        props.change |= MOVE_CHANGE_PLOT;
    }
    if (ButtonDefault((Vector2) {150, 10}, "Regresja", 16, 0) == BUTTON_STATE_CLICKED) {
        set_input_mode(INPUT_MODE_REGRESSION);
        props.current_file->data_plot_state.regression_points_count = 0;
        props.current_file->data_plot_state.selected_point = -1;
        props.current_file->data_plot_state.selected_second_point = -1;
    }


    if (ButtonDefault((Vector2) {10, 52}, "Wyeruj start", 16, is_vec2_zero(props.current_file->data_source.data[0]) * BUTTON_OPTION_DISABLED) == BUTTON_STATE_CLICKED) {
        data_operation_do(
            &props.current_file->data_source,
            &props.current_file->data_plot_state.operation_stack,
            (DataOperation) {
                .type = OP_OFFSET,
                .op = { .offset = { .offset = {
                    .x = -props.current_file->data_source.data[0].x,
                    .y = props.current_file->data_source.data[0].y
                } } }
            }
            );
        props.current_file->data_plot_state.plot_move.plot_offset = VECTOR2_ZERO;
        props.current_file->data_plot_state.view_move.pan = VECTOR2_ZERO;
        props.change |= MOVE_CHANGE_PLOT | MOVE_CHANGE_PAN;
    }


    Text("Odwróć współrzędne", 10, 89, 16, BLACK);
    if (ButtonDefault((Vector2) {10, 106}, " X ", 16, 0) == BUTTON_STATE_CLICKED) {
        data_operation_do(
            &props.current_file->data_source,
            &props.current_file->data_plot_state.operation_stack,
            (DataOperation) { .type = OP_FLIP_X }
            );

        const int count = props.current_file->data_source.count;
        point_index_flip(&props.current_file->data_plot_state.selected_point, count);
        point_index_flip(&props.current_file->data_plot_state.selected_second_point, count);
        point_index_flip(&props.current_file->data_plot_state.curve_linear.end_point_index, count);
        props.current_file->data_plot_state.curve_linear.end_point.x *= -1;
        props.change |= MOVE_CHANGE_PLOT;
    }
    if (ButtonDefault((Vector2) {64, 106}, " Y ", 16, 0) == BUTTON_STATE_CLICKED) {
        data_operation_do(
            &props.current_file->data_source,
            &props.current_file->data_plot_state.operation_stack,
            (DataOperation) { .type = OP_FLIP_Y }
            );
        props.current_file->data_plot_state.curve_linear.end_point.y *= -1;
        props.change |= MOVE_CHANGE_PLOT;
    }


    Text("Zablokuj oś", 10, 143, 16, BLACK);
    const bool is_lock_x = props.current_file->data_plot_state.plot_move.movement_lock == MOVEMENT_LOCK_X;
    if (ButtonDefault((Vector2) {10, 160}, " X ", 16, is_lock_x & BUTTON_OPTION_ACTIVE) & BUTTON_STATE_CLICKED) {
        if (is_lock_x)  props.current_file->data_plot_state.plot_move.movement_lock = MOVEMENT_LOCK_NONE;
        else            props.current_file->data_plot_state.plot_move.movement_lock = MOVEMENT_LOCK_X;
    }
    const bool is_lock_y = props.current_file->data_plot_state.plot_move.movement_lock == MOVEMENT_LOCK_Y;
    if (ButtonDefault((Vector2) {64, 160}, " Y ", 16, is_lock_y & BUTTON_OPTION_ACTIVE) & BUTTON_STATE_CLICKED) {
        if (is_lock_y)  props.current_file->data_plot_state.plot_move.movement_lock = MOVEMENT_LOCK_NONE;
        else            props.current_file->data_plot_state.plot_move.movement_lock = MOVEMENT_LOCK_Y;
    }


    const int selected = props.current_file->data_plot_state.selected_point;
    Text("Utnij", 10, 197, 16, BLACK);
    if (ButtonDefault((Vector2) {10, 214}, "Lewo", 16, BUTTON_OPTION_DISABLED * (selected <= 0)) == BUTTON_STATE_CLICKED) {
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
    if (ButtonDefault((Vector2) {75, 214}, "Prawo", 16, BUTTON_OPTION_DISABLED * (selected <= 1)) == BUTTON_STATE_CLICKED) {
        data_operation_do(
            &props.current_file->data_source,
            &props.current_file->data_plot_state.operation_stack,
            (DataOperation) {
                .op = { .cut_right = {.index = props.current_file->data_plot_state.selected_point} },
                .type = OP_CUT_RIGHT
            });
        props.current_file->data_plot_state.selected_point = -1;
        props.change |= MOVE_CHANGE_PLOT;
    }

    if (ButtonDefault((Vector2) {1050, 550}, "Eksportuj CSV", 16, 0) == BUTTON_STATE_CLICKED) {
        file_export_csv(props.current_file);
    }

    if (ButtonDefault((Vector2) {900, 550}, "Eksportuj PNG", 16, 0) == BUTTON_STATE_CLICKED) {
        image_export(props.current_file->data_source, "export.png");
    }

    const bool line_ready = props.current_file->data_plot_state.curve_linear.a && !is_input_mode(INPUT_MODE_SELECT);
    if (line_ready) {
        const float applied_x = LineSetZero(props.current_file->data_plot_state.curve_linear, props.bounds);
        if (applied_x != 0) {
            data_operation_do(
                &props.current_file->data_source,
                &props.current_file->data_plot_state.operation_stack,
                (DataOperation) {
                    .type = OP_OFFSET,
                    .op = { .offset = { .offset = {
                        .x = -applied_x,
                        .y = 0
                    } } }
                }
                );

            props.current_file->data_plot_state.plot_move.plot_offset = VECTOR2_ZERO;
            props.current_file->data_plot_state.view_move.pan = VECTOR2_ZERO;
            props.change |= MOVE_CHANGE_PLOT | MOVE_CHANGE_PAN;

            props.current_file->data_plot_state.curve_linear.b = 0;

            const int cut_index = props.current_file->data_plot_state.curve_linear.end_point_index;
            if (cut_index != 0 && cut_index != props.current_file->data_source.count) {
                DataOperation cut_operation;
                DataOperation replace_operation = { .type = OP_REPLACE, .op = { .replace = { .point = VECTOR2_ZERO } } };

                if (props.current_file->data_plot_state.curve_linear.end_point.x > 0) {
                    replace_operation.op.replace.index = 0;
                    cut_operation.type = OP_CUT_LEFT;
                    cut_operation.op.cut_left.index = cut_index - 1;
                }
                else {
                    replace_operation.op.replace.index = cut_index + 1;
                    cut_operation.type = OP_CUT_RIGHT;
                    cut_operation.op.cut_right.index = cut_index + 1;
                }
                data_operation_do(
                    &props.current_file->data_source,
                    &props.current_file->data_plot_state.operation_stack,
                    cut_operation
                    );
                data_operation_do(
                    &props.current_file->data_source,
                    &props.current_file->data_plot_state.operation_stack,
                    replace_operation
                    );
            }
            props.current_file->data_plot_state.curve_linear = (CurveLinear) {0};
            props.current_file->data_plot_state.selected_point = -1;
            props.current_file->data_plot_state.selected_second_point = -1;
        }
    }

    if (IsKeyDown(KEY_LEFT_CONTROL) && (IsKeyPressed(KEY_Z) || IsKeyPressedRepeat(KEY_Z))) {
        data_operation_undo(&props.current_file->data_source, &props.current_file->data_plot_state.operation_stack);
        props.change |= MOVE_CHANGE_PLOT;
    }

    BottomHelp("CTRL + Z -> Cofnij | CTRL + Mysz -> Przesuń | SHIFT + Scroll -> Skaluj oś X", 240);

    return props.change;
}