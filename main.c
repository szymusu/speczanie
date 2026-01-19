#include <raylib.h>
#include <stdio.h>

#include "args/args.h"
#include "data/parse_csv.h"
#include "diagnostics/components/BenchmarkProgress.h"
#include "diagnostics/components/Clock.h"
#include "diagnostics/components/FpsCounter.h"
#include "files/open_files.h"
#include "files/components/ColumnImport.h"
#include "files/components/FileList.h"
#include "math/regression.h"
#include "plot/move.h"
#include "plot/plot_math.h"
#include "plot/components/Axes.h"
#include "plot/components/Controls.h"
#include "plot/components/DataPlot.h"
#include "plot/components/Grid.h"
#include "plot/components/MultiPlot.h"
#include "text/text.h"

int main(const int argc, char** argv) {
    Options options;
    if (process_args(argc, argv, &options)) return -1;

#ifndef __arm64
    // Anty-aliasing mega psuje FPS na Macu
    SetConfigFlags(FLAG_MSAA_4X_HINT);
#endif

    InitWindow(PLOT_WIDTH, PLOT_HEIGHT, "Spęczanie");
    font_init();

    OpenFile* current_file = get_selected_file();
    MultiPlotState multi_plot_state = { .enabled = false };
    move_change_t change = 0b11;

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (current_file) {
            if (!is_imported(current_file)) {
                if (options.auto_import) {
                    import_columns(current_file, options.auto_import_x, options.auto_import_y);
                }
                else {
                    ColumnImport(current_file);
                }
            }
            else {
                Bounds bounds;
                if (multi_plot_state.enabled) {
                    bounds = compute_bounds(
                        multi_plot_state.zoom,
                        multi_plot_state.pan,
                        multi_plot_state.scale_x
                    );
                    Grid(bounds);
                    Axes("σ", "ε");
                    MultiPlot(&multi_plot_state, (MultiPlotProps) { bounds });
                }
                else {
                    bounds = compute_bounds(
                        current_file->data_plot_state.zoom,
                        current_file->data_plot_state.pan,
                        current_file->data_plot_state.scale_x
                    );
                    Grid(bounds);
                    Axes(current_file->data_plot_state.x_label, current_file->data_plot_state.y_label);
                    DataPlot(
                    (DataPlotProps) {
                        .data_source = current_file->data_source,
                        .bounds = bounds,
                    },
                    change, &current_file->data_plot_state);
                }

                change = process_move(&current_file->data_plot_state, bounds);
                change = Controls((ControlsProps) {
                    .current_file = current_file,
                    .multi_plot_state = &multi_plot_state,
                    .bounds = bounds,
                    .change = change
                });
            }
        }
        else {
            Text("Upuść pliki W01 lub CSV aby otworzyć", 280, PLOT_HEIGHT / 2.f - 40, 40, BLACK);
        }


        const FileListChange file_list_change = FileList();
        if (file_list_change.closed != -1) {
            printf("closed %d\n", file_list_change.closed);
            close_file(file_list_change.closed);
            current_file = get_selected_file();
            change |= MOVE_CHANGE_PLOT;
        }
        if (file_list_change.selected != -1) {
            current_file = select_file(file_list_change.selected);
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
                current_file = select_file(last);
                change |= MOVE_CHANGE_PLOT;
            }
            UnloadDroppedFiles(files);
        }
    }

    font_unload();
    CloseWindow();
    clear_files();
}
