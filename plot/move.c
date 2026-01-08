#include "move.h"

#include "../util/vector2.h"

// #define ZOOM_SPEED .01f
#define ZOOM_SPEED .08f

move_change_t process_move(DataPlotState* state, const Bounds bounds) {
    move_change_t change = 0;
    const float wheel_change = GetMouseWheelMove();
    if (wheel_change != 0.f) {
        change |= MOVE_CHANGE_ZOOM;
        state->zoom += wheel_change * ZOOM_SPEED * state->zoom;
        if (state->zoom <= 0.1f) state->zoom = 0.1f;
    }

    const Vector2 mouse_delta = GetMouseDelta();
    const bool no_delta = is_vec2_zero(mouse_delta);
    const Vector2 plot_delta = no_delta ? VECTOR2_ZERO : (Vector2) {
        .x = mouse_delta.x * (bounds.end_x - bounds.start_x) / PLOT_WIDTH,
        .y = mouse_delta.y * (bounds.end_y - bounds.start_y) / PLOT_HEIGHT
    };

    const bool is_moving_plot = !is_vec2_zero(state->plot_offset);
    if (is_moving_plot) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            change |= MOVE_CHANGE_APPLY_OFFSET + MOVE_CHANGE_PLOT;
        }
        else if (IsKeyReleased(KEY_LEFT_CONTROL)) {
            change |= MOVE_CHANGE_PLOT;
            state->plot_offset = VECTOR2_ZERO;
        }
        else if (!no_delta || 1) {
            change |= MOVE_CHANGE_PLOT;
            state->plot_offset.x += plot_delta.x;
            state->plot_offset.y += plot_delta.y;
        }
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (no_delta) return change;

        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            change |= MOVE_CHANGE_PLOT;
            state->plot_offset.x += plot_delta.x;
            state->plot_offset.y += plot_delta.y;
        }
        else {
            change |= MOVE_CHANGE_PAN;
            state->pan.x -= plot_delta.x;
            state->pan.y -= plot_delta.y;
        }
    }
    return change;
}
