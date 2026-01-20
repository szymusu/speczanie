#include "RegressionControls.h"

#include <stdio.h>

#include "Polynomial.h"
#include "../input_mode.h"
#include "../../text/text.h"
#include "../../files/components/CloseButton.h"
#include "../../util/format_polynomial.h"


move_change_t RegressionControls(RegressionControlProps props) {
    const button_state_t close_state = CloseButton((Vector2) {10, 10}, 16);
    if (close_state == BUTTON_STATE_CLICKED || IsKeyPressed(KEY_ESCAPE)) {
        set_input_mode(INPUT_MODE_IDLE);
        return props.change;
    }
    Text("Regresja", 60, 12, 26, BLACK);

    char degree_text[32];
    sprintf(degree_text, "Stopień wielomianu: %d", props.curve->order - 1);
    Text(degree_text, 10, 45, 20, BLACK);

    if (ButtonDefault((Vector2){10, 80}, "<", 16, 0) == BUTTON_STATE_CLICKED && props.curve->order > 1) {
        props.curve->order--;
        props.change |= MOVE_CHANGE_POLYNOMIAL;
    }
    if (ButtonDefault((Vector2){60, 80}, ">", 16, 0) == BUTTON_STATE_CLICKED && props.curve->order < POLYNOMIAL_MAX_DEGREE) {
        props.curve->order++;
        props.change |= MOVE_CHANGE_POLYNOMIAL;
    }
    if (ButtonDefault((Vector2){10, 120}, "f(x)", 16, 0) == BUTTON_STATE_CLICKED) {
        if (props.regression_point_count) {
            format_polynomial(props.curve->equation, 255, props.curve);
        }
        else {
            props.curve->equation[0] = '-';
            props.curve->equation[1] = 0;
        }
    }
    Text(props.curve->equation, 70, 128, 16, BLACK);

    return props.change;
}
