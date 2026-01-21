#include "MultiControls.h"

#include "BottomHelp.h"
#include "../input_mode.h"
#include "../../text/text.h"
#include "../../files/components/CloseButton.h"

move_change_t MultiControls(MultiControlProps props) {
    const button_state_t close_state = CloseButton((Vector2) {10, 10}, 16);
    if (close_state == BUTTON_STATE_CLICKED || IsKeyPressed(KEY_ESCAPE)) {
        *props.plot_move = MultiPlot_disable(props.state);
        set_input_mode(INPUT_MODE_IDLE);
        return props.change | MOVE_CHANGE_PLOT;
    }
    Text("σ = f(ε)", 60, 12, 26, BLACK);

    if (props.state->S0 && props.state->L0) {
        Text(props.state->constants_text, 10, 50, 20, BLACK);
        if (ButtonDefault((Vector2) {170, 10}, "Regresja", 16, 0) == BUTTON_STATE_CLICKED) {
            set_input_mode(INPUT_MODE_REGRESSION);
        }
    }

    BottomHelp("SHIFT + Scroll -> Skaluj oś X", 460);

    return props.change;
}
