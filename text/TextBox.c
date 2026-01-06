#include "TextBox.h"

#include "text.h"

Rectangle box_get_rect(const TextBoxProps props) {
    const Vector2 text_size = FontMeasureText(props.text, props.font_size);
    const float padded_width = text_size.x + 2 * props.padding.x;
    const float padded_height = text_size.y + 2 * props.padding.y;
    const float start_x = props.origin.x - (props.align & TEXTBOX_ALIGN_RIGHT ? padded_width : 0);
    const float start_y = props.origin.y - (props.align & TEXTBOX_ALIGN_BOTTOM ? padded_height : 0);
    return (Rectangle) {start_x, start_y, padded_width, padded_height};
}

void DrawTextBox(const TextBoxProps props, const Rectangle box) {
    DrawRectangleRec(box, props.background_color);
    DrawRectangleLinesEx(box, props.border, props.border_color);
    Text(props.text, box.x + props.padding.x, box.y + props.padding.y, props.font_size, props.text_color);
}

Rectangle TextBox(const TextBoxProps props) {
    const Rectangle text_box = box_get_rect(props);
    DrawTextBox(props, text_box);
    return text_box;
}
