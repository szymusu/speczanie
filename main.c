#include <raylib.h>

#include "diagnostics/components/FpsCounter.h"
#include "plot/components/Grid.h"
#include "plot/components/Plot.h"
#include "plot/components/ScatterPlot.h"
#include "plot/components/SplinePlot.h"

int main() {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 450;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Window");
    // SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (GetTime() > .5) FpsCounter();

        Grid(1.);
        Plot();
        ScatterPlot();
        SplinePlot();

        EndDrawing();
    }

    CloseWindow();
}
