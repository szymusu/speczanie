#include <raylib.h>
#include <stdio.h>

#include "data/parse_binary.h"
#include "diagnostics/components/FpsCounter.h"
#include "files/open_files.h"
#include "files/components/FileList.h"
#include "plot/move.h"
#include "plot/plot_math.h"
#include "plot/components/Controls.h"
#include "plot/components/DataPlot.h"
#include "plot/components/Grid.h"
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
            data_apply_offset(&current_file->data_source, move_state.plot_offset);
            move_state.plot_offset = VECTOR2_ZERO;
        }

        change = Controls(current_file, &move_state, change);

        const int clicked = FileList();
        if (clicked != -1) {
            select_file(clicked);
            current_file = get_selected_file();
            change |= MOVE_CHANGE_PLOT;
        }

        if (GetTime() > .5) FpsCounter();
        EndDrawing();

        if (IsFileDropped()) {
            const FilePathList files = LoadDroppedFiles();
            for (int i = 0; i < files.count; ++i) {
                printf("%s\n", files.paths[i]);
                open_file(files.paths[i]);
            }
            UnloadDroppedFiles(files);
        }
    }

    font_unload();
    CloseWindow();
    clear_files();
}
