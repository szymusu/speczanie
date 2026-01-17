#include "FileList.h"

#include "CloseButton.h"
#include "../open_files.h"
#include "../../plot/plot_math.h"
#include "../../text/Button.h"

#define FONT_SIZE 16.f
#define CLOSE_BUTTON_WIDTH 50

FileListChange FileList() {
    const int count = get_count();
    const OpenFile* files = get_files();
    const int selected = get_selected();

    FileListChange result = { -1, -1 };

    for (int i = 0; i < count; ++i) {
        const Vector2 origin = {PLOT_WIDTH - CLOSE_BUTTON_WIDTH, i * 35.f + 5.f};

        const button_state_t close_state = CloseButton(origin, FONT_SIZE);
        if (close_state == BUTTON_STATE_CLICKED) {
            result.closed = i;
        }

        if (i == selected) {
            TextBox((TextBoxProps) {
                .origin = origin,
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
                .origin = origin,
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
                .origin = origin,
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
            if (button_state == BUTTON_STATE_CLICKED) result.selected = i;
        }
    }
    return result;
}
