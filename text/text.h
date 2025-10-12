#ifndef TEXT_H
#define TEXT_H

#include <raylib.h>
void font_init(const char* file_name);
void font_unload();
void Text(const char* text, int posX, int posY, int fontSize, Color color);
void TextV(const char* text, Vector2 pos, float fontSize, Color color);

#endif //TEXT_H
