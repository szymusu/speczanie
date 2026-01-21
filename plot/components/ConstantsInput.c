#include "ConstantsInput.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "../plot_math.h"
#include "../../text/Button.h"
#include "../../text/TextInput.h"
#include "../../text/text.h"

bool ConstantsInput(MultiPlotState* state) {
    DrawRectangle(0, 0, PLOT_WIDTH, PLOT_HEIGHT, (Color) {0,0,0, 50});
    DrawRectangle(450, 140, 300, 300, RAYWHITE);

    Text("Pole przekroju S₀ [mm²]"   , 500, 170, 20, BLACK);
    Text("Długość początkowa L₀ [mm]", 500, 270, 20, BLACK);
    text_change_t l0_change = TextInput(520, 200, state->text_buffers[0], &state->text_lengths[0], state->text_max_len, state->input_focus == 1);
    text_change_t s0_change = TextInput(520, 300, state->text_buffers[1], &state->text_lengths[1], state->text_max_len, state->input_focus == 2);

    if (l0_change == TEXT_CHANGE_INPUT) {
        state->S0_tmp = strtof(state->text_buffers[0], NULL);
    }
    if (s0_change == TEXT_CHANGE_INPUT) {
        state->L0_tmp = strtof(state->text_buffers[1], NULL);
    }
    if (l0_change == TEXT_CHANGE_UNFOCUS) state->input_focus = 2;
    if (s0_change == TEXT_CHANGE_UNFOCUS) state->input_focus = 1;
    if (l0_change == TEXT_CHANGE_FOCUS) state->input_focus = 1;
    if (s0_change == TEXT_CHANGE_FOCUS) state->input_focus = 2;

    const bool both_nonzero = state->S0_tmp != 0 && state->L0_tmp != 0;
    const button_state_t ok_button = ButtonDefault((Vector2) {550, 370}, "  OK  ", 22, BUTTON_OPTION_DISABLED * !both_nonzero);
    if (both_nonzero && (ok_button == BUTTON_STATE_CLICKED || (l0_change | s0_change) & TEXT_CHANGE_ENTER)) {
        state->S0 = state->S0_tmp;
        state->L0 = state->L0_tmp;
        return true;
    }
    return false;
}
