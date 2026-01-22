#include "RegressionControls.h"

#include <stdio.h>

#include "BottomHelp.h"
#include "Polynomial.h"
#include "../input_mode.h"
#include "../../text/text.h"
#include "../../files/components/CloseButton.h"

move_change_t RegressionControls(RegressionControlProps props) {
    const button_state_t close_state = CloseButton((Vector2) {10, 10}, 16);
    if (close_state == BUTTON_STATE_CLICKED || IsKeyPressed(KEY_ESCAPE)) {
        set_input_mode(INPUT_MODE_IDLE);
        return props.change;
    }
    Text("Regresja", 60, 12, 26, BLACK);

    char degree_text[4];
    const int d = props.curve->order - 1;
    snprintf(degree_text, 4, "%d", d);

    Text("Stopień wielomianu", 8, 60, 16, BLACK);
    Text(degree_text, d > 9 ? 50 : 55, 83, 22, BLACK);

    if (ButtonDefault((Vector2){10, 80}, "<", 12, 0) == BUTTON_STATE_CLICKED && props.curve->order > 1) {
        props.curve->order--;
        props.change |= MOVE_CHANGE_POLYNOMIAL;
    }
    if (ButtonDefault((Vector2){80, 80}, ">", 12, 0) == BUTTON_STATE_CLICKED && props.curve->order < POLYNOMIAL_MAX_DEGREE) {
        props.curve->order++;
        props.change |= MOVE_CHANGE_POLYNOMIAL;
    }
    if (props.regression_point_count) {
        const button_state_t equation_button = ButtonDefault((Vector2){10, 120}, "Wzór", 16, 0);
        if (equation_button & BUTTON_STATE_HOVER) {
            TextBox((TextBoxProps) {
                .origin = {70, 120},
                .padding = {8, 8},
                .text = props.curve->equation,
                .font_size = 16,
                .text_color = BLACK,
                .background_color = {230,230,255,255},
                .border_color = BLACK,
                .border = 1,
            });
            const Color copy_color = props.curve->copied ? (Color){190,255,140,255} : (Color){230,230,255,255};
            TextBox((TextBoxProps) {
                .origin = {62, 160},
                .padding = {2, 2},
                .text = "Skopiuj",
                .font_size = 16,
                .text_color = BLACK,
                .background_color = copy_color,
                .border_color = BLACK,
                .border = 1,
                .align = TEXTBOX_ALIGN_RIGHT
            });
        }
        if (equation_button & BUTTON_STATE_CLICKED) {
            SetClipboardText(props.curve->equation);
            props.curve->copied = true;
        }
    }

    BottomHelp("Wybierz punkt początkowy i końcowy", 450);

    return props.change;
}
