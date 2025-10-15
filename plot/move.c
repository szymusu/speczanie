#include "move.h"

move_change_t process_move(MoveState* state, const Bounds bounds) {
    move_change_t change = 0;
    const float wheel_change = GetMouseWheelMove();
    if (wheel_change != 0.f) {
        change |= 1;
        state->zoom += wheel_change * 0.1f;
        if (state->zoom <= 0.1f) state->zoom = 0.1f;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        const Vector2 delta = GetMouseDelta();
        if (delta.x != 0.f || delta.y != 0.f) {
            change |= 2;
            state->pan.x -= delta.x * (bounds.end_x - bounds.start_x) / PLOT_WIDTH;
            state->pan.y -= delta.y * (bounds.end_y - bounds.start_y) / PLOT_HEIGHT;
        }
    }
    return change;
}
