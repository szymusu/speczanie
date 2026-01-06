#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <raylib.h>

#define TEXTBOX_ALIGN_BOTTOM 1
#define TEXTBOX_ALIGN_RIGHT 2
typedef unsigned char textbox_align_t;

typedef struct {
    Vector2 origin;
    Vector2 padding;
    const char* text;
    float font_size;
    Color text_color;
    Color background_color;
    Color border_color;
    float border;
    textbox_align_t align;

} TextBoxProps;

Rectangle box_get_rect(TextBoxProps props);
void DrawTextBox(TextBoxProps props, Rectangle box);
Rectangle TextBox(TextBoxProps props);

#endif //TEXTBOX_H
