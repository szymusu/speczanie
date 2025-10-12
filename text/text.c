#include "text.h"

#include <stdio.h>

Font default_font;

void font_init(const char* file_name) {
    default_font = LoadFont(file_name);
    if (!IsFontValid(default_font)) {
        printf("Font %s couldn't load!\n", file_name);
        default_font = GetFontDefault();
    }
}

void font_unload() {
    UnloadFont(default_font);
}

void Text(const char* text, const int posX, const int posY, const int fontSize, const Color color) {
    DrawTextEx(default_font, text, (Vector2) {posX, posY}, fontSize, 0, color);
}

void TextV(const char* text, const Vector2 pos, const float fontSize, const Color color) {
    DrawTextEx(default_font, text, pos, fontSize, 1, color);
}