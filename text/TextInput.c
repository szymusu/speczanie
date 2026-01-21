#include "TextInput.h"

#include <raylib.h>

#include "text.h"
#include "../util/clicked_rect.h"

#define PADDING 5
#define FONT_SIZE 20

text_change_t TextInput(const float x, const float y, char* buffer, int* len, const int max_len, const bool is_focused) {
    text_change_t change = TEXT_CHANGE_NONE;

    const Rectangle rect = { x, y, (FONT_SIZE * (max_len + 1) + 2 * PADDING) * .5f, PADDING + PADDING + FONT_SIZE };
    DrawRectangleRec(rect, WHITE);
    Text(buffer, x + PADDING, y + PADDING, FONT_SIZE, BLACK);

    if (!is_focused) {
        DrawRectangleLinesEx(rect, 1, BLACK);
        buffer[*len] = 0;
        if (clicked_in_rect(rect)) return TEXT_CHANGE_FOCUS;
        return change;
    }

    DrawRectangleLinesEx(rect, 2, DARKBLUE);

    const char c = (char) GetCharPressed();
    if (c) {
        if (c >= '0' && c <= '9' && *len < max_len) {
            buffer[(*len)++] = c;
            change |= TEXT_CHANGE_INPUT;
        }
        else if (c == ',' || c == '.') {
            buffer[(*len)++] = '.';
            change |= TEXT_CHANGE_INPUT;
        }
    }
    else if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && *len > 0) {
        buffer[(*len)--] = 0;
        buffer[*len] = '_';
        change |= TEXT_CHANGE_INPUT;
    }
    else if (IsKeyPressed(KEY_TAB)) {
        change |= TEXT_CHANGE_UNFOCUS;
    }

    if (*len < max_len) buffer[*len] = '_';

    return change;
}
