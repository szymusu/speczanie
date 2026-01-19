#include "RegressionControls.h"

#include <stdio.h>

#include "Polynomial.h"
#include "../../text/text.h"
#include "../../files/components/CloseButton.h"


move_change_t RegressionControls(CurvePolynomial* curve, enum PlotInputMode* input_mode, move_change_t change) {
    const button_state_t close_state = CloseButton((Vector2) {10, 10}, 16);
    if (close_state == BUTTON_STATE_CLICKED) {
        *input_mode = PLOT_INPUT_IDLE;
        return change;
    }
    Text("Regresja", 60, 12, 26, BLACK);

    char degree_text[32];
    sprintf(degree_text, "Stopień wielomianu: %d", curve->order - 1);
    Text(degree_text, 10, 45, 20, BLACK);

    if (ButtonDefault((Vector2){10, 80}, "<", 16, 0) == BUTTON_STATE_CLICKED && curve->order > 1) {
        curve->order--;
        change |= MOVE_CHANGE_POLYNOMIAL;
    }
    if (ButtonDefault((Vector2){60, 80}, ">", 16, 0) == BUTTON_STATE_CLICKED && curve->order < POLYNOMIAL_MAX_DEGREE) {
        curve->order++;
        change |= MOVE_CHANGE_POLYNOMIAL;
    }
    return change;
}
