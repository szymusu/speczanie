#include "RegressionControls.h"

#include "../../text/text.h"
#include "../../files/components/CloseButton.h"


void RegressionControls(enum PlotInputMode* input_mode) {
    const button_state_t close_state = CloseButton((Vector2) {10, 10}, 16);
    if (close_state == BUTTON_STATE_CLICKED) {
        *input_mode = PLOT_INPUT_IDLE;
        return;
    }
    Text("Regresja", 60, 12, 26, BLACK);
}
