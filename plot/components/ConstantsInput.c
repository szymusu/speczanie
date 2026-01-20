#include "ConstantsInput.h"

#include <raylib.h>

#include "../plot_math.h"
#include "../../text/Button.h"

bool ConstantsInput(float* S0, float* L0) {
    DrawRectangle(0, 0, PLOT_WIDTH, PLOT_HEIGHT, (Color) {0,0,0, 20});

    if (ButtonDefault((Vector2) {300, 300}, "OK", 20, 0) == BUTTON_STATE_CLICKED) {
        *S0 = 60*60;
        *L0 = 60;
        return true;
    }
    return false;
}
