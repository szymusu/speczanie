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
    Bounds bounds = compute_bounds(zoom, pan_x);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (GetTime() > .5) FpsCounter();

        Grid(1., bounds);
        SplinePlot(bounds);

        EndDrawing();
    }

    CloseWindow();
}
