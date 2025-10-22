#include "TextBox.h"

#include "text.h"

void TextBox(const TextBoxProps props) {
    const Vector2 text_size = FontMeasureText(props.text, props.font_size);
    const float padded_width = text_size.x + 2 * props.padding.x;
    const float padded_height = text_size.y + 2 * props.padding.y;
    const float start_x = props.origin.x + props.offset.x - (props.align & TEXTBOX_ALIGN_RIGHT ? padded_width : 0);
    const float start_y = props.origin.y + props.offset.y - (props.align & TEXTBOX_ALIGN_BOTTOM ? padded_height : 0);
    const Rectangle text_box = {start_x, start_y, padded_width, padded_height};

    DrawRectangleRec(text_box, WHITE);
    DrawRectangleLinesEx(text_box, 1, DARKBLUE);
    Text(props.text, text_box.x + props.padding.x, text_box.y + props.padding.y, props.font_size, BLACK);
}
