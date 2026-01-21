#include "clicked_rect.h"

bool clicked_in_rect(const Rectangle rect) {
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return false;

    const Vector2 mouse = GetMousePosition();
    return mouse.x >= rect.x
        && mouse.y >= rect.y
        && mouse.x <= rect.x + rect.width
        && mouse.y <= rect.y + rect.height;
}
