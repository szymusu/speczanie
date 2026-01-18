#include "ColumnImport.h"

#include "../../text/Button.h"
#include "../../text/text.h"

#define FONT_SIZE 20

const Vector2 import_origin = {700, 500};

void ColumnImport(OpenFile* file) {
    Text("Wybierz kolumny", 400, 20, 32, BLACK);
    Text("x", 200, 120, 48, BLACK);
    Text("y", 200, 320, 48, BLACK);
    const bool can_import = file->column_import_state.selected_x != -1 && file->column_import_state.selected_y != -1;

    float y = 70;
    for (int i = 0; i < file->binary_file.header.column_count; ++i) {
        const char* label = file->binary_file.columns[i].label;
        const bool is_selected = file->column_import_state.selected_x == i;
        const button_state_t button = ButtonDefault((Vector2) {250, y}, label, FONT_SIZE, is_selected & BUTTON_OPTION_ACTIVE);
        if (button == BUTTON_STATE_CLICKED) {
            file->column_import_state.selected_x = i;
        }
        y += 38;
    }

    y = 260;
    for (int i = 0; i < file->binary_file.header.column_count; ++i) {
        const char* label = file->binary_file.columns[i].label;
        const bool is_selected = file->column_import_state.selected_y == i;
        const button_state_t button = ButtonDefault((Vector2) {250, y}, label, FONT_SIZE, is_selected & BUTTON_OPTION_ACTIVE);
        if (button == BUTTON_STATE_CLICKED) {
            file->column_import_state.selected_y = i;
        }
        y += 38;
    }

    const button_state_t import = ButtonDefault(import_origin, "Importuj", FONT_SIZE, !can_import * BUTTON_OPTION_DISABLED);
    if (can_import && import == BUTTON_STATE_CLICKED) {
        import_columns(file, file->column_import_state.selected_x, file->column_import_state.selected_y);
    }
}
