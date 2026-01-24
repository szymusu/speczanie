#include "move.h"

#include "input_mode.h"
#include "../math/vector2.h"
#include "plot_math.h"

#define ZOOM_SPEED .08f
#define MIN_ZOOM .002f

move_change_t process_move(const MoveProps props) {
    move_change_t change = 0;
    const float wheel_change = GetMouseWheelMove();
    if (wheel_change != 0.f) {
        change |= MOVE_CHANGE_ZOOM;
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            props.view_move->scale_x += wheel_change * ZOOM_SPEED * props.view_move->scale_x;
            if (props.view_move->scale_x <= 1.f) props.view_move->scale_x = 1.f;
        }
        else {
            props.view_move->zoom += wheel_change * ZOOM_SPEED * props.view_move->zoom;
            if (props.view_move->zoom <= MIN_ZOOM) props.view_move->zoom = MIN_ZOOM;
        }
    }

    const Vector2 mouse_delta = GetMouseDelta();
    const bool no_delta = is_vec2_zero(mouse_delta);
    const Vector2 plot_delta = no_delta ? VECTOR2_ZERO : (Vector2) {
        .x = mouse_delta.x * (props.bounds.end_x - props.bounds.start_x) / PLOT_WIDTH,
        .y = mouse_delta.y * (props.bounds.end_y - props.bounds.start_y) / PLOT_HEIGHT
    };

    switch (get_input_mode()) {

    case INPUT_MODE_IDLE:
    case INPUT_MODE_REGRESSION: {
        if (no_delta || IsMouseButtonUp(MOUSE_BUTTON_LEFT)) break;

        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            change |= MOVE_CHANGE_PLOT;
            set_input_mode(INPUT_MODE_MOVE);
        }
        else {
            change |= MOVE_CHANGE_PAN;
            props.view_move->pan.x -= plot_delta.x;
            props.view_move->pan.y -= plot_delta.y;
        }
        break;
    }
    case INPUT_MODE_MOVE: {
        if (!props.plot_move) break;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            set_input_mode(INPUT_MODE_IDLE);
            change |= MOVE_CHANGE_APPLY_OFFSET + MOVE_CHANGE_PLOT;
        }
        else if (IsKeyReleased(KEY_LEFT_CONTROL)) {
            set_input_mode(INPUT_MODE_IDLE);
            change |= MOVE_CHANGE_PLOT;
            props.plot_move->plot_offset = VECTOR2_ZERO;
        }
        else if (!no_delta || 1) {
            change |= MOVE_CHANGE_PLOT;
            if (props.plot_move->movement_lock != MOVEMENT_LOCK_X) props.plot_move->plot_offset.x += plot_delta.x;
            if (props.plot_move->movement_lock != MOVEMENT_LOCK_Y) props.plot_move->plot_offset.y += plot_delta.y;
        }
        break;
    }
    case INPUT_MODE_SELECT: {
        props.view_move->mouse_position = GetMousePosition();
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            set_input_mode(INPUT_MODE_IDLE);
        }
        break;
    }
    case INPUT_MODE_TEXT:
        break;
    }

    return change;
}
