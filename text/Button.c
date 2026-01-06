#include "Button.h"

#include "text.h"

bool is_mouse_over(const Rectangle box) {
    const Vector2 mouse = GetMousePosition();
    return mouse.x >= box.x && mouse.x <= box.x + box.width
        && mouse.y >= box.y && mouse.y <= box.y + box.height;
}

button_state_t ButtonPro(const TextBoxProps idle_props, const TextBoxProps hover_props) {
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

button_state_t Button(const Vector2 origin, const char* text, const float font_size, const textbox_align_t align) {
    const TextBoxProps props = {
        .origin = origin,
        .padding = {font_size, font_size / 2},
        .text = text,
        .font_size = font_size,
        .align = align,
        .border = 1,
        .background_color = RAYWHITE,
        .border_color = DARKBLUE,
        .text_color = BLACK
    };
    const Rectangle box = box_get_rect(props);
    DrawTextBox(props, box);
    if (is_mouse_over(box)) {
        DrawRectangleRec(box, (Color) {0, 0, 0, 32});
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            return BUTTON_STATE_CLICKED;
        }
        return BUTTON_STATE_HOVER;
    }
    return BUTTON_STATE_IDLE;
}
