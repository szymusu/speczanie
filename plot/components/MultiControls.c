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

    BottomHelp("SHIFT + Scroll -> Skaluj oś X", 460);

    return props.change;
}
