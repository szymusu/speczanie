#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <raylib.h>

#define TEXTBOX_ALIGN_BOTTOM 1
#define TEXTBOX_ALIGN_RIGHT 2
typedef unsigned char textbox_align_t;

typedef struct {
    Vector2 origin;
    Vector2 padding;
    Vector2 offset;
    const char* text;
    float font_size;
    textbox_align_t align;

} TextBoxProps;

void TextBox(TextBoxProps props);

#endif //TEXTBOX_H
