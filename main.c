#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "data/parse_binary.h"
#include "diagnostics/components/FpsCounter.h"
#include "plot/move.h"
#include "plot/plot_math.h"
#include "plot/components/DataPlot.h"
#include "plot/components/Grid.h"
#include "plot/components/SplinePlot.h"

int main() {
    BinaryFile file = file_parse("input/19_v10.W01");
    Vector2* data = malloc(sizeof(Vector2) * file.header.row_count);
    for (uint32_t i = 0; i < file.header.row_count; ++i) {
        data[i].x = file.columns[3].data[i] * 50;
        data[i].y = file.columns[0].data[i];
    }
    Vector2* points = malloc(sizeof(Vector2) * file.header.row_count);

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 450;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Window");

    float zoom = 1.f;
    Vector2 pan = {0, 0};
    Bounds bounds = compute_bounds(zoom, pan);

    while (!WindowShouldClose()) {
        process_move(&zoom, &pan, bounds);

        bounds = compute_bounds(zoom, pan);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (GetTime() > .5) FpsCounter();

        Grid(1., bounds);
        SplinePlot(bounds);
        DataPlot(data, points, file.header.row_count, bounds);

        EndDrawing();
    }

    CloseWindow();
    file_destroy(&file);
}
