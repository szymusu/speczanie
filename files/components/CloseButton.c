#include "CloseButton.h"

#include "../../plot/plot_math.h"

button_state_t CloseButton(const Vector2 origin, const float font_size) {
    return ButtonPro((TextBoxProps) {
            .origin = origin,
            .padding = {font_size, font_size / 2 - .5f},
            .text = "x",
            .font_size = font_size,
            .background_color = { 220, 170, 170, 255 },
            .text_color = BLACK,
        },
        (TextBoxProps) {
            .origin = origin,
            .padding = {font_size, font_size / 2 - .5f},
            .text = "x",
            .font_size = font_size,
            .background_color = { 220, 150, 150, 255 },
            .border_color = { 220, 80, 80, 255 },
            .text_color = BLACK,
            .border = 6,
        }
    );
}
