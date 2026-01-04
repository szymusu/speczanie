#include "FileList.h"

#include "../open_files.h"
#include "../../plot/plot_math.h"
#include "../../text/Button.h"

int FileList() {
    const int count = get_count();
    const OpenFile* files = get_files();
    int clicked = -1;

    for (int i = 0; i < count; ++i) {
        const button_state_t button_state = Button(
            (Vector2) {PLOT_WIDTH - 5, i * 35.f + 5.f},
            files[i].filename, 15, TEXTBOX_ALIGN_RIGHT
        );
        if (button_state == BUTTON_STATE_CLICKED) clicked = i;
    }
    return clicked;
}
