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

void PointHoverTooltip(const PointHoverTooltipProps props) {
    const Vector2 data_point = props.data[props.index + props.visible.start];
    const Vector2 pixel_point = props.points[props.index];
    DrawCircleV(pixel_point, 6.f, DARKBLUE);

    char text[32];
    sprintf(text, "x: %.3f\ny: %.3f", data_point.x, data_point.y);
    TextBox((TextBoxProps) {
        .text = text,
        .font_size = 15,
        .origin = {pixel_point.x + 5, pixel_point.y - 5},
        .padding = {5, 2},
        .align = TEXTBOX_ALIGN_BOTTOM,
        .background_color = WHITE,
        .border_color = BLUE,
        .border = 1,
        .text_color = BLACK
    });
}