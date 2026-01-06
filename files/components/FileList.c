#include "FileList.h"

#include "../open_files.h"
#include "../../plot/plot_math.h"
#include "../../text/Button.h"

#define FONT_SIZE 15.f

int FileList() {
    const int count = get_count();
    const OpenFile* files = get_files();
    const int selected = get_selected();
    int clicked = -1;

    for (int i = 0; i < count; ++i) {
        if (i == selected) {
            TextBox((TextBoxProps) {
                .origin = {PLOT_WIDTH - 5, i * 35.f + 5.f},
                .padding = {FONT_SIZE, FONT_SIZE / 2},
                .text = files[i].filename,
                .font_size = 15,
                .background_color = DARKBLUE,
                .border_color = DARKBLUE,
                .text_color = WHITE,
                .border = 1,
                .align = TEXTBOX_ALIGN_RIGHT
                }
            );
        }
        else {
            const button_state_t button_state = ButtonPro((TextBoxProps) {
                .origin = {PLOT_WIDTH - 5, i * 35.f + 5.f},
                .padding = {FONT_SIZE, FONT_SIZE / 2},
                .text = files[i].filename,
                .font_size = 15,
                .background_color = RAYWHITE,
                .border_color = DARKBLUE,
                .text_color = BLACK,
                .border = 1,
                .align = TEXTBOX_ALIGN_RIGHT
                },
                (TextBoxProps) {
                .origin = {PLOT_WIDTH - 5, i * 35.f + 5.f},
                .padding = {FONT_SIZE, FONT_SIZE / 2},
                .text = files[i].filename,
                .font_size = 15,
                .background_color = LIGHTGRAY,
                .border_color = DARKBLUE,
                .text_color = BLACK,
                .border = 1,
                .align = TEXTBOX_ALIGN_RIGHT
                }
            );
            if (button_state == BUTTON_STATE_CLICKED) clicked = i;
        }
    }
    return clicked;
}
