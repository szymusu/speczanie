#include <raylib.h>
#include <stdio.h>

#include "args/args.h"
#include "diagnostics/components/FpsCounter.h"
#include "files/open_files.h"
#include "files/components/ColumnImport.h"
#include "files/components/FileList.h"
#include "plot/input_mode.h"
#include "plot/move.h"
#include "plot/plot_math.h"
#include "plot/components/Axes.h"
#include "plot/components/Controls.h"
#include "plot/components/DataPlot.h"
#include "plot/components/Grid.h"
#include "plot/components/MultiControls.h"
#include "plot/components/MultiPlot.h"
#include "plot/components/RegressionControls.h"
#include "text/text.h"

int main(const int argc, char** argv) {
    Options options = options_default();
    int exit_code = process_args(argc, argv, &options);
    if (exit_code) return exit_code;

#ifndef __arm64
    // Anty-aliasing mega psuje FPS na Macu
    SetConfigFlags(FLAG_MSAA_4X_HINT);
#endif

    InitWindow(PLOT_WIDTH, PLOT_HEIGHT, "Spęczanie");
    SetExitKey(KEY_NULL);
    font_init();

    OpenFile* current_file = get_selected_file();
    MultiPlotState multi_plot_state = { 0 };
    move_change_t change = 0b11;

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        const bool multi = multi_plot_state.enabled;
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
                ViewMove* view_move = multi ? &multi_plot_state.view_move : &current_file->data_plot_state.view_move;
                const Bounds bounds = compute_bounds(*view_move);
                Grid(bounds);

                if (multi) {
                    Axes("ε", "σ [MPa]");
                    MultiPlot((MultiPlotProps) { bounds }, &multi_plot_state, change);
                }
                else {
                    Axes(current_file->data_plot_state.x_label, current_file->data_plot_state.y_label);
                    DataPlot((DataPlotProps) {
                        .data_source = current_file->data_source,
                        .bounds = bounds,
                        .color = DARKBLUE
                    },
                    change, &current_file->data_plot_state);
                }

                change = process_move((MoveProps) {
                    .view_move = view_move,
                    .plot_move = multi ? NULL : &current_file->data_plot_state.plot_move,
                    .bounds = bounds
                });
                if (is_input_mode(INPUT_MODE_REGRESSION)) {
                    change = RegressionControls((RegressionControlProps) {
                        .curve = &current_file->data_plot_state.curve_polynomial,
                        .regression_point_count = current_file->data_plot_state.regression_points_count,
                        .change = change
                    });
                }
                else if (multi) {
                    change = MultiControls((MultiControlProps) {
                        .state = &multi_plot_state,
                        .plot_move = &current_file->data_plot_state.view_move,
                        .change = change
                    });
                }
                else {
                    change = Controls((ControlsProps) {
                        .current_file = current_file,
                        .multi_plot_state = &multi_plot_state,
                        .bounds = bounds,
                        .change = change
                    });
                }
            }
        }
        else {
            Text("Upuść pliki W01 lub CSV aby otworzyć", 280, PLOT_HEIGHT / 2.f - 40, 40, BLACK);
        }


        const FileListChange file_list_change = FileList(multi);
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

        if (options.show_fps && GetTime() > 1) FpsCounter();
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
