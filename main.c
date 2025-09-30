#include <raylib.h>

#include "diagnostics/components/FpsCounter.h"
#include "plot/plot_math.h"
#include "plot/components/Grid.h"
#include "plot/components/SplinePlot.h"

int main() {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 450;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Window");
    // SetTargetFPS(60);

    const double zoom = 1.;
    const double pan_x = 5.;
    const double start_x = PLOT_START_X / zoom + pan_x;
    const double end_x = PLOT_END_X / zoom + pan_x;
    const double start_y = PLOT_START_Y / zoom / ((double) PLOT_WIDTH / PLOT_HEIGHT);
    const double end_y = PLOT_END_Y / zoom / ((double) PLOT_WIDTH / PLOT_HEIGHT);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (GetTime() > .5) FpsCounter();

        Grid(1., start_x, end_x, start_y, end_y);
        SplinePlot(start_x, end_x, start_y, end_y);

        EndDrawing();
    }

    CloseWindow();
}
