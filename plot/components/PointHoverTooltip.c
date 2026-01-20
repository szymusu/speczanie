#include "PointHoverTooltip.h"

#include <stdio.h>

#include "../../text/text.h"
#include "../../text/TextBox.h"

int find_hover_point(const Vector2* points, const int count) {
    const Vector2 mouse = GetMousePosition();
    for (int i = 0; i < count; ++i) {
        const float diff_x = mouse.x - points[i].x;
        const float diff_y = mouse.y - points[i].y;
        if (diff_x*diff_x + diff_y*diff_y < 100) {
            return i;
        }
    }
    return -1;
}

int PointHoverTooltip(const PointHoverTooltipProps props) {
    const int hover_index = find_hover_point(props.points, props.visible.count);
    if (hover_index == -1) return -1;

    const int hover_absolute_index = hover_index + props.visible.start;

    const Vector2 data_point = props.data[hover_absolute_index];
    const Vector2 pixel_point = props.points[hover_index];
    DrawCircleV(pixel_point, 6.f, props.color);

    char text[32];
    sprintf(text, "x: %.3f\ny: %.3f", data_point.x, data_point.y);
    TextBox((TextBoxProps) {
        .text = text,
        .font_size = 15,
        .origin = {pixel_point.x + 5, pixel_point.y - 5},
        .padding = {5, 2},
        .align = TEXTBOX_ALIGN_BOTTOM,
        .background_color = WHITE,
        .border_color = props.color,
        .border = 1,
        .text_color = BLACK
    });
    return hover_absolute_index;
}