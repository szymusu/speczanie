#include "ColumnImport.h"

#include "../../text/Button.h"
#include "../../text/text.h"

#define FONT_SIZE 20

TextBoxProps tb_idle = {
    .padding = {10, 6},
    .font_size = FONT_SIZE,
    .text_color = BLACK,
    .background_color = WHITE,
    .border_color = DARKBLUE,
    .border = 1,
};
TextBoxProps tb_hover = {
    .padding = {10, 6},
    .font_size = FONT_SIZE,
    .text_color = BLACK,
    .background_color = LIGHTGRAY,
    .border_color = DARKBLUE,
    .border = 2,
};
TextBoxProps tb_active = {
    .padding = {10, 6},
    .font_size = FONT_SIZE,
    .text_color = WHITE,
    .background_color = DARKBLUE,
};
TextBoxProps tb_disabled = {
    .padding = {10, 6},
    .font_size = FONT_SIZE,
    .text_color = GRAY,
    .background_color = LIGHTGRAY,
    .border_color = GRAY,
    .border = 1,
};

const Vector2 import_origin = {700, 500};
const Vector2 x_origin_start = { 250, 70 };
const Vector2 y_origin_start = { 250, 260 };

void ColumnImport(OpenFile* file) {
    Text("Wybierz kolumny", 400, 20, 32, BLACK);
    Text("x", 200, 110, 48, BLACK);
    Text("y", 200, 300, 48, BLACK);
    const bool can_import = file->column_import_state.selected_x != -1 && file->column_import_state.selected_y != -1;

    tb_idle.origin = x_origin_start;
    tb_hover.origin = x_origin_start;
    tb_active.origin = x_origin_start;
    float y = x_origin_start.y;
    for (int i = 0; i < file->binary_file.header.column_count; ++i) {
        const char* label = file->binary_file.columns[i].label;
        if (file->column_import_state.selected_x == i) {
            tb_active.origin.y = y;
            tb_active.text = label;
            ButtonPro(tb_active, tb_active);
        }
        else {
            tb_idle.origin.y = y;
            tb_idle.text = label;
            tb_hover.origin.y = y;
            tb_hover.text = label;
            if (ButtonPro(tb_idle, tb_hover) == BUTTON_STATE_CLICKED) {
                file->column_import_state.selected_x = i;
            }
        }
        y += 35;
    }

    tb_idle.origin = y_origin_start;
    tb_hover.origin = y_origin_start;
    tb_active.origin = y_origin_start;
    y = y_origin_start.y;
    for (int i = 0; i < file->binary_file.header.column_count; ++i) {
        const char* label = file->binary_file.columns[i].label;
        if (file->column_import_state.selected_y == i) {
            tb_active.origin.y = y;
            tb_active.text = label;
            ButtonPro(tb_active, tb_active);
        }
        else {
            tb_idle.origin.y = y;
            tb_idle.text = label;
            tb_hover.origin.y = y;
            tb_hover.text = label;
            if (ButtonPro(tb_idle, tb_hover) == BUTTON_STATE_CLICKED) {
                file->column_import_state.selected_y = i;
            }
        }
        y += 35;
    }

    if (can_import) {
        tb_idle.origin = import_origin;
        tb_idle.text = "Importuj";
        tb_hover.origin = import_origin;
        tb_hover.text = "Importuj";
        if (ButtonPro(tb_idle, tb_hover) == BUTTON_STATE_CLICKED) {
            // import_columns(file, 3, 2);
            import_columns(file, file->column_import_state.selected_x, file->column_import_state.selected_y);
        }
    }
    else {
        tb_disabled.origin = import_origin;
        tb_disabled.text = "Importuj";
        ButtonPro(tb_disabled, tb_disabled);
    }
}
