#include <raylib.h>
#include <stdio.h>

#include "data/parse_binary.h"
#include "data/point_data.h"
#include "diagnostics/more_data.h"
#include "diagnostics/components/Clock.h"
#include "diagnostics/components/FpsCounter.h"
#include "files/open_files.h"
#include "files/components/FileList.h"
#include "plot/move.h"
#include "plot/plot_math.h"
#include "plot/components/DataPlot.h"
#include "plot/components/Grid.h"
#include "plot/components/SplinePlot.h"
#include "text/Button.h"
#include "text/text.h"
#include "util/vector2.h"

int main() {
    // Anty-aliasing mega psuje FPS na Macu
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(PLOT_WIDTH, PLOT_HEIGHT, "Raylib Window");
    font_init("resources/JetBrainsMono-SemiBold.ttf");

    const int f1 = open_file("input/19_v10.W01");
    const int f2 = open_file("input/20_v50.W01");
    OpenFile* current_file = get_selected_file();

    MoveState move_state = {
        .zoom = 1.f,
        .pan = {0, 0}
    };
    move_change_t change = 0b11;

    char offset_text[32] = "0";

    while (!WindowShouldClose()) {
        const Bounds bounds = compute_bounds(move_state.zoom, move_state.pan);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Grid(bounds);

        DataPlot(
            (DataPlotProps) {
                .data_source = current_file->data_source,
                .bounds = bounds,
                .plot_offset = move_state.plot_offset
            },
            change, &current_file->data_plot_state);

        change = process_move(&move_state, bounds);
        if (change & MOVE_CHANGE_PLOT) {
            sprintf(offset_text, "x: %.2f\ny: %.2f", move_state.plot_offset.x, move_state.plot_offset.y);
        }

        if (change & MOVE_CHANGE_APPLY_OFFSET) {
            puts("aplaj ofset");
            data_apply_offset(&current_file->data_source, move_state.plot_offset);
            move_state.plot_offset = VECTOR2_ZERO;
        }

        if (Button((Vector2) {10, 50}, "Odwroc y", 16, 0) == BUTTON_STATE_CLICKED) {
            data_scale_y(&current_file->data_source, -1);
            change |= MOVE_CHANGE_PLOT;
        }

        if (Button((Vector2) {100, 50}, "Odwroc x", 16, 0) == BUTTON_STATE_CLICKED) {
            data_flip_x(&current_file->data_source);
            change |= MOVE_CHANGE_PLOT;
        }

        if (!is_vec2_zero(current_file->data_source.data[0])) {
            if (Button((Vector2) {10, 100}, "Zeruj start", 16, 0) == BUTTON_STATE_CLICKED) {
                data_apply_offset(&current_file->data_source, (Vector2) {
                    -current_file->data_source.data[0].x,
                    current_file->data_source.data[0].y
                });
                move_state.plot_offset = VECTOR2_ZERO;
                change |= MOVE_CHANGE_PLOT;
            }
        }

        if (*(uint64_t*)&move_state.plot_offset != 0) {
            if (Button((Vector2) {10, 140}, offset_text, 16, 0) == BUTTON_STATE_CLICKED) {
                data_apply_offset(&current_file->data_source, move_state.plot_offset);
                move_state.plot_offset = VECTOR2_ZERO;
                change |= MOVE_CHANGE_PLOT;
            }
        }

        if (current_file->data_plot_state.selected_point > 0) {
            Text("Utnij", 10, 200, 16, BLACK);
            if (Button((Vector2) {70, 216}, "Lewo", 16, TEXTBOX_ALIGN_RIGHT) == BUTTON_STATE_CLICKED) {
                data_cut_left(&current_file->data_source, current_file->data_plot_state.selected_point);
                current_file->data_plot_state.selected_point = -1;
                change |= MOVE_CHANGE_PLOT;
            }
            if (Button((Vector2) {75, 216}, "Prawo", 16, 0) == BUTTON_STATE_CLICKED) {
                data_cut_right(&current_file->data_source, current_file->data_plot_state.selected_point);
                current_file->data_plot_state.selected_point = -1;
                change |= MOVE_CHANGE_PLOT;
            }
        }

        const int clicked = FileList();
        if (clicked != -1) {
            select_file(clicked);
            current_file = get_selected_file();
            change |= MOVE_CHANGE_PLOT;
        }

        if (GetTime() > .5) FpsCounter();
        EndDrawing();
    }

    font_unload();
    CloseWindow();
    clear_files();
}
