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

    // BinaryFile file = file_parse("input/19_v10.W01");
    // Vector2* data = malloc(sizeof(Vector2) * file.header.row_count);
    // for (uint32_t i = 0; i < file.header.row_count; ++i) {
    //     data[i].x = file.columns[3].data[i] * 50;
    //     data[i].y = file.columns[0].data[i];
    // }
    // Vector2* points = malloc(sizeof(Vector2) * file.header.row_count);
    DataSource sin0 = create_sinus_data(10000000, 0.f);
    DataPlotState sin0_state = DataPlotState_create(sin0.count);

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
                .data_source = sin0,
                .bounds = bounds,
                .plot_offset = move_state.plot_offset
            },
            change, &sin0_state);

        if (GetTime() > .5) FpsCounter();
        EndDrawing();

        change = process_move(&move_state, bounds);
    }

    font_unload();
    CloseWindow();
    // file_destroy(&file);
    destroy_sinus_data(&sin0);
    DataPlotState_destroy(&sin0_state);
}
