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
#include "text/text.h"

int main() {
    InitWindow(800, 450, "Raylib Window");
    font_init("resources/JetBrainsMono-SemiBold.ttf");

    BinaryFile file = file_parse("input/19_v10.W01");
    DataSource file_source = data_source_columns(&file, 3, 0, 50.f);
    DataPlotState plot_state = DataPlotState_create(file_source.count);

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

        DataPlot(
            (DataPlotProps) {
                .data_source = file_source,
                .bounds = bounds,
                .plot_offset = move_state.plot_offset
            },
            change, &plot_state);

        if (GetTime() > .5) FpsCounter();
        EndDrawing();

        change = process_move(&move_state, bounds);
    }

    font_unload();
    CloseWindow();
    file_destroy(&file);
    data_source_destroy(&file_source);
    DataPlotState_destroy(&plot_state);
}
