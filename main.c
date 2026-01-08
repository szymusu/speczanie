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
    font_init();

    OpenFile* current_file = get_selected_file();

    move_change_t change = 0b11;

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (current_file) {
            const Bounds bounds = compute_bounds(current_file->data_plot_state.zoom, current_file->data_plot_state.pan);
            Grid(bounds);
            DataPlot(
                (DataPlotProps) {
                    .data_source = current_file->data_source,
                    .bounds = bounds,
                },
                change, &current_file->data_plot_state);

            change = process_move(&current_file->data_plot_state, bounds);
            change = Controls(current_file, &current_file->data_plot_state, change);
        }
        else {
            Text("Upuść pliki .W01 aby otworzyć", 200, 200, 20, BLACK);
        }


        const int clicked = FileList();
        if (clicked != -1) {
            current_file = select_file(clicked);
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
                current_file = select_file(clicked);
                change |= MOVE_CHANGE_PLOT;
            }
            UnloadDroppedFiles(files);
        }
    }

    font_unload();
    CloseWindow();
    clear_files();
}
