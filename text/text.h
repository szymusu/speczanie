#ifndef TEXT_H
#define TEXT_H

#include <raylib.h>

Font* get_font();
void font_init(const char* file_name);
void font_unload();
void Text(const char* text, float posX, float posY, float fontSize, Color color);
void TextV(const char* text, Vector2 pos, float fontSize, Color color);
Vector2 FontMeasureText(const char* text, const float fontSize);

#endif //TEXT_H
