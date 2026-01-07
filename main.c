#include <raylib.h>
#include <stdio.h>

#include "args/args.h"
#include "diagnostics/components/FpsCounter.h"
#include "files/open_files.h"
#include "files/components/FileList.h"
#include "plot/move.h"
#include "plot/plot_math.h"
#include "plot/components/Controls.h"
#include "plot/components/DataPlot.h"
#include "plot/components/Grid.h"
#include "text/text.h"

int main(const int argc, char** argv) {
    if (process_args(argc, argv)) return -1;

    // Anty-aliasing mega psuje FPS na Macu
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(PLOT_WIDTH, PLOT_HEIGHT, "Spęczator 2000");
    font_init("resources/JetBrainsMono-SemiBold.ttf");

    OpenFile* current_file = get_selected_file();

    MoveState move_state = {
        .zoom = 1.f,
        .pan = {0, 0}
    };
    move_change_t change = 0b11;

    while (!WindowShouldClose()) {
        const Bounds bounds = compute_bounds(move_state.zoom, move_state.pan);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Grid(bounds);

        if (current_file) DataPlot(
            (DataPlotProps) {
                .data_source = current_file->data_source,
                .bounds = bounds,
                .plot_offset = move_state.plot_offset
            },
            change, &current_file->data_plot_state);

        change = process_move(&move_state, bounds);

        if (current_file) change = Controls(current_file, &move_state, change);

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
            int last = -1;
            for (int i = 0; i < files.count; ++i) {
                printf("%s\n", files.paths[i]);
                last = open_file(files.paths[i]);
            }
            if (last != -1){
                select_file(last);
                current_file = get_selected_file();
                change |= MOVE_CHANGE_PLOT;
            }
            UnloadDroppedFiles(files);
        }
    }

    font_unload();
    CloseWindow();
    clear_files();
}
