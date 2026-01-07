#include "text.h"

#include <stdio.h>
#include <stdlib.h>

const unsigned char font_bytes[] = {
#embed "../resources/JetBrainsMono-SemiBold.ttf"
};

Font default_font;

Font* get_font() {
    return &default_font;
}

void font_init(const char* file_name) {
    constexpr size_t font_size = sizeof font_bytes;
    printf("font byte size %lu\n", font_size);
    if (!font_size) {
        puts("Font did not embed!");
        exit(1);
    }

    default_font = LoadFontFromMemory(".ttf", font_bytes, sizeof font_bytes, 32, nullptr, 250);

    if (!IsFontValid(default_font)) {
        printf("Font %s couldn't load!\n", file_name);
        default_font = GetFontDefault();
    }
}

void font_unload() {
    UnloadFont(default_font);
}

void Text(const char* text, const float posX, const float posY, const float fontSize, const Color color) {
    DrawTextEx(default_font, text, (Vector2) {posX, posY}, fontSize, 0, color);
}

void TextV(const char* text, const Vector2 pos, const float fontSize, const Color color) {
    DrawTextEx(default_font, text, pos, fontSize, 0, color);
}

Vector2 FontMeasureText(const char* text, const float fontSize) {
    return MeasureTextEx(default_font, text, fontSize, 0);
}