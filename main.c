#include <raylib.h>
#include <stdio.h>

#include "data/parse_binary.h"
#include "data/point_data.h"
#include "diagnostics/more_data.h"
#include "diagnostics/components/Clock.h"
#include "diagnostics/components/FpsCounter.h"
#include "plot/move.h"
#include "plot/plot_math.h"
#include "plot/components/DataPlot.h"
#include "plot/components/Grid.h"
#include "plot/components/SplinePlot.h"
#include "text/Button.h"
#include "text/text.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "Raylib Window");
    font_init("resources/JetBrainsMono-SemiBold.ttf");

    // BinaryFile file = file_parse("input/19_v10.W01");
    BinaryFile file = file_parse("input/20_v50.W01");
    DataSource file_source = data_source_columns(&file, 3, 0, 100.f);
    DataPlotState plot_state = DataPlotState_create(file_source.count);

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
                .data_source = file_source,
                .bounds = bounds,
                .plot_offset = move_state.plot_offset
            },
            change, &plot_state);


        change = process_move(&move_state, bounds);
        if (change & MOVE_CHANGE_PLOT) {
            sprintf(offset_text, "x: %.2f\ny: %.2f", move_state.plot_offset.x, move_state.plot_offset.y);
        }

        if (Button((Vector2) {10, 50}, "Odwroc y", 16, 0) == BUTTON_STATE_CLICKED) {
            data_scale_y(&file_source, -1);
            change |= MOVE_CHANGE_PLOT;
        }

        if (file_source.data->x != 0 || file_source.data->y != 0) {
            if (Button((Vector2) {10, 100}, "Zeruj start", 16, 0) == BUTTON_STATE_CLICKED) {
                data_apply_offset(&file_source, (Vector2) {
                    -file_source.data[0].x,
                    file_source.data[0].y
                });
                *(uint64_t*)&move_state.plot_offset = 0;
                change |= MOVE_CHANGE_PLOT;
            }
        }

        if (*(uint64_t*)&move_state.plot_offset != 0) {
            if (Button((Vector2) {10, 140}, offset_text, 16, 0) == BUTTON_STATE_CLICKED) {
                data_apply_offset(&file_source, move_state.plot_offset);
                *(uint64_t*)&move_state.plot_offset = 0;
                change |= MOVE_CHANGE_PLOT;
            }
        }

        if (plot_state.selected_point > 0) {
            Text("Utnij", 10, 200, 16, BLACK);
            if (Button((Vector2) {70, 200}, "Lewo", 16, TEXTBOX_ALIGN_RIGHT) == BUTTON_STATE_CLICKED) {
                data_cut_left(&file_source, plot_state.selected_point);
                plot_state.selected_point = -1;
                change |= MOVE_CHANGE_PLOT;
            }
            if (Button((Vector2) {75, 200}, "Prawo", 16, 0) == BUTTON_STATE_CLICKED) {
                data_cut_right(&file_source, plot_state.selected_point);
                plot_state.selected_point = -1;
                change |= MOVE_CHANGE_PLOT;
            }
        }

        if (GetTime() > .5) FpsCounter();
        EndDrawing();
    }

    font_unload();
    CloseWindow();
    file_destroy(&file);
    data_source_destroy(&file_source);
    DataPlotState_destroy(&plot_state);
}
