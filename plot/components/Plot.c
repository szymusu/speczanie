#include "Plot.h"

#include <math.h>
#include <raylib.h>

#include "../plot_math.h"

double f(const double x) {
    return sin(x) * 2;
}

void Plot() {
    DrawRectangleLines(PLOT_OFFSET_X, PLOT_OFFSET_Y, PLOT_WIDTH, PLOT_HEIGHT, GRAY);

    for (int x = 0; x < PLOT_WIDTH; ++x) {
        const int y = y_to_pixel(f(pixel_to_x(x)));
        DrawPixel(x + PLOT_OFFSET_X, y + PLOT_OFFSET_Y, DARKBLUE);
    }
}
