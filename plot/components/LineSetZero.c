#include "LineSetZero.h"

#include "../../text/TextBox.h"
#include "../../math/vector2.h"
#include "../plot_math.h"

float LineSetZero(const CurveLinear curve_linear, const Bounds bounds) {
    const Vector2 p0 = { -curve_linear.b / curve_linear.a, 0 };
    const Vector2 p0_pixel = transform_v_to_pixel(p0, bounds);
    if (vec2_magnitude(vec2_subtract(p0_pixel, GetMousePosition())) < 20) {
        DrawCircleV(p0_pixel, 10, LIME);
        TextBox((TextBoxProps) {
            .text = "Wyzeruj",
            .font_size = 20,
            .origin = {p0_pixel.x - 30, p0_pixel.y - 10},
            .padding = {5, 2},
            .align = TEXTBOX_ALIGN_BOTTOM,
            .background_color = WHITE,
            .border_color = LIME,
            .border = 2,
            .text_color = DARKGREEN
        });
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            return p0.x;
        }
    }
    else {
        DrawCircleV(p0_pixel, 5, LIME);
    }
    return 0;
}
