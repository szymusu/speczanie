#include "Button.h"

#include "text.h"

bool is_mouse_over(const Rectangle box) {
    const Vector2 mouse = GetMousePosition();
    return mouse.x >= box.x && mouse.x <= box.x + box.width
        && mouse.y >= box.y && mouse.y <= box.y + box.height;
}

button_state_t Button(const TextBoxProps idle_props, const TextBoxProps hover_props) {
    const Rectangle box = box_get_rect(idle_props);
    if (is_mouse_over(box)) {
        // SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
        DrawTextBox(hover_props, box);
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            return BUTTON_STATE_CLICKED;
        }
        return BUTTON_STATE_HOVER;
    }
    // SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    DrawTextBox(idle_props, box);
    return BUTTON_STATE_IDLE;
}
