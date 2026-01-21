#include "BottomHelp.h"

#include "../plot_math.h"
#include "../../text/TextBox.h"

#define FONT_SIZE 18

void BottomHelp(const char* text, const float left) {
    TextBox((TextBoxProps) {
        .origin = {left, PLOT_HEIGHT},
        .padding = 15,
        .text = text,
        .font_size = FONT_SIZE,
        .text_color = BLACK,
        .background_color = WHITE,
        .border_color = LIGHTGRAY,
        .border = 1,
        .align = TEXTBOX_ALIGN_BOTTOM
    });
}
